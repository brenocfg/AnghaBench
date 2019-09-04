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
struct xsphy_instance {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct mtk_xsphy {int dummy; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_USB2 ; 
 struct mtk_xsphy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct xsphy_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  u2_phy_instance_power_on (struct mtk_xsphy*,struct xsphy_instance*) ; 
 int /*<<< orphan*/  u2_phy_slew_rate_calibrate (struct mtk_xsphy*,struct xsphy_instance*) ; 

__attribute__((used)) static int mtk_phy_power_on(struct phy *phy)
{
	struct xsphy_instance *inst = phy_get_drvdata(phy);
	struct mtk_xsphy *xsphy = dev_get_drvdata(phy->dev.parent);

	if (inst->type == PHY_TYPE_USB2) {
		u2_phy_instance_power_on(xsphy, inst);
		u2_phy_slew_rate_calibrate(xsphy, inst);
	}

	return 0;
}