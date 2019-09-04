#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int name; } ;
struct tps6586x_regulator {TYPE_4__ desc; } ;
struct tps6586x_platform_data {struct regulator_init_data** reg_init_data; } ;
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  of_node; struct tps6586x_regulator* driver_data; struct regulator_init_data* init_data; TYPE_1__* dev; } ;
struct TYPE_9__ {TYPE_1__* parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_regulator_match {int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int TPS6586X_ID_MAX_REGULATOR ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct tps6586x_platform_data* dev_get_platdata (TYPE_1__*) ; 
 struct regulator_dev* devm_regulator_register (TYPE_3__*,TYPE_4__*,struct regulator_config*) ; 
 struct tps6586x_regulator* find_regulator_info (int,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 
 int tps6586x_get_version (TYPE_1__*) ; 
 struct tps6586x_platform_data* tps6586x_parse_regulator_dt (struct platform_device*,struct of_regulator_match**) ; 
 int tps6586x_regulator_preinit (TYPE_1__*,struct tps6586x_regulator*) ; 
 int tps6586x_regulator_set_slew_rate (struct platform_device*,int,struct regulator_init_data*) ; 

__attribute__((used)) static int tps6586x_regulator_probe(struct platform_device *pdev)
{
	struct tps6586x_regulator *ri = NULL;
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	struct regulator_init_data *reg_data;
	struct tps6586x_platform_data *pdata;
	struct of_regulator_match *tps6586x_reg_matches = NULL;
	int version;
	int id;
	int err;

	dev_dbg(&pdev->dev, "Probing regulator\n");

	pdata = dev_get_platdata(pdev->dev.parent);
	if ((!pdata) && (pdev->dev.parent->of_node))
		pdata = tps6586x_parse_regulator_dt(pdev,
					&tps6586x_reg_matches);

	if (!pdata) {
		dev_err(&pdev->dev, "Platform data not available, exiting\n");
		return -ENODEV;
	}

	version = tps6586x_get_version(pdev->dev.parent);

	for (id = 0; id < TPS6586X_ID_MAX_REGULATOR; ++id) {
		reg_data = pdata->reg_init_data[id];

		ri = find_regulator_info(id, version);

		if (!ri) {
			dev_err(&pdev->dev, "invalid regulator ID specified\n");
			return -EINVAL;
		}

		err = tps6586x_regulator_preinit(pdev->dev.parent, ri);
		if (err) {
			dev_err(&pdev->dev,
				"regulator %d preinit failed, e %d\n", id, err);
			return err;
		}

		config.dev = pdev->dev.parent;
		config.init_data = reg_data;
		config.driver_data = ri;

		if (tps6586x_reg_matches)
			config.of_node = tps6586x_reg_matches[id].of_node;

		rdev = devm_regulator_register(&pdev->dev, &ri->desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "failed to register regulator %s\n",
					ri->desc.name);
			return PTR_ERR(rdev);
		}

		if (reg_data) {
			err = tps6586x_regulator_set_slew_rate(pdev, id,
					reg_data);
			if (err < 0) {
				dev_err(&pdev->dev,
					"Slew rate config failed, e %d\n", err);
				return err;
			}
		}
	}

	platform_set_drvdata(pdev, rdev);
	return 0;
}