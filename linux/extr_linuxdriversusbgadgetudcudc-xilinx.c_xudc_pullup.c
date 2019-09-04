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
typedef  int /*<<< orphan*/  u32 ;
struct xusb_udc {int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  (* write_fn ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_fn ) (scalar_t__) ;} ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 scalar_t__ XUSB_CONTROL_OFFSET ; 
 int /*<<< orphan*/  XUSB_CONTROL_USB_READY_MASK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct xusb_udc* to_udc (struct usb_gadget*) ; 

__attribute__((used)) static int xudc_pullup(struct usb_gadget *gadget, int is_on)
{
	struct xusb_udc *udc = to_udc(gadget);
	unsigned long flags;
	u32 crtlreg;

	spin_lock_irqsave(&udc->lock, flags);

	crtlreg = udc->read_fn(udc->addr + XUSB_CONTROL_OFFSET);
	if (is_on)
		crtlreg |= XUSB_CONTROL_USB_READY_MASK;
	else
		crtlreg &= ~XUSB_CONTROL_USB_READY_MASK;

	udc->write_fn(udc->addr, XUSB_CONTROL_OFFSET, crtlreg);

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}