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
struct udev {int dummy; } ;

/* Variables and functions */
 int UNBIND_ST_FAILED ; 
 int UNBIND_ST_USBIP_HOST ; 
 char* USBIP_HOST_DRV_NAME ; 
 int /*<<< orphan*/  USBIP_VHCI_DRV_NAME ; 
 int bind_usbip (char*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int modify_match_busid (char*,int) ; 
 scalar_t__ strstr (char const*,int /*<<< orphan*/ ) ; 
 char* udev_device_get_devpath (struct udev_device*) ; 
 struct udev_device* udev_device_new_from_subsystem_sysname (struct udev*,char*,char*) ; 
 struct udev* udev_new () ; 
 int /*<<< orphan*/  udev_unref (struct udev*) ; 
 int unbind_other (char*) ; 

__attribute__((used)) static int bind_device(char *busid)
{
	int rc;
	struct udev *udev;
	struct udev_device *dev;
	const char *devpath;

	/* Check whether the device with this bus ID exists. */
	udev = udev_new();
	dev = udev_device_new_from_subsystem_sysname(udev, "usb", busid);
	if (!dev) {
		err("device with the specified bus ID does not exist");
		return -1;
	}
	devpath = udev_device_get_devpath(dev);
	udev_unref(udev);

	/* If the device is already attached to vhci_hcd - bail out */
	if (strstr(devpath, USBIP_VHCI_DRV_NAME)) {
		err("bind loop detected: device: %s is attached to %s\n",
		    devpath, USBIP_VHCI_DRV_NAME);
		return -1;
	}

	rc = unbind_other(busid);
	if (rc == UNBIND_ST_FAILED) {
		err("could not unbind driver from device on busid %s", busid);
		return -1;
	} else if (rc == UNBIND_ST_USBIP_HOST) {
		err("device on busid %s is already bound to %s", busid,
		    USBIP_HOST_DRV_NAME);
		return -1;
	}

	rc = modify_match_busid(busid, 1);
	if (rc < 0) {
		err("unable to bind device on %s", busid);
		return -1;
	}

	rc = bind_usbip(busid);
	if (rc < 0) {
		err("could not bind device to %s", USBIP_HOST_DRV_NAME);
		modify_match_busid(busid, 0);
		return -1;
	}

	info("bind device on busid %s: complete", busid);

	return 0;
}