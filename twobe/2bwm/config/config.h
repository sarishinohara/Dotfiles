///---User configurable stuff---///
///---Modifiers---///
#define MOD             XCB_MOD_MASK_4       /* Super/Windows key  or check xmodmap(1) with -pm  defined in /usr/include/xcb/xproto.h */
///--Speed---///
/* Move this many pixels when moving or resizing with keyboard unless the window has hints saying otherwise.
 *0)move step slow   1)move step fast
 *2)mouse slow       3)mouse fast     */
static const uint16_t movements[] = {20,40,15,400};
/* resize by line like in mcwm -- jmbi */
static const bool     resize_by_line          = true;
/* the ratio used when resizing and keeping the aspect */
static const float    resize_keep_aspect_ratio= 1.03;
///---Offsets---///
/*0)offsetx          1)offsety
 *2)maxwidth         3)maxheight */
static const uint8_t offsets[] = {0,0,0,0};
///---Colors---///
/*0)focuscol         1)unfocuscol
 *2)fixedcol         3)unkilcol
 *4)fixedunkilcol    5)outerbordercol
 *6)emptycol         */
static const char *colors[] = {"#1d383e","#1d383e","#ffffff","#e47d73","#ffffff","#1d383e","#1d383e"};
/* if this is set to true the inner border and outer borders colors will be swapped */
static const bool inverted_colors = false;
///---Cursor---///
/* default position of the cursor:
 * correct values are:
 * TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, MIDDLE
 * All these are relative to the current window. */
#define CURSOR_POSITION MIDDLE
///---Borders---///
/*0) Outer border size. If you put this negative it will be a square.
 *1) Full borderwidth    2) Magnet border size
 *3) Resize border size  */
static const uint8_t borders[] = {0,0,0,4};
/* Windows that won't have a border.
 * It uses substring comparison with what is found in the WM_NAME
 * attribute of the window. You can test this using `xprop WM_NAME`
 */
#define LOOK_INTO "WM_NAME"
static const char *ignore_names[] = {"bar", "xclock"};
///--Menus and Programs---///
static const char *menucmd[] = { "", NULL };
static const char *sakura[]   = { "sakura", NULL };
static const char *urxvt[]   = { "urxvt", NULL };
static const char *rofi[]   = { "rofir", NULL };
static const char *dmenu[]   = { "dmenuu", NULL };
static const char *draw[]   = { "draw", NULL };
static const char *std[]   = { "std", NULL };
static const char *brightup[]   = { "light", "-A","0.5", NULL };
static const char *brightdown[]   = { "light", "-U", "0.5", NULL };
static const char *volup[]   = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldown[]   = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *wall[]   = { "wall", NULL };
static const char *wald[]   = { "wald", NULL };
static const char *date[]   = { "dato", NULL };
static const char *bat[]   = { "bato", NULL };
static const char *lock[]   = { "i3lock-next", NULL };
///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=TWOBWM_MAXHALF_VERTICAL_LEFT};
	maxhalf(&arg2);
	Arg arg3 = {.i=TWOBWM_TELEPORT_CENTER};
	teleport(&arg3);
}
///---Shortcuts---///
/* Check /usr/include/X11/keysymdef.h for the list of all keys
 * 0x000000 is for no modkey
 * If you are having trouble finding the right keycode use the `xev` to get it
 * For example:
 * KeyRelease event, serial 40, synthetic NO, window 0x1e00001,
 *  root 0x98, subw 0x0, time 211120530, (128,73), root:(855,214),
 *  state 0x10, keycode 171 (keysym 0x1008ff17, XF86AudioNext), same_screen YES,
 *  XLookupString gives 0 bytes: 
 *  XFilterEvent returns: False
 *
 *  The keycode here is keysym 0x1008ff17, so use  0x1008ff17
 *
 *
 * For AZERTY keyboards XK_1...0 should be replaced by :
 *      DESKTOPCHANGE(     XK_ampersand,                     0)
 *      DESKTOPCHANGE(     XK_eacute,                        1)
 *      DESKTOPCHANGE(     XK_quotedbl,                      2)
 *      DESKTOPCHANGE(     XK_apostrophe,                    3)
 *      DESKTOPCHANGE(     XK_parenleft,                     4)
 *      DESKTOPCHANGE(     XK_minus,                         5)
 *      DESKTOPCHANGE(     XK_egrave,                        6)
 *      DESKTOPCHANGE(     XK_underscore,                    7)
 *      DESKTOPCHANGE(     XK_ccedilla,                      8)
 *      DESKTOPCHANGE(     XK_agrave,                        9)*
 */
