#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct regmap {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
typedef  struct regmap phy_provider ;
typedef  struct regmap phy ;
struct exynos5_usbdrd_phy_drvdata {int /*<<< orphan*/ * phy_cfg; int /*<<< orphan*/  pmu_offset_usbdrd0_phy; int /*<<< orphan*/  pmu_offset_usbdrd1_phy; } ;
struct exynos5_usbdrd_phy {struct device* dev; TYPE_1__* phys; struct regmap* vbus_boost; struct regmap* vbus; struct exynos5_usbdrd_phy_drvdata const* drv_data; struct regmap* reg_phy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int index; int /*<<< orphan*/ * phy_cfg; int /*<<< orphan*/  pmu_offset; struct regmap* reg_pmu; struct regmap* phy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int EXYNOS5_DRDPHYS_NUM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct exynos5_usbdrd_phy*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct regmap* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct exynos5_usbdrd_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct regmap* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int exynos5_usbdrd_phy_clk_handle (struct exynos5_usbdrd_phy*) ; 
 int /*<<< orphan*/  exynos5_usbdrd_phy_ops ; 
 int /*<<< orphan*/  exynos5_usbdrd_phy_xlate ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 struct exynos5_usbdrd_phy_drvdata* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct regmap*,TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct exynos5_usbdrd_phy *phy_drd;
	struct phy_provider *phy_provider;
	struct resource *res;
	const struct exynos5_usbdrd_phy_drvdata *drv_data;
	struct regmap *reg_pmu;
	u32 pmu_offset;
	int i, ret;
	int channel;

	phy_drd = devm_kzalloc(dev, sizeof(*phy_drd), GFP_KERNEL);
	if (!phy_drd)
		return -ENOMEM;

	dev_set_drvdata(dev, phy_drd);
	phy_drd->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	phy_drd->reg_phy = devm_ioremap_resource(dev, res);
	if (IS_ERR(phy_drd->reg_phy))
		return PTR_ERR(phy_drd->reg_phy);

	drv_data = of_device_get_match_data(dev);
	if (!drv_data)
		return -EINVAL;

	phy_drd->drv_data = drv_data;

	ret = exynos5_usbdrd_phy_clk_handle(phy_drd);
	if (ret) {
		dev_err(dev, "Failed to initialize clocks\n");
		return ret;
	}

	reg_pmu = syscon_regmap_lookup_by_phandle(dev->of_node,
						   "samsung,pmu-syscon");
	if (IS_ERR(reg_pmu)) {
		dev_err(dev, "Failed to lookup PMU regmap\n");
		return PTR_ERR(reg_pmu);
	}

	/*
	 * Exynos5420 SoC has multiple channels for USB 3.0 PHY, with
	 * each having separate power control registers.
	 * 'channel' facilitates to set such registers.
	 */
	channel = of_alias_get_id(node, "usbdrdphy");
	if (channel < 0)
		dev_dbg(dev, "Not a multi-controller usbdrd phy\n");

	switch (channel) {
	case 1:
		pmu_offset = phy_drd->drv_data->pmu_offset_usbdrd1_phy;
		break;
	case 0:
	default:
		pmu_offset = phy_drd->drv_data->pmu_offset_usbdrd0_phy;
		break;
	}

	/* Get Vbus regulators */
	phy_drd->vbus = devm_regulator_get(dev, "vbus");
	if (IS_ERR(phy_drd->vbus)) {
		ret = PTR_ERR(phy_drd->vbus);
		if (ret == -EPROBE_DEFER)
			return ret;

		dev_warn(dev, "Failed to get VBUS supply regulator\n");
		phy_drd->vbus = NULL;
	}

	phy_drd->vbus_boost = devm_regulator_get(dev, "vbus-boost");
	if (IS_ERR(phy_drd->vbus_boost)) {
		ret = PTR_ERR(phy_drd->vbus_boost);
		if (ret == -EPROBE_DEFER)
			return ret;

		dev_warn(dev, "Failed to get VBUS boost supply regulator\n");
		phy_drd->vbus_boost = NULL;
	}

	dev_vdbg(dev, "Creating usbdrd_phy phy\n");

	for (i = 0; i < EXYNOS5_DRDPHYS_NUM; i++) {
		struct phy *phy = devm_phy_create(dev, NULL,
						  &exynos5_usbdrd_phy_ops);
		if (IS_ERR(phy)) {
			dev_err(dev, "Failed to create usbdrd_phy phy\n");
			return PTR_ERR(phy);
		}

		phy_drd->phys[i].phy = phy;
		phy_drd->phys[i].index = i;
		phy_drd->phys[i].reg_pmu = reg_pmu;
		phy_drd->phys[i].pmu_offset = pmu_offset;
		phy_drd->phys[i].phy_cfg = &drv_data->phy_cfg[i];
		phy_set_drvdata(phy, &phy_drd->phys[i]);
	}

	phy_provider = devm_of_phy_provider_register(dev,
						     exynos5_usbdrd_phy_xlate);
	if (IS_ERR(phy_provider)) {
		dev_err(phy_drd->dev, "Failed to register phy provider\n");
		return PTR_ERR(phy_provider);
	}

	return 0;
}