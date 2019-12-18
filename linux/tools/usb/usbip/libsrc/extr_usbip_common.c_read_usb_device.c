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
typedef  int /*<<< orphan*/  uint32_t ;
struct usbip_usb_device {char* path; char* busid; int /*<<< orphan*/  busnum; int /*<<< orphan*/  speed; } ;
struct udev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ATTR (struct usbip_usb_device*,int /*<<< orphan*/ ,struct udev_device*,int /*<<< orphan*/ ,char*) ; 
 int SYSFS_BUS_ID_SIZE ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  bConfigurationValue ; 
 int /*<<< orphan*/  bDeviceClass ; 
 int /*<<< orphan*/  bDeviceProtocol ; 
 int /*<<< orphan*/  bDeviceSubClass ; 
 int /*<<< orphan*/  bNumConfigurations ; 
 int /*<<< orphan*/  bNumInterfaces ; 
 int /*<<< orphan*/  bcdDevice ; 
 int /*<<< orphan*/  idProduct ; 
 int /*<<< orphan*/  idVendor ; 
 int /*<<< orphan*/  read_attr_speed (struct udev_device*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* udev_device_get_sysname (struct udev_device*) ; 
 char* udev_device_get_syspath (struct udev_device*) ; 
 int /*<<< orphan*/  uint16_t ; 
 int /*<<< orphan*/  uint8_t ; 

int read_usb_device(struct udev_device *sdev, struct usbip_usb_device *udev)
{
	uint32_t busnum, devnum;
	const char *path, *name;

	READ_ATTR(udev, uint8_t,  sdev, bDeviceClass,		"%02x\n");
	READ_ATTR(udev, uint8_t,  sdev, bDeviceSubClass,	"%02x\n");
	READ_ATTR(udev, uint8_t,  sdev, bDeviceProtocol,	"%02x\n");

	READ_ATTR(udev, uint16_t, sdev, idVendor,		"%04x\n");
	READ_ATTR(udev, uint16_t, sdev, idProduct,		"%04x\n");
	READ_ATTR(udev, uint16_t, sdev, bcdDevice,		"%04x\n");

	READ_ATTR(udev, uint8_t,  sdev, bConfigurationValue,	"%02x\n");
	READ_ATTR(udev, uint8_t,  sdev, bNumConfigurations,	"%02x\n");
	READ_ATTR(udev, uint8_t,  sdev, bNumInterfaces,		"%02x\n");

	READ_ATTR(udev, uint8_t,  sdev, devnum,			"%d\n");
	udev->speed = read_attr_speed(sdev);

	path = udev_device_get_syspath(sdev);
	name = udev_device_get_sysname(sdev);

	strncpy(udev->path,  path,  SYSFS_PATH_MAX - 1);
	udev->path[SYSFS_PATH_MAX - 1] = '\0';
	strncpy(udev->busid, name, SYSFS_BUS_ID_SIZE - 1);
	udev->busid[SYSFS_BUS_ID_SIZE - 1] = '\0';

	sscanf(name, "%u-%u", &busnum, &devnum);
	udev->busnum = busnum;

	return 0;
}