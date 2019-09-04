#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct brcmf_usbdev_info {TYPE_1__ bus_pub; int /*<<< orphan*/  settings; int /*<<< orphan*/  dev; int /*<<< orphan*/  wowl_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMFMAC_USB_STATE_UP ; 
 int /*<<< orphan*/  USB ; 
 int brcmf_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_usb_rx_fill_all (struct brcmf_usbdev_info*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 

__attribute__((used)) static int brcmf_usb_resume(struct usb_interface *intf)
{
	struct usb_device *usb = interface_to_usbdev(intf);
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(&usb->dev);

	brcmf_dbg(USB, "Enter\n");
	if (!devinfo->wowl_enabled)
		return brcmf_attach(devinfo->dev, devinfo->settings);

	devinfo->bus_pub.state = BRCMFMAC_USB_STATE_UP;
	brcmf_usb_rx_fill_all(devinfo);
	return 0;
}