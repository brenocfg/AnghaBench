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
typedef  int /*<<< orphan*/  u32 ;
struct pmic_wrapper {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PWRAP_INT_CLR ; 
 int /*<<< orphan*/  PWRAP_INT_FLG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrap_readl (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pwrap_interrupt(int irqno, void *dev_id)
{
	u32 rdata;
	struct pmic_wrapper *wrp = dev_id;

	rdata = pwrap_readl(wrp, PWRAP_INT_FLG);

	dev_err(wrp->dev, "unexpected interrupt int=0x%x\n", rdata);

	pwrap_writel(wrp, 0xffffffff, PWRAP_INT_CLR);

	return IRQ_HANDLED;
}