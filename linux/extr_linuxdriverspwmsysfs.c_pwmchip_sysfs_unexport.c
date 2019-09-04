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
struct pwm_chip {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  pwm_class ; 
 int /*<<< orphan*/  pwmchip_sysfs_match ; 

void pwmchip_sysfs_unexport(struct pwm_chip *chip)
{
	struct device *parent;

	parent = class_find_device(&pwm_class, NULL, chip,
				   pwmchip_sysfs_match);
	if (parent) {
		/* for class_find_device() */
		put_device(parent);
		device_unregister(parent);
	}
}