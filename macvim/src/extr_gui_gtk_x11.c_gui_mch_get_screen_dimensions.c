#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mainwin; } ;
typedef  int /*<<< orphan*/  GdkScreen ;

/* Variables and functions */
 int /*<<< orphan*/ * gdk_screen_get_default () ; 
 int gdk_screen_get_height (int /*<<< orphan*/ *) ; 
 int gdk_screen_get_width (int /*<<< orphan*/ *) ; 
 int gdk_screen_height () ; 
 int gdk_screen_width () ; 
 scalar_t__ get_menu_tool_height () ; 
 scalar_t__ get_menu_tool_width () ; 
 int /*<<< orphan*/ * gtk_widget_get_screen (int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_widget_has_screen (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int p_ghr ; 

void
gui_mch_get_screen_dimensions(int *screen_w, int *screen_h)
{
#ifdef HAVE_GTK_MULTIHEAD
    GdkScreen* screen;

    if (gui.mainwin != NULL && gtk_widget_has_screen(gui.mainwin))
	screen = gtk_widget_get_screen(gui.mainwin);
    else
	screen = gdk_screen_get_default();

    *screen_w = gdk_screen_get_width(screen);
    *screen_h = gdk_screen_get_height(screen) - p_ghr;
#else
    *screen_w = gdk_screen_width();
    /* Subtract 'guiheadroom' from the height to allow some room for the
     * window manager (task list and window title bar). */
    *screen_h = gdk_screen_height() - p_ghr;
#endif

    /*
     * FIXME: dirty trick: Because the gui_get_base_height() doesn't include
     * the toolbar and menubar for GTK, we subtract them from the screen
     * height, so that the window size can be made to fit on the screen.
     * This should be completely changed later.
     */
    *screen_w -= get_menu_tool_width();
    *screen_h -= get_menu_tool_height();
}