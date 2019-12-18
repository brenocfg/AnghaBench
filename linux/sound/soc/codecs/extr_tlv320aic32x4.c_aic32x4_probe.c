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
struct regmap {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; struct aic32x4_pdata* platform_data; } ;
struct aic32x4_priv {int swapdacs; int rstn_gpio; char* mclk_name; scalar_t__ micpga_routing; scalar_t__ power_cfg; struct device* dev; } ;
struct aic32x4_pdata {int swapdacs; int rstn_gpio; scalar_t__ micpga_routing; scalar_t__ power_cfg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  aic32x4_dai ; 
 int /*<<< orphan*/  aic32x4_disable_regulators (struct aic32x4_priv*) ; 
 int aic32x4_parse_dt (struct aic32x4_priv*,struct device_node*) ; 
 int aic32x4_register_clocks (struct device*,char*) ; 
 int aic32x4_setup_regulators (struct device*,struct aic32x4_priv*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct aic32x4_priv*) ; 
 int devm_gpio_request_one (struct device*,int,int /*<<< orphan*/ ,char*) ; 
 struct aic32x4_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  soc_component_dev_aic32x4 ; 

int aic32x4_probe(struct device *dev, struct regmap *regmap)
{
	struct aic32x4_priv *aic32x4;
	struct aic32x4_pdata *pdata = dev->platform_data;
	struct device_node *np = dev->of_node;
	int ret;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	aic32x4 = devm_kzalloc(dev, sizeof(struct aic32x4_priv),
				   GFP_KERNEL);
	if (aic32x4 == NULL)
		return -ENOMEM;

	aic32x4->dev = dev;
	dev_set_drvdata(dev, aic32x4);

	if (pdata) {
		aic32x4->power_cfg = pdata->power_cfg;
		aic32x4->swapdacs = pdata->swapdacs;
		aic32x4->micpga_routing = pdata->micpga_routing;
		aic32x4->rstn_gpio = pdata->rstn_gpio;
		aic32x4->mclk_name = "mclk";
	} else if (np) {
		ret = aic32x4_parse_dt(aic32x4, np);
		if (ret) {
			dev_err(dev, "Failed to parse DT node\n");
			return ret;
		}
	} else {
		aic32x4->power_cfg = 0;
		aic32x4->swapdacs = false;
		aic32x4->micpga_routing = 0;
		aic32x4->rstn_gpio = -1;
		aic32x4->mclk_name = "mclk";
	}

	ret = aic32x4_register_clocks(dev, aic32x4->mclk_name);
	if (ret)
		return ret;

	if (gpio_is_valid(aic32x4->rstn_gpio)) {
		ret = devm_gpio_request_one(dev, aic32x4->rstn_gpio,
				GPIOF_OUT_INIT_LOW, "tlv320aic32x4 rstn");
		if (ret != 0)
			return ret;
	}

	ret = aic32x4_setup_regulators(dev, aic32x4);
	if (ret) {
		dev_err(dev, "Failed to setup regulators\n");
		return ret;
	}

	ret = devm_snd_soc_register_component(dev,
			&soc_component_dev_aic32x4, &aic32x4_dai, 1);
	if (ret) {
		dev_err(dev, "Failed to register component\n");
		aic32x4_disable_regulators(aic32x4);
		return ret;
	}

	return 0;
}