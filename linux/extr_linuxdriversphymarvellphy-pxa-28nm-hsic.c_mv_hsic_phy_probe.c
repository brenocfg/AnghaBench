#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct phy_provider {int dummy; } ;
struct mv_hsic_phy {int /*<<< orphan*/  phy; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mv_hsic_phy* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hsic_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct mv_hsic_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_hsic_phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct mv_hsic_phy *mv_phy;
	struct resource *r;

	mv_phy = devm_kzalloc(&pdev->dev, sizeof(*mv_phy), GFP_KERNEL);
	if (!mv_phy)
		return -ENOMEM;

	mv_phy->pdev = pdev;

	mv_phy->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(mv_phy->clk)) {
		dev_err(&pdev->dev, "failed to get clock.\n");
		return PTR_ERR(mv_phy->clk);
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mv_phy->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(mv_phy->base))
		return PTR_ERR(mv_phy->base);

	mv_phy->phy = devm_phy_create(&pdev->dev, pdev->dev.of_node, &hsic_ops);
	if (IS_ERR(mv_phy->phy))
		return PTR_ERR(mv_phy->phy);

	phy_set_drvdata(mv_phy->phy, mv_phy);

	phy_provider = devm_of_phy_provider_register(&pdev->dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}