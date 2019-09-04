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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned long power; } ;
struct backlight_device {int /*<<< orphan*/  ops_lock; TYPE_1__ props; scalar_t__ ops; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENXIO ; 
 int backlight_update_status (struct backlight_device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 struct backlight_device* to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t bl_power_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	int rc;
	struct backlight_device *bd = to_backlight_device(dev);
	unsigned long power, old_power;

	rc = kstrtoul(buf, 0, &power);
	if (rc)
		return rc;

	rc = -ENXIO;
	mutex_lock(&bd->ops_lock);
	if (bd->ops) {
		pr_debug("set power to %lu\n", power);
		if (bd->props.power != power) {
			old_power = bd->props.power;
			bd->props.power = power;
			rc = backlight_update_status(bd);
			if (rc)
				bd->props.power = old_power;
			else
				rc = count;
		} else {
			rc = count;
		}
	}
	mutex_unlock(&bd->ops_lock);

	return rc;
}