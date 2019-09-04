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
struct lpc32xx_udc {int /*<<< orphan*/ * driver; scalar_t__ enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled_ep_cnt; int /*<<< orphan*/  ep_disable_wait_queue; scalar_t__ clocked; int /*<<< orphan*/ * udp_irq; } ;

/* Variables and functions */
 int IRQ_USB_ATX ; 
 int IRQ_USB_LP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_activity (struct lpc32xx_udc*) ; 
 struct lpc32xx_udc* to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  udc_clk_set (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpc32xx_stop(struct usb_gadget *gadget)
{
	int i;
	struct lpc32xx_udc *udc = to_udc(gadget);

	for (i = IRQ_USB_LP; i <= IRQ_USB_ATX; i++)
		disable_irq(udc->udp_irq[i]);

	if (udc->clocked) {
		spin_lock(&udc->lock);
		stop_activity(udc);
		spin_unlock(&udc->lock);

		/*
		 *  Wait for all the endpoints to disable,
		 *  before disabling clocks. Don't wait if
		 *  endpoints are not enabled.
		 */
		if (atomic_read(&udc->enabled_ep_cnt))
			wait_event_interruptible(udc->ep_disable_wait_queue,
				(atomic_read(&udc->enabled_ep_cnt) == 0));

		spin_lock(&udc->lock);
		udc_clk_set(udc, 0);
		spin_unlock(&udc->lock);
	}

	udc->enabled = 0;
	udc->driver = NULL;

	return 0;
}