#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int border_offset; int border_width; int /*<<< orphan*/ * vimToolBar; int /*<<< orphan*/ * vimToolBarGroup; int /*<<< orphan*/ * vimMenuBar; int /*<<< orphan*/ * vimWindow; int /*<<< orphan*/ * vimTextArea; int /*<<< orphan*/ * vimContainer; int /*<<< orphan*/ * vimPanelGroup; int /*<<< orphan*/ * event_buffer; } ;
struct TYPE_5__ {int member_0; int member_1; int w; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PtArg_t ;
typedef  TYPE_1__ PhPoint_t ;
typedef  int /*<<< orphan*/  PhEvent_t ;
typedef  TYPE_2__ PhDim_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BUFFER_SIZE ; 
 int FAIL ; 
 int /*<<< orphan*/  GO_MENUS ; 
 int /*<<< orphan*/  GO_TOOLBAR ; 
 int GUI_PH_MARGIN ; 
 int GUI_PH_MOUSE_TYPE ; 
 int OK ; 
 int Ph_EV_BUT_PRESS ; 
 int Ph_EV_BUT_RELEASE ; 
 int Ph_EV_KEY ; 
 int Ph_EV_PTR_MOTION_BUTTON ; 
 int Ph_WM_CLOSE ; 
 int Ph_WM_FOCUS ; 
 int Ph_WM_RESIZE ; 
 int /*<<< orphan*/  PtAddCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtAddEventHandler (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* PtCreateWidget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtMenuBar ; 
 int /*<<< orphan*/  PtPane ; 
 int /*<<< orphan*/  PtPanelGroup ; 
 int /*<<< orphan*/  PtRaw ; 
 int /*<<< orphan*/  PtSetArg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PtTimer ; 
 int /*<<< orphan*/  PtToolbar ; 
 int /*<<< orphan*/  PtToolbarGroup ; 
 int /*<<< orphan*/  PtWindow ; 
 int Pt_ALL ; 
 int Pt_ANCHOR_ALL ; 
 int Pt_ANCHOR_LEFT_RIGHT ; 
 int /*<<< orphan*/  Pt_ARG_ANCHOR_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_BASIC_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_BEVEL_WIDTH ; 
 int /*<<< orphan*/  Pt_ARG_CONTAINER_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_CURSOR_COLOR ; 
 int /*<<< orphan*/  Pt_ARG_CURSOR_TYPE ; 
 int /*<<< orphan*/  Pt_ARG_DIM ; 
 int /*<<< orphan*/  Pt_ARG_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_MARGIN_HEIGHT ; 
 int /*<<< orphan*/  Pt_ARG_MARGIN_WIDTH ; 
 int /*<<< orphan*/  Pt_ARG_PG_PANEL_TITLES ; 
 int /*<<< orphan*/  Pt_ARG_POS ; 
 int /*<<< orphan*/  Pt_ARG_RAW_DRAW_F ; 
 int /*<<< orphan*/  Pt_ARG_RESIZE_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_WIDTH ; 
 int /*<<< orphan*/  Pt_ARG_WINDOW_MANAGED_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_WINDOW_NOTIFY_FLAGS ; 
 int Pt_AUTO_EXTENT ; 
 int /*<<< orphan*/  Pt_CB_GOT_FOCUS ; 
 int /*<<< orphan*/  Pt_CB_LOST_FOCUS ; 
 int /*<<< orphan*/  Pt_CB_PG_PANEL_SWITCHING ; 
 int /*<<< orphan*/  Pt_CB_RESIZE ; 
 int /*<<< orphan*/  Pt_CB_TIMER_ACTIVATE ; 
 int /*<<< orphan*/  Pt_CB_WINDOW ; 
 int /*<<< orphan*/  Pt_CB_WINDOW_OPENING ; 
 int Pt_DELAY_REALIZE ; 
 int /*<<< orphan*/ * Pt_DFLT_PARENT ; 
 int Pt_FALSE ; 
 int Pt_GETS_FOCUS ; 
 int Pt_HIGHLIGHTED ; 
 int Pt_IS_ANCHORED ; 
 int Pt_RESIZE_Y_AS_REQUIRED ; 
 int Pt_TOP_ANCHORED_TOP ; 
 int Pt_TRUE ; 
 int /*<<< orphan*/  PxTranslateSet (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charset_translate ; 
 int /*<<< orphan*/  empty_title ; 
 TYPE_3__ gui ; 
 int /*<<< orphan*/  gui_ph_handle_focus ; 
 int /*<<< orphan*/  gui_ph_handle_keyboard ; 
 int /*<<< orphan*/  gui_ph_handle_menu_resize ; 
 int /*<<< orphan*/  gui_ph_handle_mouse ; 
 int /*<<< orphan*/  gui_ph_handle_pg_change ; 
 int gui_ph_handle_raw_draw ; 
 int /*<<< orphan*/  gui_ph_handle_timer_cursor ; 
 int /*<<< orphan*/  gui_ph_handle_timer_timeout ; 
 int /*<<< orphan*/  gui_ph_handle_window_cb ; 
 int /*<<< orphan*/  gui_ph_handle_window_open ; 
 int gui_ph_mouse_color ; 
 int /*<<< orphan*/  gui_ph_pane_resize ; 
 int /*<<< orphan*/ * gui_ph_timer_cursor ; 
 int /*<<< orphan*/ * gui_ph_timer_timeout ; 
 int /*<<< orphan*/  p_go ; 
 int /*<<< orphan*/  vim_strchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gui_mch_init(void)
{
    PtArg_t args[10];
    int	    flags = 0, n = 0;

    PhDim_t	window_size = {100, 100}; /* Arbitrary values */
    PhPoint_t	pos = {0, 0};

    gui.event_buffer = (PhEvent_t *) alloc(EVENT_BUFFER_SIZE);
    if (gui.event_buffer == NULL)
	return FAIL;

    /* Get a translation so we can convert from ISO Latin-1 to UTF */
    charset_translate = PxTranslateSet(NULL, "latin1");

    /* The +2 is for the 1 pixel dark line on each side */
    gui.border_offset = gui.border_width = GUI_PH_MARGIN + 2;

    /* Handle close events ourselves */
    PtSetArg(&args[ n++ ], Pt_ARG_WINDOW_MANAGED_FLAGS, Pt_FALSE, Ph_WM_CLOSE);
    PtSetArg(&args[ n++ ], Pt_ARG_WINDOW_NOTIFY_FLAGS, Pt_TRUE,
	    Ph_WM_CLOSE | Ph_WM_RESIZE | Ph_WM_FOCUS);
    PtSetArg(&args[ n++ ], Pt_ARG_DIM, &window_size, 0);
    gui.vimWindow = PtCreateWidget(PtWindow, NULL, n, args);
    if (gui.vimWindow == NULL)
	return FAIL;

    PtAddCallback(gui.vimWindow, Pt_CB_WINDOW, gui_ph_handle_window_cb, NULL);
    PtAddCallback(gui.vimWindow, Pt_CB_WINDOW_OPENING,
	    gui_ph_handle_window_open, NULL);

    n = 0;
    PtSetArg(&args[ n++ ], Pt_ARG_ANCHOR_FLAGS, Pt_ANCHOR_ALL, Pt_IS_ANCHORED);
    PtSetArg(&args[ n++ ], Pt_ARG_DIM, &window_size, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_POS, &pos, 0);

#ifdef USE_PANEL_GROUP
    /* Put in a temporary place holder title */
    PtSetArg(&args[ n++ ], Pt_ARG_PG_PANEL_TITLES, &empty_title, 1);

    gui.vimPanelGroup = PtCreateWidget(PtPanelGroup, gui.vimWindow, n, args);
    if (gui.vimPanelGroup == NULL)
	return FAIL;

    PtAddCallback(gui.vimPanelGroup, Pt_CB_PG_PANEL_SWITCHING,
	    gui_ph_handle_pg_change, NULL);
#else
    /* Turn off all edge decorations */
    PtSetArg(&args[ n++ ], Pt_ARG_BASIC_FLAGS, Pt_FALSE, Pt_ALL);
    PtSetArg(&args[ n++ ], Pt_ARG_BEVEL_WIDTH, 0, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_MARGIN_WIDTH, 0, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_MARGIN_HEIGHT, 0, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_CONTAINER_FLAGS, Pt_TRUE, Pt_AUTO_EXTENT);

    gui.vimContainer = PtCreateWidget(PtPane, gui.vimWindow, n, args);
    if (gui.vimContainer == NULL)
	return FAIL;

    PtAddCallback(gui.vimContainer, Pt_CB_RESIZE, gui_ph_pane_resize, NULL);
#endif

    /* Size for the text area is set in gui_mch_set_text_area_pos */
    n = 0;

    PtSetArg(&args[ n++ ], Pt_ARG_RAW_DRAW_F, gui_ph_handle_raw_draw, 1);
    PtSetArg(&args[ n++ ], Pt_ARG_BEVEL_WIDTH, GUI_PH_MARGIN, 0);
    /*
     * Using focus render also causes the whole widget to be redrawn
     * whenever it changes focus, which is very annoying :p
     */
    PtSetArg(&args[ n++ ], Pt_ARG_FLAGS, Pt_TRUE,
	    Pt_GETS_FOCUS | Pt_HIGHLIGHTED);
#ifndef FEAT_MOUSESHAPE
    PtSetArg(&args[ n++ ], Pt_ARG_CURSOR_TYPE, GUI_PH_MOUSE_TYPE, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_CURSOR_COLOR, gui_ph_mouse_color, 0);
#endif

    gui.vimTextArea = PtCreateWidget(PtRaw, Pt_DFLT_PARENT, n, args);
    if (gui.vimTextArea == NULL)
	return FAIL;

    /* TODO: use PtAddEventHandlers instead? */
    /* Not using Ph_EV_BUT_REPEAT because vim wouldn't use it anyway */
    PtAddEventHandler(gui.vimTextArea,
	    Ph_EV_BUT_PRESS | Ph_EV_BUT_RELEASE | Ph_EV_PTR_MOTION_BUTTON,
	    gui_ph_handle_mouse, NULL);
    PtAddEventHandler(gui.vimTextArea, Ph_EV_KEY,
	    gui_ph_handle_keyboard, NULL);
    PtAddCallback(gui.vimTextArea, Pt_CB_GOT_FOCUS,
	    gui_ph_handle_focus, NULL);
    PtAddCallback(gui.vimTextArea, Pt_CB_LOST_FOCUS,
	    gui_ph_handle_focus, NULL);

    /*
     * Now that the text area widget has been created, set up the colours,
     * which wil call PtSetResource from gui_mch_new_colors
     */

    /*
     * Create the two timers, not as accurate as using the kernel timer
     * functions, but good enough
     */
    gui_ph_timer_cursor  = PtCreateWidget(PtTimer, gui.vimWindow, 0, NULL);
    if (gui_ph_timer_cursor == NULL)
	return FAIL;

    gui_ph_timer_timeout = PtCreateWidget(PtTimer, gui.vimWindow, 0, NULL);
    if (gui_ph_timer_timeout == NULL)
	return FAIL;

    PtAddCallback(gui_ph_timer_cursor,  Pt_CB_TIMER_ACTIVATE,
	    gui_ph_handle_timer_cursor, NULL);
    PtAddCallback(gui_ph_timer_timeout, Pt_CB_TIMER_ACTIVATE,
	    gui_ph_handle_timer_timeout, NULL);

#ifdef FEAT_MENU
    n = 0;
    PtSetArg(&args[ n++ ], Pt_ARG_WIDTH, window_size.w, 0);
    PtSetArg(&args[ n++ ], Pt_ARG_ANCHOR_FLAGS, Pt_ANCHOR_LEFT_RIGHT,
	    Pt_IS_ANCHORED);
    gui.vimToolBarGroup = PtCreateWidget(PtToolbarGroup, gui.vimWindow,
	    n, args);
    if (gui.vimToolBarGroup == NULL)
	return FAIL;

    PtAddCallback(gui.vimToolBarGroup, Pt_CB_RESIZE,
	    gui_ph_handle_menu_resize, NULL);

    n = 0;
    flags = 0;
    PtSetArg(&args[ n++ ], Pt_ARG_WIDTH, window_size.w, 0);
    if (! vim_strchr(p_go, GO_MENUS))
    {
	flags |= Pt_DELAY_REALIZE;
	PtSetArg(&args[ n++ ], Pt_ARG_FLAGS, Pt_TRUE, flags);
    }
    gui.vimMenuBar = PtCreateWidget(PtMenuBar, gui.vimToolBarGroup, n, args);
    if (gui.vimMenuBar == NULL)
	return FAIL;

# ifdef FEAT_TOOLBAR
    n = 0;

    PtSetArg(&args[ n++ ], Pt_ARG_ANCHOR_FLAGS,
	    Pt_ANCHOR_LEFT_RIGHT |Pt_TOP_ANCHORED_TOP, Pt_IS_ANCHORED);
    PtSetArg(&args[ n++ ], Pt_ARG_RESIZE_FLAGS, Pt_TRUE,
	    Pt_RESIZE_Y_AS_REQUIRED);
    PtSetArg(&args[ n++ ], Pt_ARG_WIDTH, window_size.w, 0);

    flags = Pt_GETS_FOCUS;
    if (! vim_strchr(p_go, GO_TOOLBAR))
	flags |= Pt_DELAY_REALIZE;

    PtSetArg(&args[ n++ ], Pt_ARG_FLAGS, Pt_DELAY_REALIZE, flags);

    gui.vimToolBar = PtCreateWidget(PtToolbar, gui.vimToolBarGroup, n, args);
    if (gui.vimToolBar == NULL)
	return FAIL;

    /*
     * Size for the toolbar is fetched in gui_mch_show_toolbar, after
     * the buttons have been added and the toolbar has resized it's height
     * for the buttons to fit
     */
# endif

#endif

    return OK;
}