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
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {int /*<<< orphan*/  next_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_STATE_PERIODIC ; 
 int __clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevents_config (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int clockevents_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 

int __clockevents_update_freq(struct clock_event_device *dev, u32 freq)
{
	clockevents_config(dev, freq);

	if (clockevent_state_oneshot(dev))
		return clockevents_program_event(dev, dev->next_event, false);

	if (clockevent_state_periodic(dev))
		return __clockevents_switch_state(dev, CLOCK_EVT_STATE_PERIODIC);

	return 0;
}