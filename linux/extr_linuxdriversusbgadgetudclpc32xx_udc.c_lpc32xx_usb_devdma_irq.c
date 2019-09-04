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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NUM_ENDPOINTS ; 
 int /*<<< orphan*/  USBD_EOTINTST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_EPDMAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_NDDRTINTST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_SYSERRTINTST (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_handle_dma_ep (struct lpc32xx_udc*,TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t lpc32xx_usb_devdma_irq(int irq, void *_udc)
{
	struct lpc32xx_udc *udc = _udc;

	int i;
	u32 tmp;

	spin_lock(&udc->lock);

	/* Handle EP DMA EOT interrupts */
	tmp = readl(USBD_EOTINTST(udc->udp_baseaddr)) |
		(readl(USBD_EPDMAST(udc->udp_baseaddr)) &
		 readl(USBD_NDDRTINTST(udc->udp_baseaddr))) |
		readl(USBD_SYSERRTINTST(udc->udp_baseaddr));
	for (i = 1; i < NUM_ENDPOINTS; i++) {
		if (tmp & (1 << udc->ep[i].hwep_num))
			udc_handle_dma_ep(udc, &udc->ep[i]);
	}

	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}