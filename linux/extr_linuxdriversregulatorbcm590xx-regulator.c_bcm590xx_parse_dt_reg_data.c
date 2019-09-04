#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_regulator_match {scalar_t__ init_data; int /*<<< orphan*/  of_node; } ;
struct device_node {int dummy; } ;
struct bcm590xx_board {scalar_t__* bcm590xx_pmu_init_data; } ;
struct TYPE_6__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct of_regulator_match*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct of_regulator_match* bcm590xx_matches ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct bcm590xx_board* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_regulator_match (TYPE_2__*,struct device_node*,struct of_regulator_match*,int) ; 

__attribute__((used)) static struct bcm590xx_board *bcm590xx_parse_dt_reg_data(
		struct platform_device *pdev,
		struct of_regulator_match **bcm590xx_reg_matches)
{
	struct bcm590xx_board *data;
	struct device_node *np = pdev->dev.parent->of_node;
	struct device_node *regulators;
	struct of_regulator_match *matches = bcm590xx_matches;
	int count = ARRAY_SIZE(bcm590xx_matches);
	int idx = 0;
	int ret;

	if (!np) {
		dev_err(&pdev->dev, "of node not found\n");
		return NULL;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;

	np = of_node_get(np);
	regulators = of_get_child_by_name(np, "regulators");
	if (!regulators) {
		dev_warn(&pdev->dev, "regulator node not found\n");
		return NULL;
	}

	ret = of_regulator_match(&pdev->dev, regulators, matches, count);
	of_node_put(regulators);
	if (ret < 0) {
		dev_err(&pdev->dev, "Error parsing regulator init data: %d\n",
			ret);
		return NULL;
	}

	*bcm590xx_reg_matches = matches;

	for (idx = 0; idx < count; idx++) {
		if (!matches[idx].init_data || !matches[idx].of_node)
			continue;

		data->bcm590xx_pmu_init_data[idx] = matches[idx].init_data;
	}

	return data;
}