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
typedef  int /*<<< orphan*/  unbind_attr_path ;
struct udev_device {int dummy; } ;
struct udev {int dummy; } ;

/* Variables and functions */
 char* SYSFS_BUS_NAME ; 
 char* SYSFS_DRIVERS_NAME ; 
 char* SYSFS_MNT_PATH ; 
 int SYSFS_PATH_MAX ; 
 char* USBIP_HOST_DRV_NAME ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int modify_match_busid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* udev_device_get_driver (struct udev_device*) ; 
 struct udev_device* udev_device_new_from_subsystem_sysname (struct udev*,char*,char*) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 
 struct udev* udev_new () ; 
 int /*<<< orphan*/  udev_unref (struct udev*) ; 
 int write_sysfs_attribute (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unbind_device(char *busid)
{
	char bus_type[] = "usb";
	int rc, ret = -1;

	char unbind_attr_name[] = "unbind";
	char unbind_attr_path[SYSFS_PATH_MAX];
	char rebind_attr_name[] = "rebind";
	char rebind_attr_path[SYSFS_PATH_MAX];

	struct udev *udev;
	struct udev_device *dev;
	const char *driver;

	/* Create libudev context. */
	udev = udev_new();

	/* Check whether the device with this bus ID exists. */
	dev = udev_device_new_from_subsystem_sysname(udev, "usb", busid);
	if (!dev) {
		err("device with the specified bus ID does not exist");
		goto err_close_udev;
	}

	/* Check whether the device is using usbip-host driver. */
	driver = udev_device_get_driver(dev);
	if (!driver || strcmp(driver, "usbip-host")) {
		err("device is not bound to usbip-host driver");
		goto err_close_udev;
	}

	/* Unbind device from driver. */
	snprintf(unbind_attr_path, sizeof(unbind_attr_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, bus_type, SYSFS_DRIVERS_NAME,
		 USBIP_HOST_DRV_NAME, unbind_attr_name);

	rc = write_sysfs_attribute(unbind_attr_path, busid, strlen(busid));
	if (rc < 0) {
		err("error unbinding device %s from driver", busid);
		goto err_close_udev;
	}

	/* Notify driver of unbind. */
	rc = modify_match_busid(busid, 0);
	if (rc < 0) {
		err("unable to unbind device on %s", busid);
		goto err_close_udev;
	}

	/* Trigger new probing. */
	snprintf(rebind_attr_path, sizeof(unbind_attr_path), "%s/%s/%s/%s/%s/%s",
			SYSFS_MNT_PATH, SYSFS_BUS_NAME, bus_type, SYSFS_DRIVERS_NAME,
			USBIP_HOST_DRV_NAME, rebind_attr_name);

	rc = write_sysfs_attribute(rebind_attr_path, busid, strlen(busid));
	if (rc < 0) {
		err("error rebinding");
		goto err_close_udev;
	}

	ret = 0;
	info("unbind device on busid %s: complete", busid);

err_close_udev:
	udev_device_unref(dev);
	udev_unref(udev);

	return ret;
}