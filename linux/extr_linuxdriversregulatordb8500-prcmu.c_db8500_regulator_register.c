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
struct regulator_init_data {int dummy; } ;
struct regulator_config {struct device_node* of_node; struct dbx500_regulator_info* driver_data; struct regulator_init_data* init_data; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dbx500_regulator_info {TYPE_1__ desc; int /*<<< orphan*/  rdev; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct dbx500_regulator_info* dbx500_regulator_info ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ *,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  rdev_get_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db8500_regulator_register(struct platform_device *pdev,
					struct regulator_init_data *init_data,
					int id,
					struct device_node *np)
{
	struct dbx500_regulator_info *info;
	struct regulator_config config = { };
	int err;

	/* assign per-regulator data */
	info = &dbx500_regulator_info[id];
	info->dev = &pdev->dev;

	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.driver_data = info;
	config.of_node = np;

	/* register with the regulator framework */
	info->rdev = devm_regulator_register(&pdev->dev, &info->desc, &config);
	if (IS_ERR(info->rdev)) {
		err = PTR_ERR(info->rdev);
		dev_err(&pdev->dev, "failed to register %s: err %i\n",
			info->desc.name, err);
		return err;
	}

	dev_dbg(rdev_get_dev(info->rdev),
		"regulator-%s-probed\n", info->desc.name);

	return 0;
}