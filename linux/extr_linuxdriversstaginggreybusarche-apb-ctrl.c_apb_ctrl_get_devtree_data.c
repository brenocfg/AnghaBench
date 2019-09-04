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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct arche_apb_ctrl_drvdata {int resetn_gpio; int boot_ret_gpio; int pwroff_gpio; int clk_en_gpio; int spi_en_polarity_high; void* spi_en_gpio; void* pin_default; void* pinctrl; void* vio; void* vcore; void* pwrdn_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int devm_gpio_request_one (struct device*,int,int /*<<< orphan*/ ,char*) ; 
 void* devm_pinctrl_get (struct device*) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 void* pinctrl_lookup_state (void*,char*) ; 

__attribute__((used)) static int apb_ctrl_get_devtree_data(struct platform_device *pdev,
				     struct arche_apb_ctrl_drvdata *apb)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;

	apb->resetn_gpio = of_get_named_gpio(np, "reset-gpios", 0);
	if (apb->resetn_gpio < 0) {
		dev_err(dev, "failed to get reset gpio\n");
		return apb->resetn_gpio;
	}
	ret = devm_gpio_request_one(dev, apb->resetn_gpio,
				    GPIOF_OUT_INIT_LOW, "apb-reset");
	if (ret) {
		dev_err(dev, "Failed requesting reset gpio %d\n",
			apb->resetn_gpio);
		return ret;
	}

	apb->boot_ret_gpio = of_get_named_gpio(np, "boot-ret-gpios", 0);
	if (apb->boot_ret_gpio < 0) {
		dev_err(dev, "failed to get boot retention gpio\n");
		return apb->boot_ret_gpio;
	}
	ret = devm_gpio_request_one(dev, apb->boot_ret_gpio,
				    GPIOF_OUT_INIT_LOW, "boot retention");
	if (ret) {
		dev_err(dev, "Failed requesting bootret gpio %d\n",
			apb->boot_ret_gpio);
		return ret;
	}

	/* It's not mandatory to support power management interface */
	apb->pwroff_gpio = of_get_named_gpio(np, "pwr-off-gpios", 0);
	if (apb->pwroff_gpio < 0) {
		dev_err(dev, "failed to get power off gpio\n");
		return apb->pwroff_gpio;
	}
	ret = devm_gpio_request_one(dev, apb->pwroff_gpio,
				    GPIOF_IN, "pwroff_n");
	if (ret) {
		dev_err(dev, "Failed requesting pwroff_n gpio %d\n",
			apb->pwroff_gpio);
		return ret;
	}

	/* Do not make clock mandatory as of now (for DB3) */
	apb->clk_en_gpio = of_get_named_gpio(np, "clock-en-gpio", 0);
	if (apb->clk_en_gpio < 0) {
		dev_warn(dev, "failed to get clock en gpio\n");
	} else if (gpio_is_valid(apb->clk_en_gpio)) {
		ret = devm_gpio_request_one(dev, apb->clk_en_gpio,
					    GPIOF_OUT_INIT_LOW, "apb_clk_en");
		if (ret) {
			dev_warn(dev, "Failed requesting APB clock en gpio %d\n",
				 apb->clk_en_gpio);
			return ret;
		}
	}

	apb->pwrdn_gpio = of_get_named_gpio(np, "pwr-down-gpios", 0);
	if (apb->pwrdn_gpio < 0)
		dev_warn(dev, "failed to get power down gpio\n");

	/* Regulators are optional, as we may have fixed supply coming in */
	apb->vcore = devm_regulator_get(dev, "vcore");
	if (IS_ERR(apb->vcore))
		dev_warn(dev, "no core regulator found\n");

	apb->vio = devm_regulator_get(dev, "vio");
	if (IS_ERR(apb->vio))
		dev_warn(dev, "no IO regulator found\n");

	apb->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(apb->pinctrl)) {
		dev_err(&pdev->dev, "could not get pinctrl handle\n");
		return PTR_ERR(apb->pinctrl);
	}
	apb->pin_default = pinctrl_lookup_state(apb->pinctrl, "default");
	if (IS_ERR(apb->pin_default)) {
		dev_err(&pdev->dev, "could not get default pin state\n");
		return PTR_ERR(apb->pin_default);
	}

	/* Only applicable for platform >= V2 */
	apb->spi_en_gpio = of_get_named_gpio(np, "spi-en-gpio", 0);
	if (apb->spi_en_gpio >= 0) {
		if (of_property_read_bool(pdev->dev.of_node,
					  "spi-en-active-high"))
			apb->spi_en_polarity_high = true;
	}

	return 0;
}