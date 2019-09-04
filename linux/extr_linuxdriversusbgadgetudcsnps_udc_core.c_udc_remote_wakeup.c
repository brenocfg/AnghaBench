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
typedef  int /*<<< orphan*/  u32 ;
struct udc {int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMD_CLEAR_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  UDC_DEVCTL_RES ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udc_remote_wakeup(struct udc *dev)
{
	unsigned long flags;
	u32 tmp;

	DBG(dev, "UDC initiates remote wakeup\n");

	spin_lock_irqsave(&dev->lock, flags);

	tmp = readl(&dev->regs->ctl);
	tmp |= AMD_BIT(UDC_DEVCTL_RES);
	writel(tmp, &dev->regs->ctl);
	tmp &= AMD_CLEAR_BIT(UDC_DEVCTL_RES);
	writel(tmp, &dev->regs->ctl);

	spin_unlock_irqrestore(&dev->lock, flags);
	return 0;
}