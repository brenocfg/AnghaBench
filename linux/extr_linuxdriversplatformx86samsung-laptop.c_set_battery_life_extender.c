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
struct samsung_laptop {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct samsung_laptop* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int write_battery_life_extender (struct samsung_laptop*,int) ; 

__attribute__((used)) static ssize_t set_battery_life_extender(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct samsung_laptop *samsung = dev_get_drvdata(dev);
	int ret, value;

	if (!count || kstrtoint(buf, 0, &value) != 0)
		return -EINVAL;

	ret = write_battery_life_extender(samsung, !!value);
	if (ret < 0)
		return ret;

	return count;
}