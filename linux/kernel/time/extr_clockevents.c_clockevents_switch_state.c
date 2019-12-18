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
struct clock_event_device {int mult; } ;
typedef  enum clock_event_state { ____Placeholder_clock_event_state } clock_event_state ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ __clockevents_switch_state (struct clock_event_device*,int) ; 
 int clockevent_get_state (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevent_set_state (struct clock_event_device*,int) ; 
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 

void clockevents_switch_state(struct clock_event_device *dev,
			      enum clock_event_state state)
{
	if (clockevent_get_state(dev) != state) {
		if (__clockevents_switch_state(dev, state))
			return;

		clockevent_set_state(dev, state);

		/*
		 * A nsec2cyc multiplicator of 0 is invalid and we'd crash
		 * on it, so fix it up and emit a warning:
		 */
		if (clockevent_state_oneshot(dev)) {
			if (WARN_ON(!dev->mult))
				dev->mult = 1;
		}
	}
}