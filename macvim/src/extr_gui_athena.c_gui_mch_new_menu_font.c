#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  dname; struct TYPE_5__* next; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  scalar_t__ Widget ;
struct TYPE_6__ {int menu_height; int /*<<< orphan*/  dpy; int /*<<< orphan*/  menu_height_fixed; } ;
typedef  int Position ;
typedef  scalar_t__ Pixmap ;
typedef  int Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  RESIZE_VERT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XtNborderWidth ; 
 int /*<<< orphan*/  XtNheight ; 
 int /*<<< orphan*/  XtNvSpace ; 
 int /*<<< orphan*/  XtNwidth ; 
 int /*<<< orphan*/  XtVaGetValues (scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,...) ; 
 TYPE_4__ gui ; 
 scalar_t__ gui_athena_create_pullright_pixmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gui_mch_submenu_change (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_resize_shell (int,int) ; 
 int /*<<< orphan*/  gui_set_shellsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ menuBar ; 
 scalar_t__ menu_is_menubar (int /*<<< orphan*/ ) ; 
 scalar_t__ pullerBitmap ; 
 TYPE_1__* root_menu ; 
 int /*<<< orphan*/  ui_new_shellsize () ; 
 scalar_t__ vimShell ; 
 int xim_get_status_area_height () ; 

void
gui_mch_new_menu_font()
{
    Pixmap oldpuller = None;

    if (menuBar == (Widget)0)
	return;

    if (pullerBitmap != None)
    {
	oldpuller = pullerBitmap;
	pullerBitmap = gui_athena_create_pullright_pixmap(NULL);
    }
    gui_mch_submenu_change(root_menu, FALSE);

    {
	/* Iterate through the menubar menu items and get the height of
	 * each one.  The menu bar height is set to the maximum of all
	 * the heights.
	 */
	vimmenu_T *mp;
	int max_height = 9999;

	for (mp = root_menu; mp != NULL; mp = mp->next)
	{
	    if (menu_is_menubar(mp->dname))
	    {
		Dimension height;

		XtVaGetValues(mp->id,
			XtNheight, &height,
			NULL);
		if (height < max_height)
		    max_height = height;
	    }
	}
	if (max_height != 9999)
	{
	    /* Don't update the menu height when it was set at a fixed value */
	    if (!gui.menu_height_fixed)
	    {
		Dimension   space, border;

		XtVaGetValues(menuBar,
			XtNvSpace,	&space,
			XtNborderWidth, &border,
			NULL);
		gui.menu_height = max_height + 2 * (space + border);
	    }
	}
    }
    /* Now, to simulate the window being resized.  Only, this
     * will resize the window to it's current state.
     *
     * There has to be a better way, but I do not see one at this time.
     * (David Harrison)
     */
    {
	Position w, h;

	XtVaGetValues(vimShell,
		XtNwidth, &w,
		XtNheight, &h,
		NULL);
	gui_resize_shell(w, h
#ifdef FEAT_XIM
						- xim_get_status_area_height()
#endif
		     );
    }
    gui_set_shellsize(FALSE, TRUE, RESIZE_VERT);
    ui_new_shellsize();
    if (oldpuller != None)
	XFreePixmap(gui.dpy, oldpuller);
}