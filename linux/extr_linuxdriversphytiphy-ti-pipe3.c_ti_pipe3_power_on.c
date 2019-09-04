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
typedef  unsigned long u32 ;
struct ti_pipe3 {int /*<<< orphan*/  power_reg; int /*<<< orphan*/  phy_power_syscon; int /*<<< orphan*/  dev; int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  control_dev; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_MASK ; 
 unsigned long OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_MASK ; 
 unsigned long OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_SHIFT ; 
 unsigned long PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT ; 
 unsigned long PIPE3_PHY_TX_RX_POWERON ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_control_phy_power (int /*<<< orphan*/ ,int) ; 
 struct ti_pipe3* phy_get_drvdata (struct phy*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static int ti_pipe3_power_on(struct phy *x)
{
	u32 val;
	u32 mask;
	int ret;
	unsigned long rate;
	struct ti_pipe3 *phy = phy_get_drvdata(x);

	if (!phy->phy_power_syscon) {
		omap_control_phy_power(phy->control_dev, 1);
		return 0;
	}

	rate = clk_get_rate(phy->sys_clk);
	if (!rate) {
		dev_err(phy->dev, "Invalid clock rate\n");
		return -EINVAL;
	}
	rate = rate / 1000000;
	mask = OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_MASK |
		  OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_MASK;
	val = PIPE3_PHY_TX_RX_POWERON << PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT;
	val |= rate << OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_SHIFT;

	ret = regmap_update_bits(phy->phy_power_syscon, phy->power_reg,
				 mask, val);
	return ret;
}