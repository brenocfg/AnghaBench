#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_desc {int /*<<< orphan*/  name; } ;
struct regulator_config {TYPE_2__* dev; } ;
struct TYPE_5__ {TYPE_1__* parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct regulator_desc*) ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 struct regulator_desc* act8945a_alt_regulators ; 
 struct regulator_desc* act8945a_regulators ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,struct regulator_desc const*,struct regulator_config*) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int act8945a_pmic_probe(struct platform_device *pdev)
{
	struct regulator_config config = { };
	const struct regulator_desc *regulators;
	struct regulator_dev *rdev;
	int i, num_regulators;
	bool voltage_select;

	voltage_select = of_property_read_bool(pdev->dev.parent->of_node,
					       "active-semi,vsel-high");

	if (voltage_select) {
		regulators = act8945a_alt_regulators;
		num_regulators = ARRAY_SIZE(act8945a_alt_regulators);
	} else {
		regulators = act8945a_regulators;
		num_regulators = ARRAY_SIZE(act8945a_regulators);
	}

	config.dev = &pdev->dev;
	config.dev->of_node = pdev->dev.parent->of_node;
	for (i = 0; i < num_regulators; i++) {
		rdev = devm_regulator_register(&pdev->dev, &regulators[i], &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				regulators[i].name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}