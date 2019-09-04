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
struct at91_udc {int enabled; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pullup (struct at91_udc*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct at91_udc* to_udc (struct usb_gadget*) ; 

__attribute__((used)) static int at91_pullup(struct usb_gadget *gadget, int is_on)
{
	struct at91_udc	*udc = to_udc(gadget);
	unsigned long	flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->enabled = is_on = !!is_on;
	pullup(udc, is_on);
	spin_unlock_irqrestore(&udc->lock, flags);
	return 0;
}