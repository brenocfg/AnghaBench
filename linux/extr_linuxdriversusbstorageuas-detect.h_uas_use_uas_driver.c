#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_host_interface {int dummy; } ;
struct usb_host_endpoint {int /*<<< orphan*/  ss_ep_comp; } ;
struct usb_hcd {int /*<<< orphan*/  can_do_streams; TYPE_4__* driver; } ;
struct usb_device_id {unsigned long driver_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  idVendor; int /*<<< orphan*/  idProduct; } ;
struct usb_device {scalar_t__ speed; int /*<<< orphan*/  dev; TYPE_6__* bus; TYPE_3__ descriptor; TYPE_2__* actconfig; } ;
struct TYPE_12__ {scalar_t__ sg_tablesize; } ;
struct TYPE_11__ {int /*<<< orphan*/  bus_name; } ;
struct TYPE_10__ {int /*<<< orphan*/  description; } ;
struct TYPE_7__ {scalar_t__ bMaxPower; } ;
struct TYPE_8__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_SUPER ; 
 unsigned long US_FL_IGNORE_UAS ; 
 unsigned long US_FL_MAX_SECTORS_240 ; 
 unsigned long US_FL_NO_ATA_1X ; 
 struct usb_hcd* bus_to_hcd (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_5__* hcd_to_bus (struct usb_hcd*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int uas_find_endpoints (struct usb_host_interface*,struct usb_host_endpoint**) ; 
 struct usb_host_interface* uas_find_uas_alt_setting (struct usb_interface*) ; 
 int usb_ss_max_streams (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_adjust_quirks (struct usb_device*,unsigned long*) ; 

__attribute__((used)) static int uas_use_uas_driver(struct usb_interface *intf,
			      const struct usb_device_id *id,
			      unsigned long *flags_ret)
{
	struct usb_host_endpoint *eps[4] = { };
	struct usb_device *udev = interface_to_usbdev(intf);
	struct usb_hcd *hcd = bus_to_hcd(udev->bus);
	unsigned long flags = id->driver_info;
	struct usb_host_interface *alt;
	int r;

	alt = uas_find_uas_alt_setting(intf);
	if (!alt)
		return 0;

	r = uas_find_endpoints(alt, eps);
	if (r < 0)
		return 0;

	/*
	 * ASMedia has a number of usb3 to sata bridge chips, at the time of
	 * this writing the following versions exist:
	 * ASM1051 - no uas support version
	 * ASM1051 - with broken (*) uas support
	 * ASM1053 - with working uas support, but problems with large xfers
	 * ASM1153 - with working uas support
	 *
	 * Devices with these chips re-use a number of device-ids over the
	 * entire line, so the device-id is useless to determine if we're
	 * dealing with an ASM1051 (which we want to avoid).
	 *
	 * The ASM1153 can be identified by config.MaxPower == 0,
	 * where as the ASM105x models have config.MaxPower == 36.
	 *
	 * Differentiating between the ASM1053 and ASM1051 is trickier, when
	 * connected over USB-3 we can look at the number of streams supported,
	 * ASM1051 supports 32 streams, where as early ASM1053 versions support
	 * 16 streams, newer ASM1053-s also support 32 streams, but have a
	 * different prod-id.
	 *
	 * (*) ASM1051 chips do work with UAS with some disks (with the
	 *     US_FL_NO_REPORT_OPCODES quirk), but are broken with other disks
	 */
	if (le16_to_cpu(udev->descriptor.idVendor) == 0x174c &&
			(le16_to_cpu(udev->descriptor.idProduct) == 0x5106 ||
			 le16_to_cpu(udev->descriptor.idProduct) == 0x55aa)) {
		if (udev->actconfig->desc.bMaxPower == 0) {
			/* ASM1153, do nothing */
		} else if (udev->speed < USB_SPEED_SUPER) {
			/* No streams info, assume ASM1051 */
			flags |= US_FL_IGNORE_UAS;
		} else if (usb_ss_max_streams(&eps[1]->ss_ep_comp) == 32) {
			/* Possibly an ASM1051, disable uas */
			flags |= US_FL_IGNORE_UAS;
		} else {
			/* ASM1053, these have issues with large transfers */
			flags |= US_FL_MAX_SECTORS_240;
		}
	}

	/* All Seagate disk enclosures have broken ATA pass-through support */
	if (le16_to_cpu(udev->descriptor.idVendor) == 0x0bc2)
		flags |= US_FL_NO_ATA_1X;

	usb_stor_adjust_quirks(udev, &flags);

	if (flags & US_FL_IGNORE_UAS) {
		dev_warn(&udev->dev,
			"UAS is blacklisted for this device, using usb-storage instead\n");
		return 0;
	}

	if (udev->bus->sg_tablesize == 0) {
		dev_warn(&udev->dev,
			"The driver for the USB controller %s does not support scatter-gather which is\n",
			hcd->driver->description);
		dev_warn(&udev->dev,
			"required by the UAS driver. Please try an other USB controller if you wish to use UAS.\n");
		return 0;
	}

	if (udev->speed >= USB_SPEED_SUPER && !hcd->can_do_streams) {
		dev_warn(&udev->dev,
			"USB controller %s does not support streams, which are required by the UAS driver.\n",
			hcd_to_bus(hcd)->bus_name);
		dev_warn(&udev->dev,
			"Please try an other USB controller if you wish to use UAS.\n");
		return 0;
	}

	if (flags_ret)
		*flags_ret = flags;

	return 1;
}