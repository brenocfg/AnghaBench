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
struct clock_event_device {int features; int /*<<< orphan*/  event_handler; } ;
struct TYPE_2__ {int mode; struct clock_event_device* evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int CLOCK_EVT_FEAT_HRTIMER ; 
#define  TICKDEV_MODE_ONESHOT 129 
#define  TICKDEV_MODE_PERIODIC 128 
 int /*<<< orphan*/  clockevents_shutdown (struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tick_broadcast_clear_oneshot (int) ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_lock ; 
 int /*<<< orphan*/  tick_broadcast_mask ; 
 int /*<<< orphan*/  tick_broadcast_on ; 
 int /*<<< orphan*/  tick_broadcast_setup_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_broadcast_start_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_device_is_functional (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_device_setup_broadcast_func (struct clock_event_device*) ; 
 int /*<<< orphan*/  tick_handle_periodic ; 

int tick_device_uses_broadcast(struct clock_event_device *dev, int cpu)
{
	struct clock_event_device *bc = tick_broadcast_device.evtdev;
	unsigned long flags;
	int ret = 0;

	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);

	/*
	 * Devices might be registered with both periodic and oneshot
	 * mode disabled. This signals, that the device needs to be
	 * operated from the broadcast device and is a placeholder for
	 * the cpu local device.
	 */
	if (!tick_device_is_functional(dev)) {
		dev->event_handler = tick_handle_periodic;
		tick_device_setup_broadcast_func(dev);
		cpumask_set_cpu(cpu, tick_broadcast_mask);
		if (tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC)
			tick_broadcast_start_periodic(bc);
		else
			tick_broadcast_setup_oneshot(bc);
		ret = 1;
	} else {
		/*
		 * Clear the broadcast bit for this cpu if the
		 * device is not power state affected.
		 */
		if (!(dev->features & CLOCK_EVT_FEAT_C3STOP))
			cpumask_clear_cpu(cpu, tick_broadcast_mask);
		else
			tick_device_setup_broadcast_func(dev);

		/*
		 * Clear the broadcast bit if the CPU is not in
		 * periodic broadcast on state.
		 */
		if (!cpumask_test_cpu(cpu, tick_broadcast_on))
			cpumask_clear_cpu(cpu, tick_broadcast_mask);

		switch (tick_broadcast_device.mode) {
		case TICKDEV_MODE_ONESHOT:
			/*
			 * If the system is in oneshot mode we can
			 * unconditionally clear the oneshot mask bit,
			 * because the CPU is running and therefore
			 * not in an idle state which causes the power
			 * state affected device to stop. Let the
			 * caller initialize the device.
			 */
			tick_broadcast_clear_oneshot(cpu);
			ret = 0;
			break;

		case TICKDEV_MODE_PERIODIC:
			/*
			 * If the system is in periodic mode, check
			 * whether the broadcast device can be
			 * switched off now.
			 */
			if (cpumask_empty(tick_broadcast_mask) && bc)
				clockevents_shutdown(bc);
			/*
			 * If we kept the cpu in the broadcast mask,
			 * tell the caller to leave the per cpu device
			 * in shutdown state. The periodic interrupt
			 * is delivered by the broadcast device, if
			 * the broadcast device exists and is not
			 * hrtimer based.
			 */
			if (bc && !(bc->features & CLOCK_EVT_FEAT_HRTIMER))
				ret = cpumask_test_cpu(cpu, tick_broadcast_mask);
			break;
		default:
			break;
		}
	}
	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
	return ret;
}