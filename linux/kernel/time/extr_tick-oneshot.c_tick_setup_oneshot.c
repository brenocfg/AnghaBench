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
struct clock_event_device {void (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_STATE_ONESHOT ; 
 int /*<<< orphan*/  clockevents_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 

void tick_setup_oneshot(struct clock_event_device *newdev,
			void (*handler)(struct clock_event_device *),
			ktime_t next_event)
{
	newdev->event_handler = handler;
	clockevents_switch_state(newdev, CLOCK_EVT_STATE_ONESHOT);
	clockevents_program_event(newdev, next_event, true);
}