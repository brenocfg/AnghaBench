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
struct TYPE_2__ {int /*<<< orphan*/  starting; int /*<<< orphan*/ * menubar; int /*<<< orphan*/ * menubar_h; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET_VISIBLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  update_window_manager_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ using_gnome ; 

void
gui_mch_enable_menu(int showit)
{
    GtkWidget *widget;

# ifdef FEAT_GUI_GNOME
    if (using_gnome)
	widget = gui.menubar_h;
    else
# endif
	widget = gui.menubar;

    /* Do not disable the menu while starting up, otherwise F10 doesn't work. */
    if (!showit != !GTK_WIDGET_VISIBLE(widget) && !gui.starting)
    {
	if (showit)
	    gtk_widget_show(widget);
	else
	    gtk_widget_hide(widget);

	update_window_manager_hints(0, 0);
    }
}