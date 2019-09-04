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
struct usb_gadget {int dummy; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
#define  USB_EVENT_NONE 129 
#define  USB_EVENT_VBUS 128 
 int /*<<< orphan*/  usb_gadget_vbus_connect (struct usb_gadget*) ; 
 int /*<<< orphan*/  usb_gadget_vbus_disconnect (struct usb_gadget*) ; 

__attribute__((used)) static int pxa_udc_phy_event(struct notifier_block *nb, unsigned long action,
			     void *data)
{
	struct usb_gadget *gadget = data;

	switch (action) {
	case USB_EVENT_VBUS:
		usb_gadget_vbus_connect(gadget);
		return NOTIFY_OK;
	case USB_EVENT_NONE:
		usb_gadget_vbus_disconnect(gadget);
		return NOTIFY_OK;
	default:
		return NOTIFY_DONE;
	}
}