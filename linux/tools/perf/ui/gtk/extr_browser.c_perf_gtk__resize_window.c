#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int width; int height; } ;
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ GtkWidget ;
typedef  int /*<<< orphan*/  GdkScreen ;
typedef  TYPE_2__ GdkRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int gdk_screen_get_monitor_at_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_screen_get_monitor_geometry (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * gtk_widget_get_screen (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_window_resize (int /*<<< orphan*/ ,int,int) ; 

void perf_gtk__resize_window(GtkWidget *window)
{
	GdkRectangle rect;
	GdkScreen *screen;
	int monitor;
	int height;
	int width;

	screen = gtk_widget_get_screen(window);

	monitor = gdk_screen_get_monitor_at_window(screen, window->window);

	gdk_screen_get_monitor_geometry(screen, monitor, &rect);

	width	= rect.width * 3 / 4;
	height	= rect.height * 3 / 4;

	gtk_window_resize(GTK_WINDOW(window), width, height);
}