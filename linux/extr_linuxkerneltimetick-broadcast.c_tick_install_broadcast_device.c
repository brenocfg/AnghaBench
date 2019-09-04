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
struct clock_event_device {int features; int /*<<< orphan*/  event_handler; int /*<<< orphan*/  owner; } ;
struct TYPE_2__ {struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  clockevents_exchange_device (struct clock_event_device*,struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevents_handle_noop ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_mask ; 
 int /*<<< orphan*/  tick_broadcast_start_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_check_broadcast_device (struct clock_event_device*,struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_clock_notify () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

void tick_install_broadcast_device(struct clock_event_device *dev)
{
	struct clock_event_device *cur = tick_broadcast_device.evtdev;

	if (!tick_check_broadcast_device(cur, dev))
		return;

	if (!try_module_get(dev->owner))
		return;

	clockevents_exchange_device(cur, dev);
	if (cur)
		cur->event_handler = clockevents_handle_noop;
	tick_broadcast_device.evtdev = dev;
	if (!cpumask_empty(tick_broadcast_mask))
		tick_broadcast_start_periodic(dev);
	/*
	 * Inform all cpus about this. We might be in a situation
	 * where we did not switch to oneshot mode because the per cpu
	 * devices are affected by CLOCK_EVT_FEAT_C3STOP and the lack
	 * of a oneshot capable broadcast device. Without that
	 * notification the systems stays stuck in periodic mode
	 * forever.
	 */
	if (dev->features & CLOCK_EVT_FEAT_ONESHOT)
		tick_clock_notify();
}