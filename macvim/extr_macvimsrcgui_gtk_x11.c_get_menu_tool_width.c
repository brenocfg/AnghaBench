#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static int
get_menu_tool_width(void)
{
    int width = 0;

#ifdef FEAT_GUI_GNOME /* these are never vertical without GNOME */
# ifdef FEAT_MENU
    width += get_item_dimensions(gui.menubar, GTK_ORIENTATION_VERTICAL);
# endif
# ifdef FEAT_TOOLBAR
    width += get_item_dimensions(gui.toolbar, GTK_ORIENTATION_VERTICAL);
# endif
# ifdef FEAT_GUI_TABLINE
    if (gui.tabline != NULL)
	width += get_item_dimensions(gui.tabline, GTK_ORIENTATION_VERTICAL);
# endif
#endif

    return width;
}