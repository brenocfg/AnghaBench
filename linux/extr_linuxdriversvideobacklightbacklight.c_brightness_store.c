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
struct backlight_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int backlight_device_set_brightness (struct backlight_device*,unsigned long) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct backlight_device* to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t brightness_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc;
	struct backlight_device *bd = to_backlight_device(dev);
	unsigned long brightness;

	rc = kstrtoul(buf, 0, &brightness);
	if (rc)
		return rc;

	rc = backlight_device_set_brightness(bd, brightness);

	return rc ? rc : count;
}