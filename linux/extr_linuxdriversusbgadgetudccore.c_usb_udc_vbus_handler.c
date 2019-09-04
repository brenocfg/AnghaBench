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
struct usb_udc {int vbus; } ;
struct usb_gadget {struct usb_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_udc_connect_control (struct usb_udc*) ; 

void usb_udc_vbus_handler(struct usb_gadget *gadget, bool status)
{
	struct usb_udc *udc = gadget->udc;

	if (udc) {
		udc->vbus = status;
		usb_udc_connect_control(udc);
	}
}