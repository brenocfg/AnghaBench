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
struct regulator_dev {int dummy; } ;
struct regulator_config {struct device_node* of_node; struct regmap* regmap; struct hi6421_regulator_info* driver_data; struct regulator_init_data* init_data; int /*<<< orphan*/ * dev; } ;
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct hi6421_regulator_info {TYPE_1__ desc; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ *,TYPE_1__*,struct regulator_config*) ; 
 struct hi6421_regulator_info* hi6421_regulator_info ; 

__attribute__((used)) static int hi6421_regulator_register(struct platform_device *pdev,
				     struct regmap *rmap,
				     struct regulator_init_data *init_data,
				     int id, struct device_node *np)
{
	struct hi6421_regulator_info *info = NULL;
	struct regulator_config config = { };
	struct regulator_dev *rdev;

	/* assign per-regulator data */
	info = &hi6421_regulator_info[id];

	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.driver_data = info;
	config.regmap = rmap;
	config.of_node = np;

	/* register regulator with framework */
	rdev = devm_regulator_register(&pdev->dev, &info->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(&pdev->dev, "failed to register regulator %s\n",
			info->desc.name);
		return PTR_ERR(rdev);
	}

	return 0;
}