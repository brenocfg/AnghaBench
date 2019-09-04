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
struct regulator_dev {int dummy; } ;
struct regulator_config {struct da903x_regulator_info* driver_data; int /*<<< orphan*/  init_data; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {scalar_t__ id; int n_voltages; int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  n_linear_ranges; int /*<<< orphan*/  linear_ranges; } ;
struct da903x_regulator_info {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ DA9030_ID_LDO1 ; 
 scalar_t__ DA9030_ID_LDO14 ; 
 scalar_t__ DA9030_ID_LDO15 ; 
 scalar_t__ DA9034_ID_LDO12 ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  da9030_regulator_ldo14_ops ; 
 int /*<<< orphan*/  da9030_regulator_ldo1_15_ops ; 
 int /*<<< orphan*/  da9034_ldo12_ranges ; 
 int /*<<< orphan*/  da9034_regulator_ldo12_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ *,TYPE_1__*,struct regulator_config*) ; 
 struct da903x_regulator_info* find_regulator_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 

__attribute__((used)) static int da903x_regulator_probe(struct platform_device *pdev)
{
	struct da903x_regulator_info *ri = NULL;
	struct regulator_dev *rdev;
	struct regulator_config config = { };

	ri = find_regulator_info(pdev->id);
	if (ri == NULL) {
		dev_err(&pdev->dev, "invalid regulator ID specified\n");
		return -EINVAL;
	}

	/* Workaround for the weird LDO12 voltage setting */
	if (ri->desc.id == DA9034_ID_LDO12) {
		ri->desc.ops = &da9034_regulator_ldo12_ops;
		ri->desc.n_voltages = 16;
		ri->desc.linear_ranges = da9034_ldo12_ranges;
		ri->desc.n_linear_ranges = ARRAY_SIZE(da9034_ldo12_ranges);
	}

	if (ri->desc.id == DA9030_ID_LDO14)
		ri->desc.ops = &da9030_regulator_ldo14_ops;

	if (ri->desc.id == DA9030_ID_LDO1 || ri->desc.id == DA9030_ID_LDO15)
		ri->desc.ops = &da9030_regulator_ldo1_15_ops;

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = ri;

	rdev = devm_regulator_register(&pdev->dev, &ri->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(&pdev->dev, "failed to register regulator %s\n",
				ri->desc.name);
		return PTR_ERR(rdev);
	}

	platform_set_drvdata(pdev, rdev);
	return 0;
}