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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct xusb_udc {int /*<<< orphan*/  lock; scalar_t__ remote_wkp; int /*<<< orphan*/  addr; int /*<<< orphan*/  (* write_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * driver; TYPE_1__ gadget; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  XUSB_ADDRESS_OFFSET ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xusb_udc* to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  xudc_stop_activity (struct xusb_udc*) ; 

__attribute__((used)) static int xudc_stop(struct usb_gadget *gadget)
{
	struct xusb_udc *udc = to_udc(gadget);
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->driver = NULL;

	/* Set device address and remote wakeup to 0 */
	udc->write_fn(udc->addr, XUSB_ADDRESS_OFFSET, 0);
	udc->remote_wkp = 0;

	xudc_stop_activity(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}