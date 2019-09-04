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
struct usb_udc {int /*<<< orphan*/  gadget; scalar_t__ vbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_gadget_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_udc_connect_control(struct usb_udc *udc)
{
	if (udc->vbus)
		usb_gadget_connect(udc->gadget);
	else
		usb_gadget_disconnect(udc->gadget);
}