#define DESKTOPCHANGE(K,N) \
    {  MOD ,             K,              changeworkspace, {.i=N}}, \
    {  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
    /* modifier           key            function           argument */
    // Focus to next/previous window
    {  MOD ,              XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_NEXT}},
    {  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_PREVIOUS}},
    // Kill a window
    {  MOD |SHIFT,        XK_q,          deletewin,         {}},
    // Resize a window
    {  MOD |SHIFT,        XK_Up,         resizestep,        {.i=TWOBWM_RESIZE_UP}},
    {  MOD |SHIFT,        XK_Down,       resizestep,        {.i=TWOBWM_RESIZE_DOWN}},
    {  MOD |SHIFT,        XK_Right,      resizestep,        {.i=TWOBWM_RESIZE_RIGHT}},
    {  MOD |SHIFT,        XK_Left,       resizestep,        {.i=TWOBWM_RESIZE_LEFT}},
    // Resize a window slower
    {  MOD |SHIFT|CONTROL,XK_Up,         resizestep,        {.i=TWOBWM_RESIZE_UP_SLOW}},
    {  MOD |SHIFT|CONTROL,XK_Down,       resizestep,        {.i=TWOBWM_RESIZE_DOWN_SLOW}},
    {  MOD |SHIFT|CONTROL,XK_Right,      resizestep,        {.i=TWOBWM_RESIZE_RIGHT_SLOW}},
    {  MOD |SHIFT|CONTROL,XK_Left,       resizestep,        {.i=TWOBWM_RESIZE_LEFT_SLOW}},
    // Move a window
    {  MOD ,              XK_Up,         movestep,          {.i=TWOBWM_MOVE_UP}},
    {  MOD ,              XK_Down,       movestep,          {.i=TWOBWM_MOVE_DOWN}},
    {  MOD ,              XK_Right,      movestep,          {.i=TWOBWM_MOVE_RIGHT}},
    {  MOD ,              XK_Left,       movestep,          {.i=TWOBWM_MOVE_LEFT}},
    // Move a window slower
    {  MOD |CONTROL,      XK_Up,         movestep,          {.i=TWOBWM_MOVE_UP_SLOW}},
    {  MOD |CONTROL,      XK_Down,       movestep,          {.i=TWOBWM_MOVE_DOWN_SLOW}},
    {  MOD |CONTROL,      XK_Right,      movestep,          {.i=TWOBWM_MOVE_RIGHT_SLOW}},
    {  MOD |CONTROL,      XK_Left,       movestep,          {.i=TWOBWM_MOVE_LEFT_SLOW}},
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD ,              XK_a,          teleport,          {.i=TWOBWM_TELEPORT_CENTER}},
    // Center y:
    {  MOD |SHIFT,        XK_a,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_Y}},
    // Center x:
    {  MOD |CONTROL,      XK_a,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_X}},
    // Top left:
    {  MOD ,              XK_y,          teleport,          {.i=TWOBWM_TELEPORT_TOP_LEFT}},
    // Top right:
    {  MOD ,              XK_u,          teleport,          {.i=TWOBWM_TELEPORT_TOP_RIGHT}},
    // Bottom left:
    {  MOD ,              XK_b,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_LEFT}},
    // Bottom right:
    {  MOD ,              XK_n,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_RIGHT}},
    // Resize while keeping the window aspect
    {  MOD ,              XK_Home,       resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_GROW}},
    {  MOD ,              XK_End,        resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_SHRINK}},
    // Full screen window without borders
    {  MOD ,              XK_f,          maximize,          {.i=TWOBWM_FULLSCREEN}},
    //Full screen window without borders overiding offsets
    {  MOD |SHIFT ,       XK_f,          maximize,          {.i=TWOBWM_FULLSCREEN_OVERRIDE_OFFSETS}},
    // Maximize vertically
    {  MOD ,              XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_VERTICALLY}},
    // Maximize horizontally
    {  MOD |SHIFT,        XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_HORIZONTALLY}},
    // Maximize and move
    // vertically left
    {  MOD |SHIFT,        XK_y,          maxhalf,           {.i=TWOBWM_MAXHALF_VERTICAL_LEFT}},
    // vertically right
    {  MOD |SHIFT,        XK_u,          maxhalf,           {.i=TWOBWM_MAXHALF_VERTICAL_RIGHT}},
    // horizontally left
    {  MOD |SHIFT,        XK_b,          maxhalf,           {.i=TWOBWM_MAXHALF_HORIZONTAL_BOTTOM}},
    // horizontally right
    {  MOD |SHIFT,        XK_n,          maxhalf,           {.i=TWOBWM_MAXHALF_HORIZONTAL_TOP}},
    //fold half vertically
    {  MOD |SHIFT|CONTROL,XK_y,          maxhalf,           {.i=TWOBWM_MAXHALF_FOLD_VERTICAL}},
    //fold half horizontally
    {  MOD |SHIFT|CONTROL,XK_b,          maxhalf,           {.i=TWOBWM_MAXHALF_FOLD_HORIZONTAL}},
    //unfold vertically
    {  MOD |SHIFT|CONTROL,XK_u,          maxhalf,           {.i=TWOBWM_MAXHALF_UNFOLD_VERTICAL}},
    //unfold horizontally
    {  MOD |SHIFT|CONTROL,XK_n,          maxhalf,           {.i=TWOBWM_MAXHALF_UNFOLD_HORIZONTAL}},
    // Next/Previous screen
    {  MOD ,              XK_comma,      changescreen,      {.i=TWOBWM_NEXT_SCREEN}},
    {  MOD ,              XK_period,     changescreen,      {.i=TWOBWM_PREVIOUS_SCREEN}},
    // Raise or lower a window
    {  MOD ,              XK_r,          raiseorlower,      {}},
    // Next/Previous workspace
    // {  MOD ,              XK_v,          nextworkspace,     {}},
    // {  MOD ,              XK_c,          prevworkspace,     {}},
    // Move to Next/Previous workspace
    {  MOD |SHIFT ,       XK_v,          sendtonextworkspace,{}},
    {  MOD |SHIFT ,       XK_c,          sendtoprevworkspace,{}},
    // Iconify the window
    {  MOD ,              XK_l,          hide,              {}},
    //Make the window unkillable
    // {  MOD |SHIFT ,       XK_u,          unkillable,        {}},
    // Make the window appear always on top
    // {  MOD,               XK_i,          always_on_top,     {}},
    // Make the window stay on all workspaces
    {  MOD ,              XK_x,          fix,               {}},
    // Move the cursor
    // {  MOD ,              XK_Up,         cursor_move,       {.i=TWOBWM_CURSOR_UP_SLOW}},
    // {  MOD ,              XK_Down,       cursor_move,       {.i=TWOBWM_CURSOR_DOWN_SLOW}},
    // {  MOD ,              XK_Right,      cursor_move,       {.i=TWOBWM_CURSOR_RIGHT_SLOW}},
    // {  MOD ,              XK_Left,       cursor_move,       {.i=TWOBWM_CURSOR_LEFT_SLOW}},
    // Move the cursor faster
    // {  MOD |SHIFT,        XK_Up,         cursor_move,       {.i=TWOBWM_CURSOR_UP}},
    // {  MOD |SHIFT,        XK_Down,       cursor_move,       {.i=TWOBWM_CURSOR_DOWN}},
    // {  MOD |SHIFT,        XK_Right,      cursor_move,       {.i=TWOBWM_CURSOR_RIGHT}},
    // {  MOD |SHIFT,        XK_Left,       cursor_move,       {.i=TWOBWM_CURSOR_LEFT}},
    // Start programs
    {  MOD ,              XK_Return,     start,             {.com = urxvt}},
    {  MOD |SHIFT,        XK_Return,     start,             {.com = sakura}},
    {  MOD ,              XK_z,          start,             {.com = rofi}},
    {  MOD ,              XK_d,          start,             {.com = dmenu}},
    {  MOD ,              XK_w,          start,             {.com = draw}},
    {  MOD |SHIFT,        XK_w,          start,             {.com = std}},
    {  MOD ,              XK_i,          start,             {.com = wald}},
    {  MOD ,              XK_c,          start,             {.com = wall}},
    {  MOD ,              XK_ccedilla,   start,             {.com = lock}},
    // Misc
    {  MOD ,              XK_F1,         start,             {.com = date} },
    {  MOD ,              XK_F2,         start,             {.com = bat} },
    // Brightness Keys
    {  MOD ,              XK_F10,        start,             {.com = brightup} },
    {  MOD ,              XK_F9,         start,             {.com = brightdown} },
    // Volume Keys
    {  MOD ,              XK_F11,        start,             {.com = voldown} },
    {  MOD ,              XK_F12,        start,             {.com = volup} },
    // Exit or restart 2bwm
    {  MOD |SHIFT,        XK_e,          twobwm_exit,       {.i=0}},
    {  MOD |SHIFT,        XK_r,          twobwm_restart,    {.i=0}},
    {  MOD ,              XK_space,      halfandcentered,   {.i=0}},
    // Change current workspace
       DESKTOPCHANGE(     XK_ampersand,                     0)
       DESKTOPCHANGE(     XK_eacute,                        1)
       DESKTOPCHANGE(     XK_quotedbl,                      2)
       DESKTOPCHANGE(     XK_apostrophe,                    3)
       DESKTOPCHANGE(     XK_parenleft,                     4)
       DESKTOPCHANGE(     XK_minus,                         5)
       DESKTOPCHANGE(     XK_egrave,                        6)
       DESKTOPCHANGE(     XK_underscore,                    7)
    // DESKTOPCHANGE(     XK_ccedilla,                      8)
    // DESKTOPCHANGE(     XK_agrave,                        9)
};
// the last argument makes it a root window only event
static Button buttons[] = {
    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}, false},
    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}, false},
    {  0          ,XCB_BUTTON_INDEX_3,     start,         {.com = menucmd}, true},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}, false},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}, false},
    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}, false},
    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}, false}
};

