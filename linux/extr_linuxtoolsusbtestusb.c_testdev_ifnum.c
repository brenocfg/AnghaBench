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
struct usb_device_descriptor {int bLength; scalar_t__ bDescriptorType; int idVendor; int idProduct; scalar_t__ bDeviceClass; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ USB_CLASS_PER_INTERFACE ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 scalar_t__ USB_DT_DEVICE ; 
 int fread (struct usb_device_descriptor*,int,int,int /*<<< orphan*/ *) ; 
 int testdev_ffs_ifnum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int testdev_ifnum(FILE *fd)
{
	struct usb_device_descriptor dev;

	if (fread(&dev, sizeof dev, 1, fd) != 1)
		return -1;

	if (dev.bLength != sizeof dev || dev.bDescriptorType != USB_DT_DEVICE)
		return -1;

	/* FX2 with (tweaked) bulksrc firmware */
	if (dev.idVendor == 0x0547 && dev.idProduct == 0x1002)
		return 0;

	/*----------------------------------------------------*/

	/* devices that start up using the EZ-USB default device and
	 * which we can use after loading simple firmware.  hotplug
	 * can fxload it, and then run this test driver.
	 *
	 * we return false positives in two cases:
	 * - the device has a "real" driver (maybe usb-serial) that
	 *   renumerates.  the device should vanish quickly.
	 * - the device doesn't have the test firmware installed.
	 */

	/* generic EZ-USB FX controller */
	if (dev.idVendor == 0x0547 && dev.idProduct == 0x2235)
		return 0;

	/* generic EZ-USB FX2 controller */
	if (dev.idVendor == 0x04b4 && dev.idProduct == 0x8613)
		return 0;

	/* CY3671 development board with EZ-USB FX */
	if (dev.idVendor == 0x0547 && dev.idProduct == 0x0080)
		return 0;

	/* Keyspan 19Qi uses an21xx (original EZ-USB) */
	if (dev.idVendor == 0x06cd && dev.idProduct == 0x010b)
		return 0;

	/*----------------------------------------------------*/

	/* "gadget zero", Linux-USB test software */
	if (dev.idVendor == 0x0525 && dev.idProduct == 0xa4a0)
		return 0;

	/* user mode subset of that */
	if (dev.idVendor == 0x0525 && dev.idProduct == 0xa4a4)
		return testdev_ffs_ifnum(fd);
		/* return 0; */

	/* iso version of usermode code */
	if (dev.idVendor == 0x0525 && dev.idProduct == 0xa4a3)
		return 0;

	/* some GPL'd test firmware uses these IDs */

	if (dev.idVendor == 0xfff0 && dev.idProduct == 0xfff0)
		return 0;

	/*----------------------------------------------------*/

	/* iBOT2 high speed webcam */
	if (dev.idVendor == 0x0b62 && dev.idProduct == 0x0059)
		return 0;

	/*----------------------------------------------------*/

	/* the FunctionFS gadget can have the source/sink interface
	 * anywhere.  We look for an interface descriptor that match
	 * what we expect.  We ignore configuratiens thou. */

	if (dev.idVendor == 0x0525 && dev.idProduct == 0xa4ac
	 && (dev.bDeviceClass == USB_CLASS_PER_INTERFACE
	  || dev.bDeviceClass == USB_CLASS_VENDOR_SPEC))
		return testdev_ffs_ifnum(fd);

	return -1;
}