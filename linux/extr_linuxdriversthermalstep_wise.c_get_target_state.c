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
struct thermal_instance {unsigned long target; unsigned long upper; unsigned long lower; int /*<<< orphan*/  initialized; struct thermal_cooling_device* cdev; } ;
struct thermal_cooling_device {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_cur_state ) (struct thermal_cooling_device*,unsigned long*) ;} ;

/* Variables and functions */
 unsigned long THERMAL_NO_TARGET ; 
#define  THERMAL_TREND_DROPPING 131 
#define  THERMAL_TREND_DROP_FULL 130 
#define  THERMAL_TREND_RAISE_FULL 129 
#define  THERMAL_TREND_RAISING 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct thermal_cooling_device*,unsigned long*) ; 

__attribute__((used)) static unsigned long get_target_state(struct thermal_instance *instance,
				enum thermal_trend trend, bool throttle)
{
	struct thermal_cooling_device *cdev = instance->cdev;
	unsigned long cur_state;
	unsigned long next_target;

	/*
	 * We keep this instance the way it is by default.
	 * Otherwise, we use the current state of the
	 * cdev in use to determine the next_target.
	 */
	cdev->ops->get_cur_state(cdev, &cur_state);
	next_target = instance->target;
	dev_dbg(&cdev->device, "cur_state=%ld\n", cur_state);

	if (!instance->initialized) {
		if (throttle) {
			next_target = (cur_state + 1) >= instance->upper ?
					instance->upper :
					((cur_state + 1) < instance->lower ?
					instance->lower : (cur_state + 1));
		} else {
			next_target = THERMAL_NO_TARGET;
		}

		return next_target;
	}

	switch (trend) {
	case THERMAL_TREND_RAISING:
		if (throttle) {
			next_target = cur_state < instance->upper ?
				    (cur_state + 1) : instance->upper;
			if (next_target < instance->lower)
				next_target = instance->lower;
		}
		break;
	case THERMAL_TREND_RAISE_FULL:
		if (throttle)
			next_target = instance->upper;
		break;
	case THERMAL_TREND_DROPPING:
		if (cur_state <= instance->lower) {
			if (!throttle)
				next_target = THERMAL_NO_TARGET;
		} else {
			if (!throttle) {
				next_target = cur_state - 1;
				if (next_target > instance->upper)
					next_target = instance->upper;
			}
		}
		break;
	case THERMAL_TREND_DROP_FULL:
		if (cur_state == instance->lower) {
			if (!throttle)
				next_target = THERMAL_NO_TARGET;
		} else
			next_target = instance->lower;
		break;
	default:
		break;
	}

	return next_target;
}