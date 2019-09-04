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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct exynos_sata_phy {struct phy_provider* phyclk; struct phy_provider* phy; int /*<<< orphan*/  client; struct phy_provider* pmureg; struct phy_provider* regs; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct phy_provider*) ; 
 int clk_prepare_enable (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct exynos_sata_phy*) ; 
 struct phy_provider* devm_clk_get (struct device*,char*) ; 
 struct phy_provider* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct exynos_sata_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_sata_phy_ops ; 
 int /*<<< orphan*/  of_find_i2c_device_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct exynos_sata_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_provider* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int exynos_sata_phy_probe(struct platform_device *pdev)
{
	struct exynos_sata_phy *sata_phy;
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct phy_provider *phy_provider;
	struct device_node *node;
	int ret = 0;

	sata_phy = devm_kzalloc(dev, sizeof(*sata_phy), GFP_KERNEL);
	if (!sata_phy)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	sata_phy->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(sata_phy->regs))
		return PTR_ERR(sata_phy->regs);

	sata_phy->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
					"samsung,syscon-phandle");
	if (IS_ERR(sata_phy->pmureg)) {
		dev_err(dev, "syscon regmap lookup failed.\n");
		return PTR_ERR(sata_phy->pmureg);
	}

	node = of_parse_phandle(dev->of_node,
			"samsung,exynos-sataphy-i2c-phandle", 0);
	if (!node)
		return -EINVAL;

	sata_phy->client = of_find_i2c_device_by_node(node);
	if (!sata_phy->client)
		return -EPROBE_DEFER;

	dev_set_drvdata(dev, sata_phy);

	sata_phy->phyclk = devm_clk_get(dev, "sata_phyctrl");
	if (IS_ERR(sata_phy->phyclk)) {
		dev_err(dev, "failed to get clk for PHY\n");
		return PTR_ERR(sata_phy->phyclk);
	}

	ret = clk_prepare_enable(sata_phy->phyclk);
	if (ret < 0) {
		dev_err(dev, "failed to enable source clk\n");
		return ret;
	}

	sata_phy->phy = devm_phy_create(dev, NULL, &exynos_sata_phy_ops);
	if (IS_ERR(sata_phy->phy)) {
		clk_disable_unprepare(sata_phy->phyclk);
		dev_err(dev, "failed to create PHY\n");
		return PTR_ERR(sata_phy->phy);
	}

	phy_set_drvdata(sata_phy->phy, sata_phy);

	phy_provider = devm_of_phy_provider_register(dev,
					of_phy_simple_xlate);
	if (IS_ERR(phy_provider)) {
		clk_disable_unprepare(sata_phy->phyclk);
		return PTR_ERR(phy_provider);
	}

	return 0;
}