#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  notifier_call; } ;
struct rockchip_iodomain_supply {int idx; TYPE_2__ nb; struct regulator* reg; struct rockchip_iodomain* iod; } ;
struct rockchip_iodomain {struct rockchip_iodomain_supply* supplies; TYPE_1__* soc_data; TYPE_4__* dev; struct regulator* grf; } ;
struct regulator {int dummy; } ;
struct TYPE_11__ {struct device* parent; struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct device_node {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct TYPE_9__ {char** supply_names; int /*<<< orphan*/  (* init ) (struct rockchip_iodomain*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int MAX_SUPPLIES ; 
 int MAX_VOLTAGE_3_3 ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  dev_crit (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct rockchip_iodomain* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 struct regulator* devm_regulator_get_optional (TYPE_4__*,char const*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rockchip_iodomain*) ; 
 int regulator_get_voltage (struct regulator*) ; 
 int regulator_register_notifier (struct regulator*,TYPE_2__*) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (struct regulator*,TYPE_2__*) ; 
 int /*<<< orphan*/  rockchip_iodomain_match ; 
 int /*<<< orphan*/  rockchip_iodomain_notify ; 
 int rockchip_iodomain_write (struct rockchip_iodomain_supply*,int) ; 
 int /*<<< orphan*/  stub1 (struct rockchip_iodomain*) ; 
 struct regulator* syscon_node_to_regmap (scalar_t__) ; 
 struct regulator* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int rockchip_iodomain_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *match;
	struct rockchip_iodomain *iod;
	struct device *parent;
	int i, ret = 0;

	if (!np)
		return -ENODEV;

	iod = devm_kzalloc(&pdev->dev, sizeof(*iod), GFP_KERNEL);
	if (!iod)
		return -ENOMEM;

	iod->dev = &pdev->dev;
	platform_set_drvdata(pdev, iod);

	match = of_match_node(rockchip_iodomain_match, np);
	iod->soc_data = match->data;

	parent = pdev->dev.parent;
	if (parent && parent->of_node) {
		iod->grf = syscon_node_to_regmap(parent->of_node);
	} else {
		dev_dbg(&pdev->dev, "falling back to old binding\n");
		iod->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	}

	if (IS_ERR(iod->grf)) {
		dev_err(&pdev->dev, "couldn't find grf regmap\n");
		return PTR_ERR(iod->grf);
	}

	for (i = 0; i < MAX_SUPPLIES; i++) {
		const char *supply_name = iod->soc_data->supply_names[i];
		struct rockchip_iodomain_supply *supply = &iod->supplies[i];
		struct regulator *reg;
		int uV;

		if (!supply_name)
			continue;

		reg = devm_regulator_get_optional(iod->dev, supply_name);
		if (IS_ERR(reg)) {
			ret = PTR_ERR(reg);

			/* If a supply wasn't specified, that's OK */
			if (ret == -ENODEV)
				continue;
			else if (ret != -EPROBE_DEFER)
				dev_err(iod->dev, "couldn't get regulator %s\n",
					supply_name);
			goto unreg_notify;
		}

		/* set initial correct value */
		uV = regulator_get_voltage(reg);

		/* must be a regulator we can get the voltage of */
		if (uV < 0) {
			dev_err(iod->dev, "Can't determine voltage: %s\n",
				supply_name);
			goto unreg_notify;
		}

		if (uV > MAX_VOLTAGE_3_3) {
			dev_crit(iod->dev,
				 "%d uV is too high. May damage SoC!\n",
				 uV);
			ret = -EINVAL;
			goto unreg_notify;
		}

		/* setup our supply */
		supply->idx = i;
		supply->iod = iod;
		supply->reg = reg;
		supply->nb.notifier_call = rockchip_iodomain_notify;

		ret = rockchip_iodomain_write(supply, uV);
		if (ret) {
			supply->reg = NULL;
			goto unreg_notify;
		}

		/* register regulator notifier */
		ret = regulator_register_notifier(reg, &supply->nb);
		if (ret) {
			dev_err(&pdev->dev,
				"regulator notifier request failed\n");
			supply->reg = NULL;
			goto unreg_notify;
		}
	}

	if (iod->soc_data->init)
		iod->soc_data->init(iod);

	return 0;

unreg_notify:
	for (i = MAX_SUPPLIES - 1; i >= 0; i--) {
		struct rockchip_iodomain_supply *io_supply = &iod->supplies[i];

		if (io_supply->reg)
			regulator_unregister_notifier(io_supply->reg,
						      &io_supply->nb);
	}

	return ret;
}