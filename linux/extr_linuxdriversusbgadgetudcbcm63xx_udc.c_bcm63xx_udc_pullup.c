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
struct usb_gadget {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct bcm63xx_udc {scalar_t__ ep0state; int ep0_req_shutdown; int /*<<< orphan*/  lock; int /*<<< orphan*/  ep0_wq; int /*<<< orphan*/ * bep; int /*<<< orphan*/  wedgemap; TYPE_1__ gadget; } ;

/* Variables and functions */
 int BCM63XX_NUM_EP ; 
 int EINVAL ; 
 scalar_t__ EP0_REQUEUE ; 
 scalar_t__ EP0_SHUTDOWN ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  bcm63xx_ep_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_fifo_reset (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_fifo_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_select_pullup (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  bcm63xx_set_ctrl_irqs (struct bcm63xx_udc*,int) ; 
 int /*<<< orphan*/  bcm63xx_set_stall (struct bcm63xx_udc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct bcm63xx_udc* gadget_to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm63xx_udc_pullup(struct usb_gadget *gadget, int is_on)
{
	struct bcm63xx_udc *udc = gadget_to_udc(gadget);
	unsigned long flags;
	int i, rc = -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	if (is_on && udc->ep0state == EP0_SHUTDOWN) {
		udc->gadget.speed = USB_SPEED_UNKNOWN;
		udc->ep0state = EP0_REQUEUE;
		bcm63xx_fifo_setup(udc);
		bcm63xx_fifo_reset(udc);
		bcm63xx_ep_setup(udc);

		bitmap_zero(&udc->wedgemap, BCM63XX_NUM_EP);
		for (i = 0; i < BCM63XX_NUM_EP; i++)
			bcm63xx_set_stall(udc, &udc->bep[i], false);

		bcm63xx_set_ctrl_irqs(udc, true);
		bcm63xx_select_pullup(gadget_to_udc(gadget), true);
		rc = 0;
	} else if (!is_on && udc->ep0state != EP0_SHUTDOWN) {
		bcm63xx_select_pullup(gadget_to_udc(gadget), false);

		udc->ep0_req_shutdown = 1;
		spin_unlock_irqrestore(&udc->lock, flags);

		while (1) {
			schedule_work(&udc->ep0_wq);
			if (udc->ep0state == EP0_SHUTDOWN)
				break;
			msleep(50);
		}
		bcm63xx_set_ctrl_irqs(udc, false);
		cancel_work_sync(&udc->ep0_wq);
		return 0;
	}

	spin_unlock_irqrestore(&udc->lock, flags);
	return rc;
}