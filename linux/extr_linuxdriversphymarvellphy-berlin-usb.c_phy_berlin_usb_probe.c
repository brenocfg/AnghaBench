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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct phy_provider {int dummy; } ;
struct phy_berlin_usb_priv {int /*<<< orphan*/  pll_divider; struct phy* rst_ctrl; struct phy* base; } ;
struct phy {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct phy* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct phy_berlin_usb_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct phy* devm_reset_control_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_berlin_usb_of_match ; 
 int /*<<< orphan*/  phy_berlin_usb_ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct phy_berlin_usb_priv*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_berlin_usb_probe(struct platform_device *pdev)
{
	const struct of_device_id *match =
		of_match_device(phy_berlin_usb_of_match, &pdev->dev);
	struct phy_berlin_usb_priv *priv;
	struct resource *res;
	struct phy *phy;
	struct phy_provider *phy_provider;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->rst_ctrl = devm_reset_control_get(&pdev->dev, NULL);
	if (IS_ERR(priv->rst_ctrl))
		return PTR_ERR(priv->rst_ctrl);

	priv->pll_divider = *((u32 *)match->data);

	phy = devm_phy_create(&pdev->dev, NULL, &phy_berlin_usb_ops);
	if (IS_ERR(phy)) {
		dev_err(&pdev->dev, "failed to create PHY\n");
		return PTR_ERR(phy);
	}

	phy_set_drvdata(phy, priv);

	phy_provider =
		devm_of_phy_provider_register(&pdev->dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}