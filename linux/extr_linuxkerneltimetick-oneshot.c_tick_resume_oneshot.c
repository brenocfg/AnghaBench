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
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  evtdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_STATE_ONESHOT ; 
 struct clock_event_device* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockevents_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 TYPE_1__ tick_cpu_device ; 

void tick_resume_oneshot(void)
{
	struct clock_event_device *dev = __this_cpu_read(tick_cpu_device.evtdev);

	clockevents_switch_state(dev, CLOCK_EVT_STATE_ONESHOT);
	clockevents_program_event(dev, ktime_get(), true);
}