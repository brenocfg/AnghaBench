#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rockchip_pcie_phy {TYPE_2__* phys; struct regmap* clk_pciephy_ref; struct regmap* phy_rst; int /*<<< orphan*/  pcie_mutex; struct regmap* reg_base; struct rockchip_pcie_data* phy_data; } ;
struct rockchip_pcie_data {int dummy; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; TYPE_1__* parent; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_4__ {int index; struct regmap* phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PHY_MAX_LANE_NUM ; 
 int PTR_ERR (struct regmap*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct regmap* devm_clk_get (struct device*,char*) ; 
 struct rockchip_pcie_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct regmap* devm_phy_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct regmap*,TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rockchip_pcie_phy*) ; 
 int /*<<< orphan*/  rockchip_pcie_phy_dt_ids ; 
 int /*<<< orphan*/  rockchip_pcie_phy_of_xlate ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_pcie_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rockchip_pcie_phy *rk_phy;
	struct phy_provider *phy_provider;
	struct regmap *grf;
	const struct of_device_id *of_id;
	int i;
	u32 phy_num;

	grf = syscon_node_to_regmap(dev->parent->of_node);
	if (IS_ERR(grf)) {
		dev_err(dev, "Cannot find GRF syscon\n");
		return PTR_ERR(grf);
	}

	rk_phy = devm_kzalloc(dev, sizeof(*rk_phy), GFP_KERNEL);
	if (!rk_phy)
		return -ENOMEM;

	of_id = of_match_device(rockchip_pcie_phy_dt_ids, &pdev->dev);
	if (!of_id)
		return -EINVAL;

	rk_phy->phy_data = (struct rockchip_pcie_data *)of_id->data;
	rk_phy->reg_base = grf;

	mutex_init(&rk_phy->pcie_mutex);

	rk_phy->phy_rst = devm_reset_control_get(dev, "phy");
	if (IS_ERR(rk_phy->phy_rst)) {
		if (PTR_ERR(rk_phy->phy_rst) != -EPROBE_DEFER)
			dev_err(dev,
				"missing phy property for reset controller\n");
		return PTR_ERR(rk_phy->phy_rst);
	}

	rk_phy->clk_pciephy_ref = devm_clk_get(dev, "refclk");
	if (IS_ERR(rk_phy->clk_pciephy_ref)) {
		dev_err(dev, "refclk not found.\n");
		return PTR_ERR(rk_phy->clk_pciephy_ref);
	}

	/* parse #phy-cells to see if it's legacy PHY model */
	if (of_property_read_u32(dev->of_node, "#phy-cells", &phy_num))
		return -ENOENT;

	phy_num = (phy_num == 0) ? 1 : PHY_MAX_LANE_NUM;
	dev_dbg(dev, "phy number is %d\n", phy_num);

	for (i = 0; i < phy_num; i++) {
		rk_phy->phys[i].phy = devm_phy_create(dev, dev->of_node, &ops);
		if (IS_ERR(rk_phy->phys[i].phy)) {
			dev_err(dev, "failed to create PHY%d\n", i);
			return PTR_ERR(rk_phy->phys[i].phy);
		}
		rk_phy->phys[i].index = i;
		phy_set_drvdata(rk_phy->phys[i].phy, &rk_phy->phys[i]);
	}

	platform_set_drvdata(pdev, rk_phy);
	phy_provider = devm_of_phy_provider_register(dev,
					rockchip_pcie_phy_of_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}