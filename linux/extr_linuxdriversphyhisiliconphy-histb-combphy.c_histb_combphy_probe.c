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
typedef  void* u32 ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct histb_combphy_mode {void* mask; void* shift; void* reg; int /*<<< orphan*/  fixed; } ;
struct histb_combphy_priv {int /*<<< orphan*/  phy; int /*<<< orphan*/  por_rst; int /*<<< orphan*/  ref_clk; struct histb_combphy_mode mode; int /*<<< orphan*/  syscon; int /*<<< orphan*/  mmio; } ;
struct device_node {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct histb_combphy_priv*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct histb_combphy_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  histb_combphy_ops ; 
 int /*<<< orphan*/  histb_combphy_xlate ; 
 scalar_t__ is_mode_fixed (struct histb_combphy_mode*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node*,char*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct histb_combphy_priv*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int histb_combphy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct device *dev = &pdev->dev;
	struct histb_combphy_priv *priv;
	struct device_node *np = dev->of_node;
	struct histb_combphy_mode *mode;
	struct resource *res;
	u32 vals[3];
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->mmio = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->mmio)) {
		ret = PTR_ERR(priv->mmio);
		return ret;
	}

	priv->syscon = syscon_node_to_regmap(np->parent);
	if (IS_ERR(priv->syscon)) {
		dev_err(dev, "failed to find peri_ctrl syscon regmap\n");
		return PTR_ERR(priv->syscon);
	}

	mode = &priv->mode;
	mode->fixed = PHY_NONE;

	ret = of_property_read_u32(np, "hisilicon,fixed-mode", &mode->fixed);
	if (ret == 0)
		dev_dbg(dev, "found fixed phy mode %d\n", mode->fixed);

	ret = of_property_read_u32_array(np, "hisilicon,mode-select-bits",
					 vals, ARRAY_SIZE(vals));
	if (ret == 0) {
		if (is_mode_fixed(mode)) {
			dev_err(dev, "found select bits for fixed mode phy\n");
			return -EINVAL;
		}

		mode->reg = vals[0];
		mode->shift = vals[1];
		mode->mask = vals[2];
		dev_dbg(dev, "found mode select bits\n");
	} else {
		if (!is_mode_fixed(mode)) {
			dev_err(dev, "no valid select bits found for non-fixed phy\n");
			return -ENODEV;
		}
	}

	priv->ref_clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->ref_clk)) {
		dev_err(dev, "failed to find ref clock\n");
		return PTR_ERR(priv->ref_clk);
	}

	priv->por_rst = devm_reset_control_get(dev, NULL);
	if (IS_ERR(priv->por_rst)) {
		dev_err(dev, "failed to get poweron reset\n");
		return PTR_ERR(priv->por_rst);
	}

	priv->phy = devm_phy_create(dev, NULL, &histb_combphy_ops);
	if (IS_ERR(priv->phy)) {
		dev_err(dev, "failed to create combphy\n");
		return PTR_ERR(priv->phy);
	}

	dev_set_drvdata(dev, priv);
	phy_set_drvdata(priv->phy, priv);

	phy_provider = devm_of_phy_provider_register(dev, histb_combphy_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}