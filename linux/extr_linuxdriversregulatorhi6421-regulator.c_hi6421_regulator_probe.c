#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_4__* parent; } ;
struct platform_device {struct device dev; } ;
struct hi6421_regulator_pdata {int /*<<< orphan*/  lock; } ;
struct hi6421_pmic {int /*<<< orphan*/  regmap; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct hi6421_pmic* dev_get_drvdata (TYPE_4__*) ; 
 struct hi6421_regulator_pdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* hi6421_regulator_info ; 
 TYPE_1__* hi6421_regulator_match ; 
 int hi6421_regulator_register (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_regulator_match (struct device*,struct device_node*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hi6421_regulator_pdata*) ; 

__attribute__((used)) static int hi6421_regulator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np;
	struct hi6421_pmic *pmic;
	struct hi6421_regulator_pdata *pdata;
	int i, ret = 0;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	mutex_init(&pdata->lock);
	platform_set_drvdata(pdev, pdata);

	np = of_get_child_by_name(dev->parent->of_node, "regulators");
	if (!np)
		return -ENODEV;

	ret = of_regulator_match(dev, np,
				 hi6421_regulator_match,
				 ARRAY_SIZE(hi6421_regulator_match));
	of_node_put(np);
	if (ret < 0) {
		dev_err(dev, "Error parsing regulator init data: %d\n", ret);
		return ret;
	}

	pmic = dev_get_drvdata(dev->parent);

	for (i = 0; i < ARRAY_SIZE(hi6421_regulator_info); i++) {
		ret = hi6421_regulator_register(pdev, pmic->regmap,
			hi6421_regulator_match[i].init_data, i,
			hi6421_regulator_match[i].of_node);
		if (ret)
			return ret;
	}

	return 0;
}