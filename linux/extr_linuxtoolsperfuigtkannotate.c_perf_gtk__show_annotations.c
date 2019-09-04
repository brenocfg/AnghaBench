#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * main_window; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIN_POS_CENTER ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_gtk__deactivate_context (TYPE_1__**) ; 
 int /*<<< orphan*/  perf_gtk__is_active_context (TYPE_1__*) ; 
 int /*<<< orphan*/  perf_gtk__resize_window (int /*<<< orphan*/ *) ; 
 TYPE_1__* pgctx ; 

void perf_gtk__show_annotations(void)
{
	GtkWidget *window;

	if (!perf_gtk__is_active_context(pgctx))
		return;

	window = pgctx->main_window;
	gtk_widget_show_all(window);

	perf_gtk__resize_window(window);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	gtk_main();

	perf_gtk__deactivate_context(&pgctx);
}