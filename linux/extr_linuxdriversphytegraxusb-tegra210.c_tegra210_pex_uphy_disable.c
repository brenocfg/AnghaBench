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
struct tegra_xusb_pcie_pad {scalar_t__ enable; int /*<<< orphan*/  pll; int /*<<< orphan*/  rst; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; int /*<<< orphan*/  pcie; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_pcie_pad* to_pcie_pad (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra210_pex_uphy_disable(struct tegra_xusb_padctl *padctl)
{
	struct tegra_xusb_pcie_pad *pcie = to_pcie_pad(padctl->pcie);

	mutex_lock(&padctl->lock);

	if (WARN_ON(pcie->enable == 0))
		goto unlock;

	if (--pcie->enable > 0)
		goto unlock;

	reset_control_assert(pcie->rst);
	clk_disable_unprepare(pcie->pll);

unlock:
	mutex_unlock(&padctl->lock);
}