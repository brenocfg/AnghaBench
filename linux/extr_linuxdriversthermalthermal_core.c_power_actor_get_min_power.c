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
typedef  int /*<<< orphan*/  u32 ;
struct thermal_zone_device {int dummy; } ;
struct thermal_cooling_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_max_state ) (struct thermal_cooling_device*,unsigned long*) ;int (* state2power ) (struct thermal_cooling_device*,struct thermal_zone_device*,unsigned long,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cdev_is_power_actor (struct thermal_cooling_device*) ; 
 int stub1 (struct thermal_cooling_device*,unsigned long*) ; 
 int stub2 (struct thermal_cooling_device*,struct thermal_zone_device*,unsigned long,int /*<<< orphan*/ *) ; 

int power_actor_get_min_power(struct thermal_cooling_device *cdev,
			      struct thermal_zone_device *tz, u32 *min_power)
{
	unsigned long max_state;
	int ret;

	if (!cdev_is_power_actor(cdev))
		return -EINVAL;

	ret = cdev->ops->get_max_state(cdev, &max_state);
	if (ret)
		return ret;

	return cdev->ops->state2power(cdev, tz, max_state, min_power);
}