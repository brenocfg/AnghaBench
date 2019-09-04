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
struct tick_device {int /*<<< orphan*/  mode; struct clock_event_device* evtdev; } ;
struct clock_event_device {int features; void (* event_handler ) (struct clock_event_device*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  CLOCK_EVT_STATE_ONESHOT ; 
 int EINVAL ; 
 int /*<<< orphan*/  TICKDEV_MODE_ONESHOT ; 
 int /*<<< orphan*/  clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct tick_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_broadcast_switch_to_oneshot () ; 
 int /*<<< orphan*/  tick_cpu_device ; 
 int /*<<< orphan*/  tick_device_is_functional (struct clock_event_device*) ; 

int tick_switch_to_oneshot(void (*handler)(struct clock_event_device *))
{
	struct tick_device *td = this_cpu_ptr(&tick_cpu_device);
	struct clock_event_device *dev = td->evtdev;

	if (!dev || !(dev->features & CLOCK_EVT_FEAT_ONESHOT) ||
		    !tick_device_is_functional(dev)) {

		pr_info("Clockevents: could not switch to one-shot mode:");
		if (!dev) {
			pr_cont(" no tick device\n");
		} else {
			if (!tick_device_is_functional(dev))
				pr_cont(" %s is not functional.\n", dev->name);
			else
				pr_cont(" %s does not support one-shot mode.\n",
					dev->name);
		}
		return -EINVAL;
	}

	td->mode = TICKDEV_MODE_ONESHOT;
	dev->event_handler = handler;
	clockevents_switch_state(dev, CLOCK_EVT_STATE_ONESHOT);
	tick_broadcast_switch_to_oneshot();
	return 0;
}