#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int quirks; scalar_t__ speed; TYPE_4__* parent; int /*<<< orphan*/  dev; TYPE_3__* bos; } ;
struct TYPE_8__ {scalar_t__ lpm_capable; } ;
struct TYPE_7__ {TYPE_2__* ss_cap; TYPE_1__* ext_cap; } ;
struct TYPE_6__ {scalar_t__ bU1devExitLat; scalar_t__ bU2DevExitLat; } ;
struct TYPE_5__ {int /*<<< orphan*/  bmAttributes; } ;

/* Variables and functions */
 int USB_LPM_SUPPORT ; 
 int USB_QUIRK_NO_LPM ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

int usb_device_supports_lpm(struct usb_device *udev)
{
	/* Some devices have trouble with LPM */
	if (udev->quirks & USB_QUIRK_NO_LPM)
		return 0;

	/* USB 2.1 (and greater) devices indicate LPM support through
	 * their USB 2.0 Extended Capabilities BOS descriptor.
	 */
	if (udev->speed == USB_SPEED_HIGH || udev->speed == USB_SPEED_FULL) {
		if (udev->bos->ext_cap &&
			(USB_LPM_SUPPORT &
			 le32_to_cpu(udev->bos->ext_cap->bmAttributes)))
			return 1;
		return 0;
	}

	/*
	 * According to the USB 3.0 spec, all USB 3.0 devices must support LPM.
	 * However, there are some that don't, and they set the U1/U2 exit
	 * latencies to zero.
	 */
	if (!udev->bos->ss_cap) {
		dev_info(&udev->dev, "No LPM exit latency info found, disabling LPM.\n");
		return 0;
	}

	if (udev->bos->ss_cap->bU1devExitLat == 0 &&
			udev->bos->ss_cap->bU2DevExitLat == 0) {
		if (udev->parent)
			dev_info(&udev->dev, "LPM exit latency is zeroed, disabling LPM.\n");
		else
			dev_info(&udev->dev, "We don't know the algorithms for LPM for this host, disabling LPM.\n");
		return 0;
	}

	if (!udev->parent || udev->parent->lpm_capable)
		return 1;
	return 0;
}