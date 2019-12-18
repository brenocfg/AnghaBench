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
typedef  enum unbind_status { ____Placeholder_unbind_status } unbind_status ;

/* Variables and functions */
 char* SYSFS_BUS_NAME ; 
 char* SYSFS_BUS_TYPE ; 
 char* SYSFS_DRIVERS_NAME ; 
 char* SYSFS_MNT_PATH ; 
 int SYSFS_PATH_MAX ; 
 int UNBIND_ST_FAILED ; 
 int UNBIND_ST_OK ; 
 int UNBIND_ST_USBIP_HOST ; 
 char* USBIP_HOST_DRV_NAME ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  err (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 char* udev_device_get_driver (struct udev_device*) ; 
 char* udev_device_get_sysattr_value (struct udev_device*,char*) ; 
 struct udev_device* udev_device_new_from_subsystem_sysname (struct udev*,char*,char*) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 
 struct udev* udev_new () ; 
 int /*<<< orphan*/  udev_unref (struct udev*) ; 
 int write_sysfs_attribute (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unbind_other(char *busid)
{
	enum unbind_status status = UNBIND_ST_OK;

	char attr_name[] = "unbind";
	char unbind_attr_path[SYSFS_PATH_MAX];
	int rc = -1;

	struct udev *udev;
	struct udev_device *dev;
	const char *driver;
	const char *bDevClass;

	/* Create libudev context. */
	udev = udev_new();

	/* Get the device. */
	dev = udev_device_new_from_subsystem_sysname(udev, "usb", busid);
	if (!dev) {
		dbg("unable to find device with bus ID %s", busid);
		goto err_close_busid_dev;
	}

	/* Check what kind of device it is. */
	bDevClass  = udev_device_get_sysattr_value(dev, "bDeviceClass");
	if (!bDevClass) {
		dbg("unable to get bDevClass device attribute");
		goto err_close_busid_dev;
	}

	if (!strncmp(bDevClass, "09", strlen(bDevClass))) {
		dbg("skip unbinding of hub");
		goto err_close_busid_dev;
	}

	/* Get the device driver. */
	driver = udev_device_get_driver(dev);
	if (!driver) {
		/* No driver bound to this device. */
		goto out;
	}

	if (!strncmp(USBIP_HOST_DRV_NAME, driver,
				strlen(USBIP_HOST_DRV_NAME))) {
		/* Already bound to usbip-host. */
		status = UNBIND_ST_USBIP_HOST;
		goto out;
	}

	/* Unbind device from driver. */
	snprintf(unbind_attr_path, sizeof(unbind_attr_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, SYSFS_BUS_TYPE,
		 SYSFS_DRIVERS_NAME, driver, attr_name);

	rc = write_sysfs_attribute(unbind_attr_path, busid, strlen(busid));
	if (rc < 0) {
		err("error unbinding device %s from driver", busid);
		goto err_close_busid_dev;
	}

	goto out;

err_close_busid_dev:
	status = UNBIND_ST_FAILED;
out:
	udev_device_unref(dev);
	udev_unref(udev);

	return status;
}