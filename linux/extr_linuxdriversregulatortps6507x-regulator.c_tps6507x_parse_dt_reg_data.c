#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tps6507x_board {struct regulator_init_data* tps6507x_pmic_init_data; } ;
struct regulator_init_data {int dummy; } ;
struct TYPE_6__ {TYPE_1__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_regulator_match {int /*<<< orphan*/  init_data; int /*<<< orphan*/  of_node; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct of_regulator_match*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TPS6507X_NUM_REGULATOR ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct regulator_init_data*,int /*<<< orphan*/ ,int) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_regulator_match (TYPE_2__*,struct device_node*,struct of_regulator_match*,int) ; 
 struct of_regulator_match* tps6507x_matches ; 

__attribute__((used)) static struct tps6507x_board *tps6507x_parse_dt_reg_data(
		struct platform_device *pdev,
		struct of_regulator_match **tps6507x_reg_matches)
{
	struct tps6507x_board *tps_board;
	struct device_node *np = pdev->dev.parent->of_node;
	struct device_node *regulators;
	struct of_regulator_match *matches;
	struct regulator_init_data *reg_data;
	int idx = 0, count, ret;

	tps_board = devm_kzalloc(&pdev->dev, sizeof(*tps_board),
					GFP_KERNEL);
	if (!tps_board)
		return NULL;

	regulators = of_get_child_by_name(np, "regulators");
	if (!regulators) {
		dev_err(&pdev->dev, "regulator node not found\n");
		return NULL;
	}

	count = ARRAY_SIZE(tps6507x_matches);
	matches = tps6507x_matches;

	ret = of_regulator_match(&pdev->dev, regulators, matches, count);
	of_node_put(regulators);
	if (ret < 0) {
		dev_err(&pdev->dev, "Error parsing regulator init data: %d\n",
			ret);
		return NULL;
	}

	*tps6507x_reg_matches = matches;

	reg_data = devm_kzalloc(&pdev->dev, (sizeof(struct regulator_init_data)
					* TPS6507X_NUM_REGULATOR), GFP_KERNEL);
	if (!reg_data)
		return NULL;

	tps_board->tps6507x_pmic_init_data = reg_data;

	for (idx = 0; idx < count; idx++) {
		if (!matches[idx].init_data || !matches[idx].of_node)
			continue;

		memcpy(&reg_data[idx], matches[idx].init_data,
				sizeof(struct regulator_init_data));

	}

	return tps_board;
}