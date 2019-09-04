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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct hix5hd2_priv {struct phy* peri_ctrl; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hix5hd2_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hix5hd2_sata_phy_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct hix5hd2_priv*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct phy* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hix5hd2_sata_phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct phy *phy;
	struct hix5hd2_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;

	priv->base = devm_ioremap(dev, res->start, resource_size(res));
	if (!priv->base)
		return -ENOMEM;

	priv->peri_ctrl = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,peripheral-syscon");
	if (IS_ERR(priv->peri_ctrl))
		priv->peri_ctrl = NULL;

	phy = devm_phy_create(dev, NULL, &hix5hd2_sata_phy_ops);
	if (IS_ERR(phy)) {
		dev_err(dev, "failed to create PHY\n");
		return PTR_ERR(phy);
	}

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}