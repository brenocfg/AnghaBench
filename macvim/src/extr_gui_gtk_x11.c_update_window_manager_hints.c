#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int char_height; int char_width; int /*<<< orphan*/  mainwin; } ;
struct TYPE_4__ {int width_inc; int height_inc; int base_width; int base_height; int min_width; int min_height; } ;
typedef  int GdkWindowHints ;
typedef  TYPE_1__ GdkGeometry ;

/* Variables and functions */
 int GDK_HINT_BASE_SIZE ; 
 int GDK_HINT_MIN_SIZE ; 
 int GDK_HINT_RESIZE_INC ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int MIN_COLUMNS ; 
 int MIN_LINES ; 
 scalar_t__ get_menu_tool_height () ; 
 scalar_t__ get_menu_tool_width () ; 
 int /*<<< orphan*/  gtk_window_set_geometry_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 TYPE_2__ gui ; 
 int gui_get_base_height () ; 
 int gui_get_base_width () ; 
 int init_window_hints_state ; 
 int tabline_height () ; 

__attribute__((used)) static void
update_window_manager_hints(int force_width, int force_height)
{
    static int old_width  = 0;
    static int old_height = 0;
    static int old_min_width  = 0;
    static int old_min_height = 0;
    static int old_char_width  = 0;
    static int old_char_height = 0;

    int width;
    int height;
    int min_width;
    int min_height;

    /* At start-up, don't try to set the hints until the initial
     * values have been used (those that dictate our initial size)
     * Let forced (i.e., correct) values through always.
     */
    if (!(force_width && force_height)  &&  init_window_hints_state > 0)
    {
	/* Don't do it! */
	init_window_hints_state = 2;
	return;
    }

    /* This also needs to be done when the main window isn't there yet,
     * otherwise the hints don't work. */
    width  = gui_get_base_width();
    height = gui_get_base_height();
# ifdef FEAT_MENU
    height += tabline_height() * gui.char_height;
# endif
    width  += get_menu_tool_width();
    height += get_menu_tool_height();

    /* GtkSockets use GtkPlug's [gui,mainwin] min-size hints to determine
     * their actual widget size.  When we set our size ourselves (e.g.,
     * 'set columns=' or init. -geom) we briefly set the min. to the size
     * we wish to be instead of the legitimate minimum so that we actually
     * resize correctly.
     */
    if (force_width && force_height)
    {
	min_width  = force_width;
	min_height = force_height;
    }
    else
    {
	min_width  = width  + MIN_COLUMNS * gui.char_width;
	min_height = height + MIN_LINES   * gui.char_height;
    }

    /* Avoid an expose event when the size didn't change. */
    if (width != old_width
	    || height != old_height
	    || min_width != old_min_width
	    || min_height != old_min_height
	    || gui.char_width != old_char_width
	    || gui.char_height != old_char_height)
    {
	GdkGeometry	geometry;
	GdkWindowHints	geometry_mask;

	geometry.width_inc   = gui.char_width;
	geometry.height_inc  = gui.char_height;
	geometry.base_width  = width;
	geometry.base_height = height;
	geometry.min_width   = min_width;
	geometry.min_height  = min_height;
	geometry_mask	     = GDK_HINT_BASE_SIZE|GDK_HINT_RESIZE_INC
			       |GDK_HINT_MIN_SIZE;
	/* Using gui.formwin as geometry widget doesn't work as expected
	 * with GTK+ 2 -- dunno why.  Presumably all the resizing hacks
	 * in Vim confuse GTK+. */
	gtk_window_set_geometry_hints(GTK_WINDOW(gui.mainwin), gui.mainwin,
				      &geometry, geometry_mask);
	old_width       = width;
	old_height      = height;
	old_min_width   = min_width;
	old_min_height  = min_height;
	old_char_width  = gui.char_width;
	old_char_height = gui.char_height;
    }
}