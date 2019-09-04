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
struct ti_pipe3 {int sata_refclk_enabled; struct phy* refclk; struct device* dev; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct phy*) ; 
 struct ti_pipe3* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct ti_pipe3*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ti_pipe3*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int ti_pipe3_get_clk (struct ti_pipe3*) ; 
 int ti_pipe3_get_pll_base (struct ti_pipe3*) ; 
 int ti_pipe3_get_sysctrl (struct ti_pipe3*) ; 
 int ti_pipe3_get_tx_rx_base (struct ti_pipe3*) ; 
 int /*<<< orphan*/  ti_pipe3_power_off (struct phy*) ; 

__attribute__((used)) static int ti_pipe3_probe(struct platform_device *pdev)
{
	struct ti_pipe3 *phy;
	struct phy *generic_phy;
	struct phy_provider *phy_provider;
	struct device_node *node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	int ret;

	phy = devm_kzalloc(dev, sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	phy->dev		= dev;

	ret = ti_pipe3_get_pll_base(phy);
	if (ret)
		return ret;

	ret = ti_pipe3_get_tx_rx_base(phy);
	if (ret)
		return ret;

	ret = ti_pipe3_get_sysctrl(phy);
	if (ret)
		return ret;

	ret = ti_pipe3_get_clk(phy);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, phy);
	pm_runtime_enable(dev);

	/*
	 * Prevent auto-disable of refclk for SATA PHY due to Errata i783
	 */
	if (of_device_is_compatible(node, "ti,phy-pipe3-sata")) {
		if (!IS_ERR(phy->refclk)) {
			clk_prepare_enable(phy->refclk);
			phy->sata_refclk_enabled = true;
		}
	}

	generic_phy = devm_phy_create(dev, NULL, &ops);
	if (IS_ERR(generic_phy))
		return PTR_ERR(generic_phy);

	phy_set_drvdata(generic_phy, phy);

	ti_pipe3_power_off(generic_phy);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}