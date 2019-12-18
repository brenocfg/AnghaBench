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
struct udev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*,...) ; 
 int sscanf (char const*,char const*,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* udev_device_get_sysattr_value (struct udev_device*,char const*) ; 

int read_attr_value(struct udev_device *dev, const char *name,
		    const char *format)
{
	const char *attr;
	int num = 0;
	int ret;

	attr = udev_device_get_sysattr_value(dev, name);
	if (!attr) {
		err("udev_device_get_sysattr_value failed");
		goto err;
	}

	/* The client chooses the device configuration
	 * when attaching it so right after being bound
	 * to usbip-host on the server the device will
	 * have no configuration.
	 * Therefore, attributes such as bConfigurationValue
	 * and bNumInterfaces will not exist and sscanf will
	 * fail. Check for these cases and don't treat them
	 * as errors.
	 */

	ret = sscanf(attr, format, &num);
	if (ret < 1) {
		if (strcmp(name, "bConfigurationValue") &&
				strcmp(name, "bNumInterfaces")) {
			err("sscanf failed for attribute %s", name);
			goto err;
		}
	}

err:

	return num;
}