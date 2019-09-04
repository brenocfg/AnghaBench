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
struct usbatm_data {int dummy; } ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  uea_driver ; 
 int /*<<< orphan*/  uea_err (struct usb_device*,char*,int,...) ; 
 int usb_driver_claim_interface (int /*<<< orphan*/ *,struct usb_interface*,struct usbatm_data*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 

__attribute__((used)) static int claim_interface(struct usb_device *usb_dev,
			   struct usbatm_data *usbatm, int ifnum)
{
	int ret;
	struct usb_interface *intf = usb_ifnum_to_if(usb_dev, ifnum);

	if (!intf) {
		uea_err(usb_dev, "interface %d not found\n", ifnum);
		return -ENODEV;
	}

	ret = usb_driver_claim_interface(&uea_driver, intf, usbatm);
	if (ret != 0)
		uea_err(usb_dev, "can't claim interface %d, error %d\n", ifnum,
		       ret);
	return ret;
}