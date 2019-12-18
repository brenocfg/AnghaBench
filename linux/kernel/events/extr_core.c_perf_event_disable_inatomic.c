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
struct perf_event {int /*<<< orphan*/  pending; int /*<<< orphan*/  pending_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void perf_event_disable_inatomic(struct perf_event *event)
{
	WRITE_ONCE(event->pending_disable, smp_processor_id());
	/* can fail, see perf_pending_event_disable() */
	irq_work_queue(&event->pending);
}