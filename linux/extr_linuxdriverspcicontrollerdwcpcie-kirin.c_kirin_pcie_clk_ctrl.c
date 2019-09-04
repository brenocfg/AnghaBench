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
struct kirin_pcie {int /*<<< orphan*/  phy_ref_clk; int /*<<< orphan*/  apb_sys_clk; int /*<<< orphan*/  apb_phy_clk; int /*<<< orphan*/  pcie_aclk; int /*<<< orphan*/  pcie_aux_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_CLK_FREQ ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_pcie_clk_ctrl(struct kirin_pcie *kirin_pcie, bool enable)
{
	int ret = 0;

	if (!enable)
		goto close_clk;

	ret = clk_set_rate(kirin_pcie->phy_ref_clk, REF_CLK_FREQ);
	if (ret)
		return ret;

	ret = clk_prepare_enable(kirin_pcie->phy_ref_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(kirin_pcie->apb_sys_clk);
	if (ret)
		goto apb_sys_fail;

	ret = clk_prepare_enable(kirin_pcie->apb_phy_clk);
	if (ret)
		goto apb_phy_fail;

	ret = clk_prepare_enable(kirin_pcie->pcie_aclk);
	if (ret)
		goto aclk_fail;

	ret = clk_prepare_enable(kirin_pcie->pcie_aux_clk);
	if (ret)
		goto aux_clk_fail;

	return 0;

close_clk:
	clk_disable_unprepare(kirin_pcie->pcie_aux_clk);
aux_clk_fail:
	clk_disable_unprepare(kirin_pcie->pcie_aclk);
aclk_fail:
	clk_disable_unprepare(kirin_pcie->apb_phy_clk);
apb_phy_fail:
	clk_disable_unprepare(kirin_pcie->apb_sys_clk);
apb_sys_fail:
	clk_disable_unprepare(kirin_pcie->phy_ref_clk);

	return ret;
}