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
typedef  int /*<<< orphan*/  GdkDisplay ;

/* Variables and functions */
 scalar_t__ GTK_WIDGET_REALIZED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_beep () ; 
 int /*<<< orphan*/  gdk_display_beep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_display_get_default () ; 
 int /*<<< orphan*/ * gtk_widget_get_display (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 

void
gui_mch_beep(void)
{
#ifdef HAVE_GTK_MULTIHEAD
    GdkDisplay *display;

    if (gui.mainwin != NULL && GTK_WIDGET_REALIZED(gui.mainwin))
	display = gtk_widget_get_display(gui.mainwin);
    else
	display = gdk_display_get_default();

    if (display != NULL)
	gdk_display_beep(display);
#else
    gdk_beep();
#endif
}