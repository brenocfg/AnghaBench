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
struct mtk_tphy {int /*<<< orphan*/  u3phya_ref; } ;
struct mtk_phy_instance {scalar_t__ type; int /*<<< orphan*/  ref_clk; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mtk_tphy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct mtk_phy_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  u2_phy_instance_exit (struct mtk_tphy*,struct mtk_phy_instance*) ; 

__attribute__((used)) static int mtk_phy_exit(struct phy *phy)
{
	struct mtk_phy_instance *instance = phy_get_drvdata(phy);
	struct mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);

	if (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_exit(tphy, instance);

	clk_disable_unprepare(instance->ref_clk);
	clk_disable_unprepare(tphy->u3phya_ref);
	return 0;
}