#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tick_device {TYPE_2__* evtdev; } ;
struct clock_event_device {int /*<<< orphan*/  next_event; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (TYPE_2__*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  evtdev; } ;

/* Variables and functions */
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockevents_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct tick_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_lock ; 
 int /*<<< orphan*/  tick_cpu_device ; 
 int tick_do_periodic_broadcast () ; 
 int /*<<< orphan*/  tick_period ; 

__attribute__((used)) static void tick_handle_periodic_broadcast(struct clock_event_device *dev)
{
	struct tick_device *td = this_cpu_ptr(&tick_cpu_device);
	bool bc_local;

	raw_spin_lock(&tick_broadcast_lock);

	/* Handle spurious interrupts gracefully */
	if (clockevent_state_shutdown(tick_broadcast_device.evtdev)) {
		raw_spin_unlock(&tick_broadcast_lock);
		return;
	}

	bc_local = tick_do_periodic_broadcast();

	if (clockevent_state_oneshot(dev)) {
		ktime_t next = ktime_add(dev->next_event, tick_period);

		clockevents_program_event(dev, next, true);
	}
	raw_spin_unlock(&tick_broadcast_lock);

	/*
	 * We run the handler of the local cpu after dropping
	 * tick_broadcast_lock because the handler might deadlock when
	 * trying to switch to oneshot mode.
	 */
	if (bc_local)
		td->evtdev->event_handler(td->evtdev);
}