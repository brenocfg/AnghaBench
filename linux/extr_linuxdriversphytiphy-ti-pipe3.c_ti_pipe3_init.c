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
struct ti_pipe3 {TYPE_1__* dev; int /*<<< orphan*/  pll_ctrl_base; int /*<<< orphan*/  pcie_pcs_reg; int /*<<< orphan*/  pcs_syscon; int /*<<< orphan*/  control_dev; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_CTRL_PCIE_PCS_DELAY_COUNT_SHIFT ; 
 int /*<<< orphan*/  PCIE_PCS_MASK ; 
 int /*<<< orphan*/  PLL_CONFIGURATION2 ; 
 int PLL_IDLE ; 
 int PLL_LOCK ; 
 int /*<<< orphan*/  PLL_STATUS ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_control_pcie_pcs (int /*<<< orphan*/ ,int) ; 
 struct ti_pipe3* phy_get_drvdata (struct phy*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_pipe3_calibrate (struct ti_pipe3*) ; 
 int /*<<< orphan*/  ti_pipe3_disable_clocks (struct ti_pipe3*) ; 
 int ti_pipe3_dpll_program (struct ti_pipe3*) ; 
 int ti_pipe3_dpll_wait_lock (struct ti_pipe3*) ; 
 int /*<<< orphan*/  ti_pipe3_enable_clocks (struct ti_pipe3*) ; 
 int ti_pipe3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pipe3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ti_pipe3_init(struct phy *x)
{
	struct ti_pipe3 *phy = phy_get_drvdata(x);
	u32 val;
	int ret = 0;

	ti_pipe3_enable_clocks(phy);
	/*
	 * Set pcie_pcs register to 0x96 for proper functioning of phy
	 * as recommended in AM572x TRM SPRUHZ6, section 18.5.2.2, table
	 * 18-1804.
	 */
	if (of_device_is_compatible(phy->dev->of_node, "ti,phy-pipe3-pcie")) {
		if (!phy->pcs_syscon) {
			omap_control_pcie_pcs(phy->control_dev, 0x96);
			return 0;
		}

		val = 0x96 << OMAP_CTRL_PCIE_PCS_DELAY_COUNT_SHIFT;
		ret = regmap_update_bits(phy->pcs_syscon, phy->pcie_pcs_reg,
					 PCIE_PCS_MASK, val);
		if (ret)
			return ret;

		ti_pipe3_calibrate(phy);

		return 0;
	}

	/* Bring it out of IDLE if it is IDLE */
	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_CONFIGURATION2);
	if (val & PLL_IDLE) {
		val &= ~PLL_IDLE;
		ti_pipe3_writel(phy->pll_ctrl_base, PLL_CONFIGURATION2, val);
		ret = ti_pipe3_dpll_wait_lock(phy);
	}

	/* SATA has issues if re-programmed when locked */
	val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_STATUS);
	if ((val & PLL_LOCK) && of_device_is_compatible(phy->dev->of_node,
							"ti,phy-pipe3-sata"))
		return ret;

	/* Program the DPLL */
	ret = ti_pipe3_dpll_program(phy);
	if (ret) {
		ti_pipe3_disable_clocks(phy);
		return -EINVAL;
	}

	return ret;
}