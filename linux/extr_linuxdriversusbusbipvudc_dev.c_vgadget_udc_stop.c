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
struct vudc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vudc* usb_gadget_to_vudc (struct usb_gadget*) ; 

__attribute__((used)) static int vgadget_udc_stop(struct usb_gadget *g)
{
	struct vudc *udc = usb_gadget_to_vudc(g);
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->driver = NULL;
	spin_unlock_irqrestore(&udc->lock, flags);
	return 0;
}