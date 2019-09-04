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
struct dwc3_exynos {int /*<<< orphan*/ * clk; int /*<<< orphan*/ * susp_clk; int /*<<< orphan*/ * axius_clk; int /*<<< orphan*/ * vdd33; int /*<<< orphan*/ * vdd10; int /*<<< orphan*/  usb3_phy; int /*<<< orphan*/  usb2_phy; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct dwc3_exynos* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int dwc3_exynos_register_phys (struct dwc3_exynos*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dwc3_exynos*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dwc3_exynos_probe(struct platform_device *pdev)
{
	struct dwc3_exynos	*exynos;
	struct device		*dev = &pdev->dev;
	struct device_node	*node = dev->of_node;

	int			ret;

	exynos = devm_kzalloc(dev, sizeof(*exynos), GFP_KERNEL);
	if (!exynos)
		return -ENOMEM;

	platform_set_drvdata(pdev, exynos);

	exynos->dev	= dev;

	exynos->clk = devm_clk_get(dev, "usbdrd30");
	if (IS_ERR(exynos->clk)) {
		dev_err(dev, "couldn't get clock\n");
		return -EINVAL;
	}
	ret = clk_prepare_enable(exynos->clk);
	if (ret)
		return ret;

	exynos->susp_clk = devm_clk_get(dev, "usbdrd30_susp_clk");
	if (IS_ERR(exynos->susp_clk))
		exynos->susp_clk = NULL;
	ret = clk_prepare_enable(exynos->susp_clk);
	if (ret)
		goto susp_clk_err;

	if (of_device_is_compatible(node, "samsung,exynos7-dwusb3")) {
		exynos->axius_clk = devm_clk_get(dev, "usbdrd30_axius_clk");
		if (IS_ERR(exynos->axius_clk)) {
			dev_err(dev, "no AXI UpScaler clk specified\n");
			ret = -ENODEV;
			goto axius_clk_err;
		}
		ret = clk_prepare_enable(exynos->axius_clk);
		if (ret)
			goto axius_clk_err;
	} else {
		exynos->axius_clk = NULL;
	}

	exynos->vdd33 = devm_regulator_get(dev, "vdd33");
	if (IS_ERR(exynos->vdd33)) {
		ret = PTR_ERR(exynos->vdd33);
		goto vdd33_err;
	}
	ret = regulator_enable(exynos->vdd33);
	if (ret) {
		dev_err(dev, "Failed to enable VDD33 supply\n");
		goto vdd33_err;
	}

	exynos->vdd10 = devm_regulator_get(dev, "vdd10");
	if (IS_ERR(exynos->vdd10)) {
		ret = PTR_ERR(exynos->vdd10);
		goto vdd10_err;
	}
	ret = regulator_enable(exynos->vdd10);
	if (ret) {
		dev_err(dev, "Failed to enable VDD10 supply\n");
		goto vdd10_err;
	}

	ret = dwc3_exynos_register_phys(exynos);
	if (ret) {
		dev_err(dev, "couldn't register PHYs\n");
		goto phys_err;
	}

	if (node) {
		ret = of_platform_populate(node, NULL, NULL, dev);
		if (ret) {
			dev_err(dev, "failed to add dwc3 core\n");
			goto populate_err;
		}
	} else {
		dev_err(dev, "no device node, failed to add dwc3 core\n");
		ret = -ENODEV;
		goto populate_err;
	}

	return 0;

populate_err:
	platform_device_unregister(exynos->usb2_phy);
	platform_device_unregister(exynos->usb3_phy);
phys_err:
	regulator_disable(exynos->vdd10);
vdd10_err:
	regulator_disable(exynos->vdd33);
vdd33_err:
	clk_disable_unprepare(exynos->axius_clk);
axius_clk_err:
	clk_disable_unprepare(exynos->susp_clk);
susp_clk_err:
	clk_disable_unprepare(exynos->clk);
	return ret;
}