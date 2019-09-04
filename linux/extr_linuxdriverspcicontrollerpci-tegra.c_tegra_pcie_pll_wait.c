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
struct tegra_pcie_soc {int /*<<< orphan*/  pads_pll_ctl; } ;
struct tegra_pcie {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PADS_PLL_CTL_LOCKDET ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int pads_readl (struct tegra_pcie*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int tegra_pcie_pll_wait(struct tegra_pcie *pcie, unsigned long timeout)
{
	const struct tegra_pcie_soc *soc = pcie->soc;
	u32 value;

	timeout = jiffies + msecs_to_jiffies(timeout);

	while (time_before(jiffies, timeout)) {
		value = pads_readl(pcie, soc->pads_pll_ctl);
		if (value & PADS_PLL_CTL_LOCKDET)
			return 0;
	}

	return -ETIMEDOUT;
}