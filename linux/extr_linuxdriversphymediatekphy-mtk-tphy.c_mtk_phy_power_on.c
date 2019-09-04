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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct mtk_tphy {int dummy; } ;
struct mtk_phy_instance {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_PCIE ; 
 scalar_t__ PHY_TYPE_USB2 ; 
 struct mtk_tphy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hs_slew_rate_calibrate (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 int /*<<< orphan*/  pcie_phy_instance_power_on (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 struct mtk_phy_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  u2_phy_instance_power_on (struct mtk_tphy*,struct mtk_phy_instance*) ; 

__attribute__((used)) static int mtk_phy_power_on(struct phy *phy)
{
	struct mtk_phy_instance *instance = phy_get_drvdata(phy);
	struct mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);

	if (instance->type == PHY_TYPE_USB2) {
		u2_phy_instance_power_on(tphy, instance);
		hs_slew_rate_calibrate(tphy, instance);
	} else if (instance->type == PHY_TYPE_PCIE) {
		pcie_phy_instance_power_on(tphy, instance);
	}

	return 0;
}