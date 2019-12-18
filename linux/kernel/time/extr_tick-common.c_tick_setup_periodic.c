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
struct clock_event_device {int features; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_PERIODIC ; 
 int /*<<< orphan*/  CLOCK_EVT_STATE_ONESHOT ; 
 int /*<<< orphan*/  CLOCK_EVT_STATE_PERIODIC ; 
 int /*<<< orphan*/  clockevents_program_event (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clockevents_switch_state (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_lock ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tick_broadcast_oneshot_active () ; 
 int /*<<< orphan*/  tick_device_is_functional (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_next_period ; 
 int /*<<< orphan*/  tick_period ; 
 int /*<<< orphan*/  tick_set_periodic_handler (struct clock_event_device*,int) ; 

void tick_setup_periodic(struct clock_event_device *dev, int broadcast)
{
	tick_set_periodic_handler(dev, broadcast);

	/* Broadcast setup ? */
	if (!tick_device_is_functional(dev))
		return;

	if ((dev->features & CLOCK_EVT_FEAT_PERIODIC) &&
	    !tick_broadcast_oneshot_active()) {
		clockevents_switch_state(dev, CLOCK_EVT_STATE_PERIODIC);
	} else {
		unsigned int seq;
		ktime_t next;

		do {
			seq = read_seqbegin(&jiffies_lock);
			next = tick_next_period;
		} while (read_seqretry(&jiffies_lock, seq));

		clockevents_switch_state(dev, CLOCK_EVT_STATE_ONESHOT);

		for (;;) {
			if (!clockevents_program_event(dev, next, false))
				return;
			next = ktime_add(next, tick_period);
		}
	}
}