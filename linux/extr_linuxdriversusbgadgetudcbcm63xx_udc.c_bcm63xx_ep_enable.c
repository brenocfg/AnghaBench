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
struct usb_ep {scalar_t__ name; int /*<<< orphan*/  maxpacket; struct usb_endpoint_descriptor const* desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct iudma_ch {int enabled; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  wedgemap; int /*<<< orphan*/  driver; } ;
struct bcm63xx_ep {int /*<<< orphan*/  ep_num; scalar_t__ halted; int /*<<< orphan*/  queue; struct iudma_ch* iudma; struct bcm63xx_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ESHUTDOWN ; 
 scalar_t__ bcm63xx_ep0name ; 
 int /*<<< orphan*/  bcm63xx_set_stall (struct bcm63xx_udc*,struct bcm63xx_ep*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iudma_reset_channel (struct bcm63xx_udc*,struct iudma_ch*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct bcm63xx_ep* our_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int bcm63xx_ep_enable(struct usb_ep *ep,
	const struct usb_endpoint_descriptor *desc)
{
	struct bcm63xx_ep *bep = our_ep(ep);
	struct bcm63xx_udc *udc = bep->udc;
	struct iudma_ch *iudma = bep->iudma;
	unsigned long flags;

	if (!ep || !desc || ep->name == bcm63xx_ep0name)
		return -EINVAL;

	if (!udc->driver)
		return -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	if (iudma->enabled) {
		spin_unlock_irqrestore(&udc->lock, flags);
		return -EINVAL;
	}

	iudma->enabled = true;
	BUG_ON(!list_empty(&bep->queue));

	iudma_reset_channel(udc, iudma);

	bep->halted = 0;
	bcm63xx_set_stall(udc, bep, false);
	clear_bit(bep->ep_num, &udc->wedgemap);

	ep->desc = desc;
	ep->maxpacket = usb_endpoint_maxp(desc);

	spin_unlock_irqrestore(&udc->lock, flags);
	return 0;
}