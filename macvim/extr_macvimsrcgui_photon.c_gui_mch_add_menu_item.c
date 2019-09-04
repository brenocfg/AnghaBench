#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  priority; void* id; int /*<<< orphan*/  submenu_id; struct TYPE_8__* actext; struct TYPE_8__* dname; int /*<<< orphan*/  name; struct TYPE_8__* parent; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  TYPE_1__ char_u ;
typedef  int /*<<< orphan*/  PtArg_t ;

/* Variables and functions */
 int MB_LEN_MAX ; 
 TYPE_1__ NUL ; 
 int /*<<< orphan*/  PtAddCallback (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* PtCreateWidget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtMenuButton ; 
 int /*<<< orphan*/  PtSeparator ; 
 int /*<<< orphan*/  PtSetArg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_ACCEL_KEY ; 
 int /*<<< orphan*/  Pt_ARG_ACCEL_TEXT ; 
 int /*<<< orphan*/  Pt_ARG_POINTER ; 
 int /*<<< orphan*/  Pt_ARG_TEXT_STRING ; 
 int /*<<< orphan*/  Pt_CB_ACTIVATE ; 
 int /*<<< orphan*/  gui_ph_handle_menu ; 
 int /*<<< orphan*/  gui_ph_position_menu (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ menu_is_separator (int /*<<< orphan*/ ) ; 
 TYPE_1__* vim_strchr (int /*<<< orphan*/ ,char) ; 

void
gui_mch_add_menu_item(vimmenu_T *menu, int index)
{
    vimmenu_T	*parent = menu->parent;
    char_u	*accel_key;
    char_u	mnemonic_str[MB_LEN_MAX];
    int	    n;
    PtArg_t args[13];

    n = 0;
    PtSetArg(&args[ n++ ], Pt_ARG_POINTER, menu, 0);

#ifdef FEAT_TOOLBAR
    if (menu_is_toolbar(parent->name))
    {
	if (menu_is_separator(menu->name))
	{
	    PtSetArg(&args[ n++ ], Pt_ARG_SEP_FLAGS,
		    Pt_SEP_VERTICAL, Pt_SEP_ORIENTATION);
	    PtSetArg(&args[ n++ ], Pt_ARG_SEP_TYPE, Pt_ETCHED_IN, 0);
	    PtSetArg(&args[ n++ ], Pt_ARG_ANCHOR_FLAGS,
		    Pt_TRUE, Pt_ANCHOR_TOP_BOTTOM);
	    PtSetArg(&args[ n++ ], Pt_ARG_WIDTH, 2, 0);
	    menu->id = PtCreateWidget(PtSeparator, gui.vimToolBar, n, args);
	}
	else
	{
	    if (strstr((const char *) p_toolbar, "text") != NULL)
	    {
		PtSetArg(&args[ n++ ], Pt_ARG_BALLOON_POSITION,
			Pt_BALLOON_BOTTOM, 0);
		PtSetArg(&args[ n++ ], Pt_ARG_TEXT_STRING, menu->dname, 0);
		PtSetArg(&args[ n++ ], Pt_ARG_TEXT_FONT, "TextFont08", 0);
	    }
	    if ((strstr((const char *) p_toolbar, "icons") != NULL) &&
		    (gui_ph_toolbar_images != NULL))
	    {
		PtSetArg(&args[ n++ ], Pt_ARG_LABEL_IMAGE,
			gui_ph_toolbar_find_icon(menu), 0);
		PtSetArg(&args[ n++ ], Pt_ARG_LABEL_TYPE, Pt_TEXT_IMAGE, 0);
		PtSetArg(&args[ n++ ], Pt_ARG_TEXT_IMAGE_SPACING, 0, 0);
	    }
	    if (strstr((const char *) p_toolbar, "tooltips") != NULL)
	    {
		PtSetArg(&args[ n++ ], Pt_ARG_LABEL_BALLOON,
			gui_ph_show_tooltip, 0);
		PtSetArg(&args[ n++ ], Pt_ARG_LABEL_FLAGS,
			Pt_TRUE, Pt_SHOW_BALLOON);
	    }
	    PtSetArg(&args[ n++ ], Pt_ARG_MARGIN_HEIGHT, 1, 0);
	    PtSetArg(&args[ n++ ], Pt_ARG_MARGIN_WIDTH, 1, 0);
	    PtSetArg(&args[ n++ ], Pt_ARG_FLAGS, Pt_FALSE,
		    Pt_HIGHLIGHTED | Pt_GETS_FOCUS);
	    PtSetArg(&args[ n++ ], Pt_ARG_FILL_COLOR, Pg_TRANSPARENT, 0);
	    menu->id = PtCreateWidget(PtButton, gui.vimToolBar, n, args);

	    PtAddCallback(menu->id, Pt_CB_ACTIVATE, gui_ph_handle_menu, menu);
	}
	/* Update toolbar if it's open */
	if (PtWidgetIsRealized(gui.vimToolBar))
	    PtRealizeWidget(menu->id);
    }
    else
#endif
	if (menu_is_separator(menu->name))
    {
	menu->id = PtCreateWidget(PtSeparator, parent->submenu_id, n, args);
    }
    else
    {
	accel_key = vim_strchr(menu->name, '&');
	if (accel_key != NULL)
	{
	    mnemonic_str[0] = accel_key[1];
	    mnemonic_str[1] = NUL;
	}

	PtSetArg(&args[ n++ ], Pt_ARG_TEXT_STRING, menu->dname, 0);
	if (accel_key != NULL)
	    PtSetArg(&args[ n++ ], Pt_ARG_ACCEL_KEY, mnemonic_str,
		    0);

	PtSetArg(&args[ n++ ], Pt_ARG_ACCEL_TEXT, menu->actext, 0);

	menu->id = PtCreateWidget(PtMenuButton, parent->submenu_id, n, args);

	PtAddCallback(menu->id, Pt_CB_ACTIVATE, gui_ph_handle_menu, menu);

#ifdef USE_PANEL_GROUP
	if (gui_ph_is_buffer_item(menu, parent) == TRUE)
	{
	    PtAddCallback(menu->id, Pt_CB_DESTROYED,
		    gui_ph_handle_buffer_remove, menu);
	    gui_ph_pg_add_buffer(menu->dname);
	}
#endif
    }

    gui_ph_position_menu(menu->id, menu->priority);
}