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
struct usbip_usb_interface {int dummy; } ;
struct usbip_usb_device {char* busid; int bConfigurationValue; } ;
struct udev_device {int dummy; } ;
typedef  int /*<<< orphan*/  busid ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ATTR (struct usbip_usb_interface*,int /*<<< orphan*/ ,struct udev_device*,int /*<<< orphan*/ ,char*) ; 
 int SYSFS_BUS_ID_SIZE ; 
 int /*<<< orphan*/  bInterfaceClass ; 
 int /*<<< orphan*/  bInterfaceProtocol ; 
 int /*<<< orphan*/  bInterfaceSubClass ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int snprintf (char*,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  udev_context ; 
 struct udev_device* udev_device_new_from_subsystem_sysname (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  uint8_t ; 

int read_usb_interface(struct usbip_usb_device *udev, int i,
		       struct usbip_usb_interface *uinf)
{
	char busid[SYSFS_BUS_ID_SIZE];
	int size;
	struct udev_device *sif;

	size = snprintf(busid, sizeof(busid), "%s:%d.%d",
			udev->busid, udev->bConfigurationValue, i);
	if (size < 0 || (unsigned int)size >= sizeof(busid)) {
		err("busid length %i >= %lu or < 0", size,
		    (long unsigned)sizeof(busid));
		return -1;
	}

	sif = udev_device_new_from_subsystem_sysname(udev_context, "usb", busid);
	if (!sif) {
		err("udev_device_new_from_subsystem_sysname %s failed", busid);
		return -1;
	}

	READ_ATTR(uinf, uint8_t,  sif, bInterfaceClass,		"%02x\n");
	READ_ATTR(uinf, uint8_t,  sif, bInterfaceSubClass,	"%02x\n");
	READ_ATTR(uinf, uint8_t,  sif, bInterfaceProtocol,	"%02x\n");

	return 0;
}