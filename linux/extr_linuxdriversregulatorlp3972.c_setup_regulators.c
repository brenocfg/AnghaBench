#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {struct lp3972* driver_data; int /*<<< orphan*/  init_data; int /*<<< orphan*/  dev; } ;
struct lp3972_regulator_subdev {size_t id; int /*<<< orphan*/  initdata; } ;
struct lp3972_platform_data {int num_regulators; struct lp3972_regulator_subdev* regulators; } ;
struct lp3972 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/ * regulators ; 

__attribute__((used)) static int setup_regulators(struct lp3972 *lp3972,
	struct lp3972_platform_data *pdata)
{
	int i, err;

	/* Instantiate the regulators */
	for (i = 0; i < pdata->num_regulators; i++) {
		struct lp3972_regulator_subdev *reg = &pdata->regulators[i];
		struct regulator_config config = { };
		struct regulator_dev *rdev;

		config.dev = lp3972->dev;
		config.init_data = reg->initdata;
		config.driver_data = lp3972;

		rdev = devm_regulator_register(lp3972->dev,
					       &regulators[reg->id], &config);
		if (IS_ERR(rdev)) {
			err = PTR_ERR(rdev);
			dev_err(lp3972->dev, "regulator init failed: %d\n",
				err);
			return err;
		}
	}

	return 0;
}