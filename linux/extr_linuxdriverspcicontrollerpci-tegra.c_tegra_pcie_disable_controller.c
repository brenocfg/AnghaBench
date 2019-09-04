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
struct tegra_pcie {int /*<<< orphan*/  dev; TYPE_1__* soc; int /*<<< orphan*/  pcie_xrst; } ;
struct TYPE_2__ {scalar_t__ program_uphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int tegra_pcie_phy_power_off (struct tegra_pcie*) ; 

__attribute__((used)) static void tegra_pcie_disable_controller(struct tegra_pcie *pcie)
{
	int err;

	reset_control_assert(pcie->pcie_xrst);

	if (pcie->soc->program_uphy) {
		err = tegra_pcie_phy_power_off(pcie);
		if (err < 0)
			dev_err(pcie->dev, "failed to power off PHY(s): %d\n",
				err);
	}
}