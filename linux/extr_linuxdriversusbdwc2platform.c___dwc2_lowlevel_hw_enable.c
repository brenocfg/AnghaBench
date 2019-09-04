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
struct platform_device {int dummy; } ;
struct dwc2_hsotg {int /*<<< orphan*/  phy; TYPE_1__* plat; scalar_t__ uphy; scalar_t__ clk; int /*<<< orphan*/  supplies; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* phy_init ) (struct platform_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  phy_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int usb_phy_init (scalar_t__) ; 

__attribute__((used)) static int __dwc2_lowlevel_hw_enable(struct dwc2_hsotg *hsotg)
{
	struct platform_device *pdev = to_platform_device(hsotg->dev);
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(hsotg->supplies),
				    hsotg->supplies);
	if (ret)
		return ret;

	if (hsotg->clk) {
		ret = clk_prepare_enable(hsotg->clk);
		if (ret)
			return ret;
	}

	if (hsotg->uphy) {
		ret = usb_phy_init(hsotg->uphy);
	} else if (hsotg->plat && hsotg->plat->phy_init) {
		ret = hsotg->plat->phy_init(pdev, hsotg->plat->phy_type);
	} else {
		ret = phy_power_on(hsotg->phy);
		if (ret == 0)
			ret = phy_init(hsotg->phy);
	}

	return ret;
}