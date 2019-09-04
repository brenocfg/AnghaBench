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
struct clock_event_device {int /*<<< orphan*/  list; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CLOCK_EVT_STATE_DETACHED ; 
 int /*<<< orphan*/  clockevent_state_detached (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevents_released ; 
 int /*<<< orphan*/  clockevents_shutdown (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void clockevents_exchange_device(struct clock_event_device *old,
				 struct clock_event_device *new)
{
	/*
	 * Caller releases a clock event device. We queue it into the
	 * released list and do a notify add later.
	 */
	if (old) {
		module_put(old->owner);
		clockevents_switch_state(old, CLOCK_EVT_STATE_DETACHED);
		list_del(&old->list);
		list_add(&old->list, &clockevents_released);
	}

	if (new) {
		BUG_ON(!clockevent_state_detached(new));
		clockevents_shutdown(new);
	}
}