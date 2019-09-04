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
struct rockchip_pcie_phy {int /*<<< orphan*/  pcie_mutex; int /*<<< orphan*/  pwr_cnt; int /*<<< orphan*/  phy_rst; TYPE_1__* phy_data; int /*<<< orphan*/  reg_base; } ;
struct phy_pcie_instance {scalar_t__ index; } ;
struct phy {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcie_status; int /*<<< orphan*/  pcie_conf; int /*<<< orphan*/  pcie_laneoff; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HIWORD_UPDATE (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PHY_CFG_ADDR_MASK ; 
 scalar_t__ PHY_CFG_ADDR_SHIFT ; 
 int /*<<< orphan*/  PHY_CFG_CLK_SCC ; 
 int /*<<< orphan*/  PHY_CFG_CLK_TEST ; 
 int /*<<< orphan*/  PHY_CFG_PLL_100M ; 
 int PHY_CFG_PLL_LOCK ; 
 int /*<<< orphan*/  PHY_CFG_SEPE_RATE ; 
 scalar_t__ PHY_LANE_IDLE_A_SHIFT ; 
 int /*<<< orphan*/  PHY_LANE_IDLE_MASK ; 
 int /*<<< orphan*/  PHY_LANE_IDLE_OFF ; 
 int PHY_PLL_LOCKED ; 
 int PHY_PLL_OUTPUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phy_pcie_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_wr_cfg (struct rockchip_pcie_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 struct rockchip_pcie_phy* to_pcie_phy (struct phy_pcie_instance*) ; 

__attribute__((used)) static int rockchip_pcie_phy_power_on(struct phy *phy)
{
	struct phy_pcie_instance *inst = phy_get_drvdata(phy);
	struct rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);
	int err = 0;
	u32 status;
	unsigned long timeout;

	mutex_lock(&rk_phy->pcie_mutex);

	if (rk_phy->pwr_cnt++)
		goto err_out;

	err = reset_control_deassert(rk_phy->phy_rst);
	if (err) {
		dev_err(&phy->dev, "deassert phy_rst err %d\n", err);
		goto err_pwr_cnt;
	}

	regmap_write(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_PLL_LOCK,
				   PHY_CFG_ADDR_MASK,
				   PHY_CFG_ADDR_SHIFT));

	regmap_write(rk_phy->reg_base,
		     rk_phy->phy_data->pcie_laneoff,
		     HIWORD_UPDATE(!PHY_LANE_IDLE_OFF,
				   PHY_LANE_IDLE_MASK,
				   PHY_LANE_IDLE_A_SHIFT + inst->index));

	/*
	 * No documented timeout value for phy operation below,
	 * so we make it large enough here. And we use loop-break
	 * method which should not be harmful.
	 */
	timeout = jiffies + msecs_to_jiffies(1000);

	err = -EINVAL;
	while (time_before(jiffies, timeout)) {
		regmap_read(rk_phy->reg_base,
			    rk_phy->phy_data->pcie_status,
			    &status);
		if (status & PHY_PLL_LOCKED) {
			dev_dbg(&phy->dev, "pll locked!\n");
			err = 0;
			break;
		}
		msleep(20);
	}

	if (err) {
		dev_err(&phy->dev, "pll lock timeout!\n");
		goto err_pll_lock;
	}

	phy_wr_cfg(rk_phy, PHY_CFG_CLK_TEST, PHY_CFG_SEPE_RATE);
	phy_wr_cfg(rk_phy, PHY_CFG_CLK_SCC, PHY_CFG_PLL_100M);

	err = -ETIMEDOUT;
	while (time_before(jiffies, timeout)) {
		regmap_read(rk_phy->reg_base,
			    rk_phy->phy_data->pcie_status,
			    &status);
		if (!(status & PHY_PLL_OUTPUT)) {
			dev_dbg(&phy->dev, "pll output enable done!\n");
			err = 0;
			break;
		}
		msleep(20);
	}

	if (err) {
		dev_err(&phy->dev, "pll output enable timeout!\n");
		goto err_pll_lock;
	}

	regmap_write(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_PLL_LOCK,
				   PHY_CFG_ADDR_MASK,
				   PHY_CFG_ADDR_SHIFT));
	err = -EINVAL;
	while (time_before(jiffies, timeout)) {
		regmap_read(rk_phy->reg_base,
			    rk_phy->phy_data->pcie_status,
			    &status);
		if (status & PHY_PLL_LOCKED) {
			dev_dbg(&phy->dev, "pll relocked!\n");
			err = 0;
			break;
		}
		msleep(20);
	}

	if (err) {
		dev_err(&phy->dev, "pll relock timeout!\n");
		goto err_pll_lock;
	}

err_out:
	mutex_unlock(&rk_phy->pcie_mutex);
	return 0;

err_pll_lock:
	reset_control_assert(rk_phy->phy_rst);
err_pwr_cnt:
	rk_phy->pwr_cnt--;
	mutex_unlock(&rk_phy->pcie_mutex);
	return err;
}