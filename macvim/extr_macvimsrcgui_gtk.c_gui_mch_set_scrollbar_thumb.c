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
struct TYPE_7__ {scalar_t__ handler_id; int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ scrollbar_T ;
typedef  int /*<<< orphan*/  gulong ;
struct TYPE_8__ {double lower; long value; long upper; long page_size; long page_increment; double step_increment; } ;
typedef  TYPE_2__ GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  GTK_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_adjustment_changed (TYPE_2__*) ; 
 TYPE_2__* gtk_range_get_adjustment (int /*<<< orphan*/ ) ; 

void
gui_mch_set_scrollbar_thumb(scrollbar_T *sb, long val, long size, long max)
{
    if (sb->id != NULL)
    {
	GtkAdjustment *adjustment;

	adjustment = gtk_range_get_adjustment(GTK_RANGE(sb->id));

	adjustment->lower = 0.0;
	adjustment->value = val;
	adjustment->upper = max + 1;
	adjustment->page_size = size;
	adjustment->page_increment = size < 3L ? 1L : size - 2L;
	adjustment->step_increment = 1.0;

	g_signal_handler_block(GTK_OBJECT(adjustment),
						      (gulong)sb->handler_id);
	gtk_adjustment_changed(adjustment);
	g_signal_handler_unblock(GTK_OBJECT(adjustment),
						      (gulong)sb->handler_id);
    }
}