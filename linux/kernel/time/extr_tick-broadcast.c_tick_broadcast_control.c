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
struct tick_device {struct clock_event_device* evtdev; } ;
struct clock_event_device {int features; } ;
typedef  enum tick_broadcast_mode { ____Placeholder_tick_broadcast_mode } tick_broadcast_mode ;
struct TYPE_2__ {scalar_t__ mode; struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int CLOCK_EVT_FEAT_HRTIMER ; 
 scalar_t__ TICKDEV_MODE_PERIODIC ; 
#define  TICK_BROADCAST_FORCE 130 
#define  TICK_BROADCAST_OFF 129 
#define  TICK_BROADCAST_ON 128 
 int /*<<< orphan*/  clockevents_shutdown (struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_and_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_and_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int smp_processor_id () ; 
 struct tick_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ tick_broadcast_device ; 
 int tick_broadcast_forced ; 
 int /*<<< orphan*/  tick_broadcast_lock ; 
 int /*<<< orphan*/  tick_broadcast_mask ; 
 int /*<<< orphan*/  tick_broadcast_on ; 
 int /*<<< orphan*/  tick_broadcast_setup_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_broadcast_start_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_cpu_device ; 
 int /*<<< orphan*/  tick_device_is_functional (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_setup_periodic (struct clock_event_device*,int /*<<< orphan*/ ) ; 

void tick_broadcast_control(enum tick_broadcast_mode mode)
{
	struct clock_event_device *bc, *dev;
	struct tick_device *td;
	int cpu, bc_stopped;
	unsigned long flags;

	/* Protects also the local clockevent device. */
	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);
	td = this_cpu_ptr(&tick_cpu_device);
	dev = td->evtdev;

	/*
	 * Is the device not affected by the powerstate ?
	 */
	if (!dev || !(dev->features & CLOCK_EVT_FEAT_C3STOP))
		goto out;

	if (!tick_device_is_functional(dev))
		goto out;

	cpu = smp_processor_id();
	bc = tick_broadcast_device.evtdev;
	bc_stopped = cpumask_empty(tick_broadcast_mask);

	switch (mode) {
	case TICK_BROADCAST_FORCE:
		tick_broadcast_forced = 1;
		/* fall through */
	case TICK_BROADCAST_ON:
		cpumask_set_cpu(cpu, tick_broadcast_on);
		if (!cpumask_test_and_set_cpu(cpu, tick_broadcast_mask)) {
			/*
			 * Only shutdown the cpu local device, if:
			 *
			 * - the broadcast device exists
			 * - the broadcast device is not a hrtimer based one
			 * - the broadcast device is in periodic mode to
			 *   avoid a hickup during switch to oneshot mode
			 */
			if (bc && !(bc->features & CLOCK_EVT_FEAT_HRTIMER) &&
			    tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC)
				clockevents_shutdown(dev);
		}
		break;

	case TICK_BROADCAST_OFF:
		if (tick_broadcast_forced)
			break;
		cpumask_clear_cpu(cpu, tick_broadcast_on);
		if (cpumask_test_and_clear_cpu(cpu, tick_broadcast_mask)) {
			if (tick_broadcast_device.mode ==
			    TICKDEV_MODE_PERIODIC)
				tick_setup_periodic(dev, 0);
		}
		break;
	}

	if (bc) {
		if (cpumask_empty(tick_broadcast_mask)) {
			if (!bc_stopped)
				clockevents_shutdown(bc);
		} else if (bc_stopped) {
			if (tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC)
				tick_broadcast_start_periodic(bc);
			else
				tick_broadcast_setup_oneshot(bc);
		}
	}
out:
	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
}