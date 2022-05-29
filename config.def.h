/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int gap                = 5;
static const unsigned int gappih    = gap;       /* horiz inner gap between windows */
static const unsigned int gappiv    = gap;       /* vert inner gap between windows */
static const unsigned int gappoh    = gap;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = gap;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = False;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:style:medium:size=10" };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char col_urgborder[]   = "#ff0000";
static char col_red[]         = "#FF0000";
static char col_orange[]      = "#FF8800";
static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemeUrg]  = { selfgcolor, selbgcolor,  col_urgborder  },
	[SchemeStatus]  = { normfgcolor, normbgcolor,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { selfgcolor, selbgcolor,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { normfgcolor, normbgcolor,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { selfgcolor, normbgcolor,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { normfgcolor, normbgcolor,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeScratchSel]  = { selfgcolor, selbgcolor,  col_red  },
	[SchemeScratchNorm] = { selfgcolor, selbgcolor,  col_orange },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor   scratch key*/
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1,		0 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1,		0 },
	{ NULL,       NULL,   "scratchpad",   0,            1,			 1,           -1,       's' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "shift-tools.c"
#include <X11/XF86keysym.h>

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|M|",      centeredmaster },
	{ "[M]",      monocle },
	{ "D[]",      deck },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define sh(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define term "alacritty"

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "alacritty", "-t", "scratchpad", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,            		    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          sh("librewolf")},
	{ MODKEY,                       XK_s,      spawn,          sh("codium")},
	{ MODKEY|ShiftMask,             XK_e,      spawn,          sh("thunar")},
	{ MODKEY,                       XK_d,      spawn,          sh(term " -e nvim")},
	{ MODKEY,                       XK_e,      spawn,          sh(term " -e lf")},
	{ MODKEY,                       XK_a,      spawn,          sh(term " -e htop")},
	{ MODKEY,                       XK_g,      spawn,          sh(term " -e gotop")},
	{ MODKEY,                       XK_r,      spawn,          sh(term " -e musikcube")},
    { 0,                            XK_Print,  spawn,          sh("flameshot gui")},
	{ 0,                            XK_Insert, spawn,          sh("flameshot gui")},
	{ MODKEY,                       XK_space,  spawn,          sh("~/.config/rofi/bin/launcher_colorful")},
	{ Mod1Mask,                     XK_F2,     spawn,          sh("~/.config/rofi/bin/applet_powermenu")},
	{ Mod1Mask,                     XK_F3,     spawn,          sh("~/.config/rofi/bin/applet_network")},
	{ Mod1Mask,                     XK_F4,     spawn,          sh("~/.config/rofi/bin/applet_volume")},
	{ MODKEY,                       XK_F2,     spawn,          sh("systemctl poweroff") },
	{ MODKEY,             			XK_F3,     spawn,          sh("systemctl suspend") },
	{ MODKEY,             			XK_F4,     spawn,          sh("killall xinit") },
	{ MODKEY,             			XK_F5,     spawn,          sh("systemctl reboot") },
	{ MODKEY, 		    			XK_F6,     spawn,          sh("betterlockscreen -l dimblur") },
	{ MODKEY,             			XF86XK_RFKill,spawn,       sh("wifi toggle") },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,     sh("light -A 1") },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,     sh("light -U 1") },
	{ MODKEY|ShiftMask,             XK_F2,     spawn,          sh("light -S 0") },
	{ MODKEY|ShiftMask,             XK_F3,     spawn,          sh("light -S 6") },
	{ MODKEY,                       XK_grave,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,                       XK_g,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ControlMask,             XK_g,      removescratch,  {.v = scratchpadcmd } },
	{ MODKEY|Mod1Mask,           XK_g,      setscratch,     {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_l,   focusdir,       {.i = 0 } }, // left
	{ MODKEY,                       XK_h,  focusdir,       {.i = 1 } }, // right
	{ MODKEY,                       XK_k,     focusdir,       {.i = 2 } }, // up
	{ MODKEY,                       XK_j,   focusdir,       {.i = 3 } }, // down
	{ MODKEY|ControlMask,           XK_h,   placedir,       {.i = 0 } }, // left
	{ MODKEY|ControlMask,           XK_l,  placedir,       {.i = 1 } }, // right
	{ MODKEY|ControlMask,           XK_k,     placedir,       {.i = 2 } }, // up
	{ MODKEY|ControlMask,           XK_j,   placedir,       {.i = 3 } }, // down
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_bracketleft,      shiftboth,      { .i = -1 }	},
	{ MODKEY|ShiftMask,             XK_bracketright,      shiftboth,      { .i = +1 }	},
	{ MODKEY|ControlMask,		XK_bracketleft,      shiftswaptags,  { .i = -1 }	},
	{ MODKEY|ControlMask,		XK_bracketright,      shiftswaptags,  { .i = +1 }	},
	{ MODKEY,                       XK_bracketleft, shiftviewclients,    { .i = -1 } },
	{ MODKEY,                       XK_bracketright, shiftviewclients,    { .i = +1 } },
	{ MODKEY|Mod1Mask,             XK_bracketleft,	shiftview,         { .i = -1 } },
	{ MODKEY|Mod1Mask,             XK_bracketright,	shiftview,         { .i = +1 } },
	{ MODKEY|ShiftMask,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|Mod1Mask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|Mod1Mask,             XK_plus,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,                       XK_Return, zoom,           {0} },
	{ MODKEY,              			XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,              			XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,    			XK_minus,  togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_equal,  defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 	  	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefakefullscreen, {0} },
	{ MODKEY,                       XK_0,      tag,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      view,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_r,     xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,Button1,       resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


