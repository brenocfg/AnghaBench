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
struct perf_event {int pending_disable; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 

void perf_event_disable_inatomic(struct perf_event *event)
{
	event->pending_disable = 1;
	irq_work_queue(&event->pending);
}