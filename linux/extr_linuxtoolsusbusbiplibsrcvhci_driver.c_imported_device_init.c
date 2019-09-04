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
struct usbip_imported_device {int /*<<< orphan*/  udev; } ;
struct udev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  read_usb_device (struct udev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_context ; 
 struct udev_device* udev_device_new_from_subsystem_sysname (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 

__attribute__((used)) static struct usbip_imported_device *
imported_device_init(struct usbip_imported_device *idev, char *busid)
{
	struct udev_device *sudev;

	sudev = udev_device_new_from_subsystem_sysname(udev_context,
						       "usb", busid);
	if (!sudev) {
		dbg("udev_device_new_from_subsystem_sysname failed: %s", busid);
		goto err;
	}
	read_usb_device(sudev, &idev->udev);
	udev_device_unref(sudev);

	return idev;

err:
	return NULL;
}