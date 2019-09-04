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
struct clock_event_device {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 scalar_t__ clockevent_state_detached (struct clock_event_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tick_cpu_device ; 

__attribute__((used)) static int __clockevents_try_unbind(struct clock_event_device *ced, int cpu)
{
	/* Fast track. Device is unused */
	if (clockevent_state_detached(ced)) {
		list_del_init(&ced->list);
		return 0;
	}

	return ced == per_cpu(tick_cpu_device, cpu).evtdev ? -EAGAIN : -EBUSY;
}