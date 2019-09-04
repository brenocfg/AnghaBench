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
typedef  int u32 ;
struct pxa_udc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int UDCCISR0_EP_MASK ; 
 int UDCCISR1_EP_MASK ; 
 int /*<<< orphan*/  UDCCR ; 
 int /*<<< orphan*/  UDCISR0 ; 
 int /*<<< orphan*/  UDCISR1 ; 
 int UDCISR1_IRCC ; 
 int UDCISR1_IRRS ; 
 int UDCISR1_IRRU ; 
 int UDCISR1_IRSU ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  irq_handle_data (int,struct pxa_udc*) ; 
 int /*<<< orphan*/  irq_udc_reconfig (struct pxa_udc*) ; 
 int /*<<< orphan*/  irq_udc_reset (struct pxa_udc*) ; 
 int /*<<< orphan*/  irq_udc_resume (struct pxa_udc*) ; 
 int /*<<< orphan*/  irq_udc_suspend (struct pxa_udc*) ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t pxa_udc_irq(int irq, void *_dev)
{
	struct pxa_udc *udc = _dev;
	u32 udcisr0 = udc_readl(udc, UDCISR0);
	u32 udcisr1 = udc_readl(udc, UDCISR1);
	u32 udccr = udc_readl(udc, UDCCR);
	u32 udcisr1_spec;

	dev_vdbg(udc->dev, "Interrupt, UDCISR0:0x%08x, UDCISR1:0x%08x, "
		 "UDCCR:0x%08x\n", udcisr0, udcisr1, udccr);

	udcisr1_spec = udcisr1 & 0xf8000000;
	if (unlikely(udcisr1_spec & UDCISR1_IRSU))
		irq_udc_suspend(udc);
	if (unlikely(udcisr1_spec & UDCISR1_IRRU))
		irq_udc_resume(udc);
	if (unlikely(udcisr1_spec & UDCISR1_IRCC))
		irq_udc_reconfig(udc);
	if (unlikely(udcisr1_spec & UDCISR1_IRRS))
		irq_udc_reset(udc);

	if ((udcisr0 & UDCCISR0_EP_MASK) | (udcisr1 & UDCCISR1_EP_MASK))
		irq_handle_data(irq, udc);

	return IRQ_HANDLED;
}