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
struct exynos5_usbdrd_phy {int /*<<< orphan*/ * itpclk; int /*<<< orphan*/  dev; int /*<<< orphan*/ * utmiclk; int /*<<< orphan*/ * pipeclk; TYPE_1__* drv_data; int /*<<< orphan*/  extrefclk; int /*<<< orphan*/ * ref_clk; int /*<<< orphan*/ * clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_common_clk_gate; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int exynos5_rate_to_clk (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_clk_handle(struct exynos5_usbdrd_phy *phy_drd)
{
	unsigned long ref_rate;
	int ret;

	phy_drd->clk = devm_clk_get(phy_drd->dev, "phy");
	if (IS_ERR(phy_drd->clk)) {
		dev_err(phy_drd->dev, "Failed to get phy clock\n");
		return PTR_ERR(phy_drd->clk);
	}

	phy_drd->ref_clk = devm_clk_get(phy_drd->dev, "ref");
	if (IS_ERR(phy_drd->ref_clk)) {
		dev_err(phy_drd->dev, "Failed to get phy reference clock\n");
		return PTR_ERR(phy_drd->ref_clk);
	}
	ref_rate = clk_get_rate(phy_drd->ref_clk);

	ret = exynos5_rate_to_clk(ref_rate, &phy_drd->extrefclk);
	if (ret) {
		dev_err(phy_drd->dev, "Clock rate (%ld) not supported\n",
			ref_rate);
		return ret;
	}

	if (!phy_drd->drv_data->has_common_clk_gate) {
		phy_drd->pipeclk = devm_clk_get(phy_drd->dev, "phy_pipe");
		if (IS_ERR(phy_drd->pipeclk)) {
			dev_info(phy_drd->dev,
				 "PIPE3 phy operational clock not specified\n");
			phy_drd->pipeclk = NULL;
		}

		phy_drd->utmiclk = devm_clk_get(phy_drd->dev, "phy_utmi");
		if (IS_ERR(phy_drd->utmiclk)) {
			dev_info(phy_drd->dev,
				 "UTMI phy operational clock not specified\n");
			phy_drd->utmiclk = NULL;
		}

		phy_drd->itpclk = devm_clk_get(phy_drd->dev, "itp");
		if (IS_ERR(phy_drd->itpclk)) {
			dev_info(phy_drd->dev,
				 "ITP clock from main OSC not specified\n");
			phy_drd->itpclk = NULL;
		}
	}

	return 0;
}