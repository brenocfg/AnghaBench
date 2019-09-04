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
struct lpc32xx_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  enabled_ep_cnt; int /*<<< orphan*/  ep_disable_wait_queue; scalar_t__ driver; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullup (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_activity (struct lpc32xx_udc*) ; 
 struct lpc32xx_udc* to_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  udc_clk_set (struct lpc32xx_udc*,int) ; 
 int /*<<< orphan*/  udc_enable (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpc32xx_vbus_session(struct usb_gadget *gadget, int is_active)
{
	unsigned long flags;
	struct lpc32xx_udc *udc = to_udc(gadget);

	spin_lock_irqsave(&udc->lock, flags);

	/* Doesn't need lock */
	if (udc->driver) {
		udc_clk_set(udc, 1);
		udc_enable(udc);
		pullup(udc, is_active);
	} else {
		stop_activity(udc);
		pullup(udc, 0);

		spin_unlock_irqrestore(&udc->lock, flags);
		/*
		 *  Wait for all the endpoints to disable,
		 *  before disabling clocks. Don't wait if
		 *  endpoints are not enabled.
		 */
		if (atomic_read(&udc->enabled_ep_cnt))
			wait_event_interruptible(udc->ep_disable_wait_queue,
				 (atomic_read(&udc->enabled_ep_cnt) == 0));

		spin_lock_irqsave(&udc->lock, flags);

		udc_clk_set(udc, 0);
	}

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}