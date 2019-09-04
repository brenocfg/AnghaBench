#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct phy_provider {int dummy; } ;
struct lpc18xx_usb_otg_phy {int /*<<< orphan*/  phy; int /*<<< orphan*/  clk; int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct lpc18xx_usb_otg_phy* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpc18xx_usb_otg_phy_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct lpc18xx_usb_otg_phy*) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_usb_otg_phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct lpc18xx_usb_otg_phy *lpc;

	lpc = devm_kzalloc(&pdev->dev, sizeof(*lpc), GFP_KERNEL);
	if (!lpc)
		return -ENOMEM;

	lpc->reg = syscon_node_to_regmap(pdev->dev.of_node->parent);
	if (IS_ERR(lpc->reg)) {
		dev_err(&pdev->dev, "failed to get syscon\n");
		return PTR_ERR(lpc->reg);
	}

	lpc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(lpc->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(lpc->clk);
	}

	lpc->phy = devm_phy_create(&pdev->dev, NULL, &lpc18xx_usb_otg_phy_ops);
	if (IS_ERR(lpc->phy)) {
		dev_err(&pdev->dev, "failed to create PHY\n");
		return PTR_ERR(lpc->phy);
	}

	phy_set_drvdata(lpc->phy, lpc);

	phy_provider = devm_of_phy_provider_register(&pdev->dev,
						     of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}