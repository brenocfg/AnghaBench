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
struct rockchip_pcie_phy {int /*<<< orphan*/  pcie_mutex; int /*<<< orphan*/  init_cnt; int /*<<< orphan*/  clk_pciephy_ref; int /*<<< orphan*/  phy_rst; } ;
struct phy_pcie_instance {int dummy; } ;
struct phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phy_pcie_instance* phy_get_drvdata (struct phy*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 struct rockchip_pcie_phy* to_pcie_phy (struct phy_pcie_instance*) ; 

__attribute__((used)) static int rockchip_pcie_phy_init(struct phy *phy)
{
	struct phy_pcie_instance *inst = phy_get_drvdata(phy);
	struct rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);
	int err = 0;

	mutex_lock(&rk_phy->pcie_mutex);

	if (rk_phy->init_cnt++)
		goto err_out;

	err = clk_prepare_enable(rk_phy->clk_pciephy_ref);
	if (err) {
		dev_err(&phy->dev, "Fail to enable pcie ref clock.\n");
		goto err_refclk;
	}

	err = reset_control_assert(rk_phy->phy_rst);
	if (err) {
		dev_err(&phy->dev, "assert phy_rst err %d\n", err);
		goto err_reset;
	}

err_out:
	mutex_unlock(&rk_phy->pcie_mutex);
	return 0;

err_reset:

	clk_disable_unprepare(rk_phy->clk_pciephy_ref);
err_refclk:
	rk_phy->init_cnt--;
	mutex_unlock(&rk_phy->pcie_mutex);
	return err;
}