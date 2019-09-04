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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int __sony_nc_kbd_backlight_timeout_set (unsigned long) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t sony_nc_kbd_backlight_timeout_store(struct device *dev,
		struct device_attribute *attr,
		const char *buffer, size_t count)
{
	int ret = 0;
	unsigned long value;

	if (count > 31)
		return -EINVAL;

	if (kstrtoul(buffer, 10, &value))
		return -EINVAL;

	ret = __sony_nc_kbd_backlight_timeout_set(value);
	if (ret < 0)
		return ret;

	return count;
}