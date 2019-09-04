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
struct xusb_udc {int (* read_fn ) (scalar_t__) ;scalar_t__ addr; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ XUSB_FRAMENUM_OFFSET ; 
 int stub1 (scalar_t__) ; 
 struct xusb_udc* to_udc (struct usb_gadget*) ; 

__attribute__((used)) static int xudc_get_frame(struct usb_gadget *gadget)
{
	struct xusb_udc *udc;
	int frame;

	if (!gadget)
		return -ENODEV;

	udc = to_udc(gadget);
	frame = udc->read_fn(udc->addr + XUSB_FRAMENUM_OFFSET);
	return frame;
}