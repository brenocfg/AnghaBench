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
struct udev_device {int dummy; } ;
struct TYPE_2__ {int num; int /*<<< orphan*/ * speed; } ;

/* Variables and functions */
 int USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  err (char*) ; 
 TYPE_1__* speed_strings ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ *) ; 
 char* udev_device_get_sysattr_value (struct udev_device*,char*) ; 

int read_attr_speed(struct udev_device *dev)
{
	const char *speed;

	speed = udev_device_get_sysattr_value(dev, "speed");
	if (!speed) {
		err("udev_device_get_sysattr_value failed");
		goto err;
	}

	for (int i = 0; speed_strings[i].speed != NULL; i++) {
		if (!strcmp(speed, speed_strings[i].speed))
			return speed_strings[i].num;
	}

err:

	return USB_SPEED_UNKNOWN;
}