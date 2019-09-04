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
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/ * init_data; TYPE_2__* dev; } ;
typedef  struct regulator_dev regmap ;
struct isl9305_pdata {int /*<<< orphan*/ ** init_data; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {struct isl9305_pdata* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,...) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  isl9305_regmap ; 
 TYPE_1__* isl9305_regulators ; 

__attribute__((used)) static int isl9305_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct regulator_config config = { };
	struct isl9305_pdata *pdata = i2c->dev.platform_data;
	struct regulator_dev *rdev;
	struct regmap *regmap;
	int i, ret;

	regmap = devm_regmap_init_i2c(i2c, &isl9305_regmap);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to create regmap: %d\n", ret);
		return ret;
	}

	config.dev = &i2c->dev;

	for (i = 0; i < ARRAY_SIZE(isl9305_regulators); i++) {
		if (pdata)
			config.init_data = pdata->init_data[i];
		else
			config.init_data = NULL;

		rdev = devm_regulator_register(&i2c->dev,
					       &isl9305_regulators[i],
					       &config);
		if (IS_ERR(rdev)) {
			ret = PTR_ERR(rdev);
			dev_err(&i2c->dev, "Failed to register %s: %d\n",
				isl9305_regulators[i].name, ret);
			return ret;
		}
	}

	return 0;
}