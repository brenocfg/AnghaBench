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
struct device {struct device_node* of_node; struct da8xx_usb_phy_platform_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct da8xx_usb_phy_platform_data {void* cfgchip; } ;
struct da8xx_usb_phy {void* regmap; void* usb20_phy; void* usb11_phy; void* phy_provider; void* usb20_clk; void* usb11_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PHY_INIT_BITS ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  da8xx_usb11_phy_ops ; 
 int /*<<< orphan*/  da8xx_usb20_phy_ops ; 
 int /*<<< orphan*/  da8xx_usb_phy_of_xlate ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct da8xx_usb_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_phy_create (struct device*,struct device_node*,int /*<<< orphan*/ *) ; 
 int phy_create_lookup (void*,char*,char*) ; 
 int /*<<< orphan*/  phy_set_drvdata (void*,struct da8xx_usb_phy*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da8xx_usb_phy*) ; 
 int /*<<< orphan*/  regmap_write_bits (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int da8xx_usb_phy_probe(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct da8xx_usb_phy_platform_data *pdata = dev->platform_data;
	struct device_node	*node = dev->of_node;
	struct da8xx_usb_phy	*d_phy;

	d_phy = devm_kzalloc(dev, sizeof(*d_phy), GFP_KERNEL);
	if (!d_phy)
		return -ENOMEM;

	if (pdata)
		d_phy->regmap = pdata->cfgchip;
	else
		d_phy->regmap = syscon_regmap_lookup_by_compatible(
							"ti,da830-cfgchip");
	if (IS_ERR(d_phy->regmap)) {
		dev_err(dev, "Failed to get syscon\n");
		return PTR_ERR(d_phy->regmap);
	}

	d_phy->usb11_clk = devm_clk_get(dev, "usb1_clk48");
	if (IS_ERR(d_phy->usb11_clk)) {
		dev_err(dev, "Failed to get usb1_clk48\n");
		return PTR_ERR(d_phy->usb11_clk);
	}

	d_phy->usb20_clk = devm_clk_get(dev, "usb0_clk48");
	if (IS_ERR(d_phy->usb20_clk)) {
		dev_err(dev, "Failed to get usb0_clk48\n");
		return PTR_ERR(d_phy->usb20_clk);
	}

	d_phy->usb11_phy = devm_phy_create(dev, node, &da8xx_usb11_phy_ops);
	if (IS_ERR(d_phy->usb11_phy)) {
		dev_err(dev, "Failed to create usb11 phy\n");
		return PTR_ERR(d_phy->usb11_phy);
	}

	d_phy->usb20_phy = devm_phy_create(dev, node, &da8xx_usb20_phy_ops);
	if (IS_ERR(d_phy->usb20_phy)) {
		dev_err(dev, "Failed to create usb20 phy\n");
		return PTR_ERR(d_phy->usb20_phy);
	}

	platform_set_drvdata(pdev, d_phy);
	phy_set_drvdata(d_phy->usb11_phy, d_phy);
	phy_set_drvdata(d_phy->usb20_phy, d_phy);

	if (node) {
		d_phy->phy_provider = devm_of_phy_provider_register(dev,
							da8xx_usb_phy_of_xlate);
		if (IS_ERR(d_phy->phy_provider)) {
			dev_err(dev, "Failed to create phy provider\n");
			return PTR_ERR(d_phy->phy_provider);
		}
	} else {
		int ret;

		ret = phy_create_lookup(d_phy->usb11_phy, "usb-phy",
					"ohci-da8xx");
		if (ret)
			dev_warn(dev, "Failed to create usb11 phy lookup\n");
		ret = phy_create_lookup(d_phy->usb20_phy, "usb-phy",
					"musb-da8xx");
		if (ret)
			dev_warn(dev, "Failed to create usb20 phy lookup\n");
	}

	regmap_write_bits(d_phy->regmap, CFGCHIP(2),
			  PHY_INIT_BITS, PHY_INIT_BITS);

	return 0;
}