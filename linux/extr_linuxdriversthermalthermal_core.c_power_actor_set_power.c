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
struct thermal_instance {unsigned long target; int /*<<< orphan*/  tz; } ;
struct thermal_cooling_device {int updated; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* power2state ) (struct thermal_cooling_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cdev_is_power_actor (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct thermal_cooling_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  thermal_cdev_update (struct thermal_cooling_device*) ; 

int power_actor_set_power(struct thermal_cooling_device *cdev,
			  struct thermal_instance *instance, u32 power)
{
	unsigned long state;
	int ret;

	if (!cdev_is_power_actor(cdev))
		return -EINVAL;

	ret = cdev->ops->power2state(cdev, instance->tz, power, &state);
	if (ret)
		return ret;

	instance->target = state;
	mutex_lock(&cdev->lock);
	cdev->updated = false;
	mutex_unlock(&cdev->lock);
	thermal_cdev_update(cdev);

	return 0;
}