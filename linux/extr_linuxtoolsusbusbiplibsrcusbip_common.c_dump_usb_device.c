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
struct usbip_usb_device {char* path; char* busid; int /*<<< orphan*/  speed; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_UDEV_INTEGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bNumConfigurations ; 
 int /*<<< orphan*/  bNumInterfaces ; 
 int /*<<< orphan*/  bcdDevice ; 
 int /*<<< orphan*/  busnum ; 
 int /*<<< orphan*/  dbg (char*,char*,char*) ; 
 int /*<<< orphan*/  devnum ; 
 int /*<<< orphan*/  usbip_names_get_class (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_names_get_product (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* usbip_speed_string (int /*<<< orphan*/ ) ; 

void dump_usb_device(struct usbip_usb_device *udev)
{
	char buff[100];

	dbg("%-20s = %s", "path",  udev->path);
	dbg("%-20s = %s", "busid", udev->busid);

	usbip_names_get_class(buff, sizeof(buff),
			udev->bDeviceClass,
			udev->bDeviceSubClass,
			udev->bDeviceProtocol);
	dbg("%-20s = %s", "Device(C/SC/P)", buff);

	DBG_UDEV_INTEGER(bcdDevice);

	usbip_names_get_product(buff, sizeof(buff),
			udev->idVendor,
			udev->idProduct);
	dbg("%-20s = %s", "Vendor/Product", buff);

	DBG_UDEV_INTEGER(bNumConfigurations);
	DBG_UDEV_INTEGER(bNumInterfaces);

	dbg("%-20s = %s", "speed",
			usbip_speed_string(udev->speed));

	DBG_UDEV_INTEGER(busnum);
	DBG_UDEV_INTEGER(devnum);
}