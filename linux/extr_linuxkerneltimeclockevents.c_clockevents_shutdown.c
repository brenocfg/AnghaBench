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
struct clock_event_device {int /*<<< orphan*/  next_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  KTIME_MAX ; 
 int /*<<< orphan*/  clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 

void clockevents_shutdown(struct clock_event_device *dev)
{
	clockevents_switch_state(dev, CLOCK_EVT_STATE_SHUTDOWN);
	dev->next_event = KTIME_MAX;
}