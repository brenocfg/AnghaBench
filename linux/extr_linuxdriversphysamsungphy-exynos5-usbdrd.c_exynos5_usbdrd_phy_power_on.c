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
struct phy_usb_instance {TYPE_1__* phy_cfg; } ;
struct phy {int dummy; } ;
struct exynos5_usbdrd_phy {int /*<<< orphan*/  pipeclk; int /*<<< orphan*/  utmiclk; int /*<<< orphan*/  itpclk; TYPE_2__* drv_data; int /*<<< orphan*/  ref_clk; scalar_t__ vbus_boost; int /*<<< orphan*/  dev; scalar_t__ vbus; } ;
struct TYPE_4__ {int /*<<< orphan*/  has_common_clk_gate; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_isol ) (struct phy_usb_instance*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct phy_usb_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct phy_usb_instance*,int /*<<< orphan*/ ) ; 
 struct exynos5_usbdrd_phy* to_usbdrd_phy (struct phy_usb_instance*) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_power_on(struct phy *phy)
{
	int ret;
	struct phy_usb_instance *inst = phy_get_drvdata(phy);
	struct exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	dev_dbg(phy_drd->dev, "Request to power_on usbdrd_phy phy\n");

	clk_prepare_enable(phy_drd->ref_clk);
	if (!phy_drd->drv_data->has_common_clk_gate) {
		clk_prepare_enable(phy_drd->pipeclk);
		clk_prepare_enable(phy_drd->utmiclk);
		clk_prepare_enable(phy_drd->itpclk);
	}

	/* Enable VBUS supply */
	if (phy_drd->vbus_boost) {
		ret = regulator_enable(phy_drd->vbus_boost);
		if (ret) {
			dev_err(phy_drd->dev,
				"Failed to enable VBUS boost supply\n");
			goto fail_vbus;
		}
	}

	if (phy_drd->vbus) {
		ret = regulator_enable(phy_drd->vbus);
		if (ret) {
			dev_err(phy_drd->dev, "Failed to enable VBUS supply\n");
			goto fail_vbus_boost;
		}
	}

	/* Power-on PHY*/
	inst->phy_cfg->phy_isol(inst, 0);

	return 0;

fail_vbus_boost:
	if (phy_drd->vbus_boost)
		regulator_disable(phy_drd->vbus_boost);

fail_vbus:
	clk_disable_unprepare(phy_drd->ref_clk);
	if (!phy_drd->drv_data->has_common_clk_gate) {
		clk_disable_unprepare(phy_drd->itpclk);
		clk_disable_unprepare(phy_drd->utmiclk);
		clk_disable_unprepare(phy_drd->pipeclk);
	}

	return ret;
}