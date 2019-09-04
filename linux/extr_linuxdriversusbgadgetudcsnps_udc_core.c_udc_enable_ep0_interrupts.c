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
struct udc {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_irqmsk; } ;

/* Variables and functions */
 int AMD_UNMASK_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  UDC_EPINT_IN_EP0 ; 
 int /*<<< orphan*/  UDC_EPINT_OUT_EP0 ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udc_enable_ep0_interrupts(struct udc *dev)
{
	u32 tmp;

	DBG(dev, "udc_enable_ep0_interrupts()\n");

	/* read irq mask */
	tmp = readl(&dev->regs->ep_irqmsk);
	/* enable ep0 irq's */
	tmp &= AMD_UNMASK_BIT(UDC_EPINT_IN_EP0)
		& AMD_UNMASK_BIT(UDC_EPINT_OUT_EP0);
	writel(tmp, &dev->regs->ep_irqmsk);

	return 0;
}