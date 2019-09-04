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
struct usb_gadget_driver {int /*<<< orphan*/  (* reset ) (struct usb_gadget*) ;} ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  stub1 (struct usb_gadget*) ; 
 int /*<<< orphan*/  usb_gadget_set_state (struct usb_gadget*,int /*<<< orphan*/ ) ; 

void usb_gadget_udc_reset(struct usb_gadget *gadget,
		struct usb_gadget_driver *driver)
{
	driver->reset(gadget);
	usb_gadget_set_state(gadget, USB_STATE_DEFAULT);
}