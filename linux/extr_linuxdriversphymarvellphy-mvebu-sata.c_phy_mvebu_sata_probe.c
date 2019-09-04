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
struct resource {int dummy; } ;
struct priv {struct phy_provider* clk; struct phy_provider* base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct phy_provider phy ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 struct phy_provider* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct phy_provider* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_mvebu_sata_ops ; 
 int /*<<< orphan*/  phy_mvebu_sata_power_off (struct phy_provider*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct priv*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_mvebu_sata_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct resource *res;
	struct priv *priv;
	struct phy *phy;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, "sata");
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	phy = devm_phy_create(&pdev->dev, NULL, &phy_mvebu_sata_ops);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_register(&pdev->dev,
						     of_phy_simple_xlate);
	if (IS_ERR(phy_provider))
		return PTR_ERR(phy_provider);

	/* The boot loader may of left it on. Turn it off. */
	phy_mvebu_sata_power_off(phy);

	return 0;
}