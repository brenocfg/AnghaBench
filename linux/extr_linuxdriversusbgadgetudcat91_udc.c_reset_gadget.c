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
struct usb_gadget_driver {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct at91_udc {int /*<<< orphan*/  lock; TYPE_1__ gadget; struct at91_ep* ep; scalar_t__ suspended; struct usb_gadget_driver* driver; } ;
struct at91_ep {int stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int NUM_ENDPOINTS ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  nuke (struct at91_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_reinit (struct at91_udc*) ; 
 int /*<<< orphan*/  usb_gadget_udc_reset (TYPE_1__*,struct usb_gadget_driver*) ; 

__attribute__((used)) static void reset_gadget(struct at91_udc *udc)
{
	struct usb_gadget_driver *driver = udc->driver;
	int i;

	if (udc->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	for (i = 0; i < NUM_ENDPOINTS; i++) {
		struct at91_ep *ep = &udc->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}
	if (driver) {
		spin_unlock(&udc->lock);
		usb_gadget_udc_reset(&udc->gadget, driver);
		spin_lock(&udc->lock);
	}

	udc_reinit(udc);
}