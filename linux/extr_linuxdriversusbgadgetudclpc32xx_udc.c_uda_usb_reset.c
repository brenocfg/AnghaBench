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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct lpc32xx_udc {struct lpc32xx_ep* ep; TYPE_1__ gadget; } ;
struct lpc32xx_ep {scalar_t__ req_pending; } ;

/* Variables and functions */
 size_t NUM_ENDPOINTS ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  udc_enable (struct lpc32xx_udc*) ; 

__attribute__((used)) static void uda_usb_reset(struct lpc32xx_udc *udc)
{
	u32 i = 0;
	/* Re-init device controller and EP0 */
	udc_enable(udc);
	udc->gadget.speed = USB_SPEED_FULL;

	for (i = 1; i < NUM_ENDPOINTS; i++) {
		struct lpc32xx_ep *ep = &udc->ep[i];
		ep->req_pending = 0;
	}
}