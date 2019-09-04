#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mv_otg {int irq_status; TYPE_2__* pdata; TYPE_1__* op_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {scalar_t__ vbus; } ;
struct TYPE_3__ {int /*<<< orphan*/  otgsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int OTGSC_INTSTS_USB_ID ; 
 int OTGSC_STS_USB_ID ; 
 int /*<<< orphan*/  mv_otg_run_state_machine (struct mv_otg*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mv_otg_irq(int irq, void *dev)
{
	struct mv_otg *mvotg = dev;
	u32 otgsc;

	otgsc = readl(&mvotg->op_regs->otgsc);
	writel(otgsc, &mvotg->op_regs->otgsc);

	/*
	 * if we have vbus, then the vbus detection for B-device
	 * will be done by mv_otg_inputs_irq().
	 */
	if (mvotg->pdata->vbus)
		if ((otgsc & OTGSC_STS_USB_ID) &&
		    !(otgsc & OTGSC_INTSTS_USB_ID))
			return IRQ_NONE;

	if ((otgsc & mvotg->irq_status) == 0)
		return IRQ_NONE;

	mv_otg_run_state_machine(mvotg, 0);

	return IRQ_HANDLED;
}