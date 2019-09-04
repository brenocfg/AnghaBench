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
struct usb_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct brcmf_usbdev_info {int dummy; } ;
struct brcmf_fw_request {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int brcmf_fw_get_firmwares (int /*<<< orphan*/ *,struct brcmf_fw_request*,int /*<<< orphan*/ ) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (int /*<<< orphan*/ *) ; 
 struct brcmf_fw_request* brcmf_usb_prepare_fw_request (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_usb_probe_phase2 ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw_request*) ; 

__attribute__((used)) static int brcmf_usb_reset_resume(struct usb_interface *intf)
{
	struct usb_device *usb = interface_to_usbdev(intf);
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(&usb->dev);
	struct brcmf_fw_request *fwreq;
	int ret;

	brcmf_dbg(USB, "Enter\n");

	fwreq = brcmf_usb_prepare_fw_request(devinfo);
	if (!fwreq)
		return -ENOMEM;

	ret = brcmf_fw_get_firmwares(&usb->dev, fwreq, brcmf_usb_probe_phase2);
	if (ret < 0)
		kfree(fwreq);

	return ret;
}