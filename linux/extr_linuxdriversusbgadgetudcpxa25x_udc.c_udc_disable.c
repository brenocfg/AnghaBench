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
struct pxa25x_udc {TYPE_1__ gadget; } ;

/* Variables and functions */
 int UDCCR_REM ; 
 int UDCCR_SRM ; 
 int /*<<< orphan*/  UDCCR_UDE ; 
 int /*<<< orphan*/  UFNRH ; 
 int UFNRH_SIM ; 
 int /*<<< orphan*/  UICR0 ; 
 int /*<<< orphan*/  UICR1 ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ep0_idle (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  pullup_off () ; 
 int /*<<< orphan*/  udc_clear_mask_UDCCR (struct pxa25x_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_set_mask_UDCCR (struct pxa25x_udc*,int) ; 
 int /*<<< orphan*/  udc_set_reg (struct pxa25x_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void udc_disable(struct pxa25x_udc *dev)
{
	/* block all irqs */
	udc_set_mask_UDCCR(dev, UDCCR_SRM|UDCCR_REM);
	udc_set_reg(dev, UICR0, 0xff);
	udc_set_reg(dev, UICR1, 0xff);
	udc_set_reg(dev, UFNRH, UFNRH_SIM);

	/* if hardware supports it, disconnect from usb */
	pullup_off();

	udc_clear_mask_UDCCR(dev, UDCCR_UDE);

	ep0_idle (dev);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
}