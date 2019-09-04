#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_usb_instance {TYPE_2__* phy_cfg; } ;
struct phy {int dummy; } ;
struct exynos5_usbdrd_phy {int /*<<< orphan*/  utmiclk; int /*<<< orphan*/  pipeclk; int /*<<< orphan*/  itpclk; TYPE_1__* drv_data; int /*<<< orphan*/  ref_clk; scalar_t__ vbus_boost; scalar_t__ vbus; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* phy_isol ) (struct phy_usb_instance*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  has_common_clk_gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct phy_usb_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct phy_usb_instance*,int) ; 
 struct exynos5_usbdrd_phy* to_usbdrd_phy (struct phy_usb_instance*) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_power_off(struct phy *phy)
{
	struct phy_usb_instance *inst = phy_get_drvdata(phy);
	struct exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	dev_dbg(phy_drd->dev, "Request to power_off usbdrd_phy phy\n");

	/* Power-off the PHY */
	inst->phy_cfg->phy_isol(inst, 1);

	/* Disable VBUS supply */
	if (phy_drd->vbus)
		regulator_disable(phy_drd->vbus);
	if (phy_drd->vbus_boost)
		regulator_disable(phy_drd->vbus_boost);

	clk_disable_unprepare(phy_drd->ref_clk);
	if (!phy_drd->drv_data->has_common_clk_gate) {
		clk_disable_unprepare(phy_drd->itpclk);
		clk_disable_unprepare(phy_drd->pipeclk);
		clk_disable_unprepare(phy_drd->utmiclk);
	}

	return 0;
}