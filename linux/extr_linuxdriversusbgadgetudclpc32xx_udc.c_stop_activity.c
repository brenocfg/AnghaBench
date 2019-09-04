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
struct usb_gadget_driver {int /*<<< orphan*/  (* disconnect ) (TYPE_1__*) ;} ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct lpc32xx_udc {int /*<<< orphan*/  lock; TYPE_1__ gadget; struct lpc32xx_ep* ep; scalar_t__ suspended; struct usb_gadget_driver* driver; } ;
struct lpc32xx_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int NUM_ENDPOINTS ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  isp1301_pullup_enable (struct lpc32xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuke (struct lpc32xx_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  udc_disable (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  udc_reinit (struct lpc32xx_udc*) ; 

__attribute__((used)) static void stop_activity(struct lpc32xx_udc *udc)
{
	struct usb_gadget_driver *driver = udc->driver;
	int i;

	if (udc->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	for (i = 0; i < NUM_ENDPOINTS; i++) {
		struct lpc32xx_ep *ep = &udc->ep[i];
		nuke(ep, -ESHUTDOWN);
	}
	if (driver) {
		spin_unlock(&udc->lock);
		driver->disconnect(&udc->gadget);
		spin_lock(&udc->lock);
	}

	isp1301_pullup_enable(udc, 0, 0);
	udc_disable(udc);
	udc_reinit(udc);
}