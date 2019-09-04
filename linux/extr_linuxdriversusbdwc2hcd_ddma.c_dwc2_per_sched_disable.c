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
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCFG ; 
 int HCFG_PERSCHEDENA ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dwc2_per_sched_disable(struct dwc2_hsotg *hsotg)
{
	u32 hcfg;
	unsigned long flags;

	spin_lock_irqsave(&hsotg->lock, flags);

	hcfg = dwc2_readl(hsotg, HCFG);
	if (!(hcfg & HCFG_PERSCHEDENA)) {
		/* already disabled */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		return;
	}

	hcfg &= ~HCFG_PERSCHEDENA;
	dev_vdbg(hsotg->dev, "Disabling Periodic schedule\n");
	dwc2_writel(hsotg, hcfg, HCFG);

	spin_unlock_irqrestore(&hsotg->lock, flags);
}