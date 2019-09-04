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
struct gem {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PCS_MIICTRL ; 
 int PCS_MIICTRL_RST ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_pcs_reset(struct gem *gp)
{
	int limit;
	u32 val;

	/* Reset PCS unit. */
	val = readl(gp->regs + PCS_MIICTRL);
	val |= PCS_MIICTRL_RST;
	writel(val, gp->regs + PCS_MIICTRL);

	limit = 32;
	while (readl(gp->regs + PCS_MIICTRL) & PCS_MIICTRL_RST) {
		udelay(100);
		if (limit-- <= 0)
			break;
	}
	if (limit < 0)
		netdev_warn(gp->dev, "PCS reset bit would not clear\n");
}