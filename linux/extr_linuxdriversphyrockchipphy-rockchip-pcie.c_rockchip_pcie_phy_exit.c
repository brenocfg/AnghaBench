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
struct rockchip_pcie_phy {int /*<<< orphan*/  pcie_mutex; int /*<<< orphan*/  clk_pciephy_ref; scalar_t__ init_cnt; } ;
struct phy_pcie_instance {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phy_pcie_instance* phy_get_drvdata (struct phy*) ; 
 struct rockchip_pcie_phy* to_pcie_phy (struct phy_pcie_instance*) ; 

__attribute__((used)) static int rockchip_pcie_phy_exit(struct phy *phy)
{
	struct phy_pcie_instance *inst = phy_get_drvdata(phy);
	struct rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);

	mutex_lock(&rk_phy->pcie_mutex);

	if (--rk_phy->init_cnt)
		goto err_init_cnt;

	clk_disable_unprepare(rk_phy->clk_pciephy_ref);

err_init_cnt:
	mutex_unlock(&rk_phy->pcie_mutex);
	return 0;
}