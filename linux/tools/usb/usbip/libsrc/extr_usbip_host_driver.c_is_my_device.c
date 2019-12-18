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
 int /*<<< orphan*/  USBIP_HOST_DRV_NAME ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* udev_device_get_driver (struct udev_device*) ; 

__attribute__((used)) static int is_my_device(struct udev_device *dev)
{
	const char *driver;

	driver = udev_device_get_driver(dev);
	return driver != NULL && !strcmp(driver, USBIP_HOST_DRV_NAME);
}