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
typedef  int u32 ;
struct lpc32xx_udc {int /*<<< orphan*/  lock; TYPE_1__* ep; int /*<<< orphan*/  udp_baseaddr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int hwep_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_IN ; 
 int EP_MASK_SEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EP_OUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NUM_ENDPOINTS ; 
 int /*<<< orphan*/  USBD_DEVINTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EPINTST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EP_FAST ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_handle_ep0_in (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  udc_handle_ep0_out (struct lpc32xx_udc*) ; 
 int /*<<< orphan*/  udc_handle_eps (struct lpc32xx_udc*,TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lpc32xx_usb_hp_irq(int irq, void *_udc)
{
	u32 tmp;
	struct lpc32xx_udc *udc = _udc;

	spin_lock(&udc->lock);

	/* Read the device status register */
	writel(USBD_EP_FAST, USBD_DEVINTCLR(udc->udp_baseaddr));

	/* Endpoints */
	tmp = readl(USBD_EPINTST(udc->udp_baseaddr));

	/* Special handling for EP0 */
	if (tmp & (EP_MASK_SEL(0, EP_OUT) | EP_MASK_SEL(0, EP_IN))) {
		/* Handle EP0 IN */
		if (tmp & (EP_MASK_SEL(0, EP_IN)))
			udc_handle_ep0_in(udc);

		/* Handle EP0 OUT */
		if (tmp & (EP_MASK_SEL(0, EP_OUT)))
			udc_handle_ep0_out(udc);
	}

	/* All other EPs */
	if (tmp & ~(EP_MASK_SEL(0, EP_OUT) | EP_MASK_SEL(0, EP_IN))) {
		int i;

		/* Handle other EP interrupts */
		for (i = 1; i < NUM_ENDPOINTS; i++) {
			if (tmp & (1 << udc->ep[i].hwep_num))
				udc_handle_eps(udc, &udc->ep[i]);
		}
	}

	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}