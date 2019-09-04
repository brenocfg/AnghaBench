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
struct regulator_config {struct regulator_dev* regmap; int /*<<< orphan*/ * dev; } ;
typedef  struct regulator_dev regmap ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
#define  MT6311_E1_CID_CODE 130 
#define  MT6311_E2_CID_CODE 129 
#define  MT6311_E3_CID_CODE 128 
 int MT6311_MAX_REGULATORS ; 
 int /*<<< orphan*/  MT6311_SWCID ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  mt6311_regmap_config ; 
 int /*<<< orphan*/ * mt6311_regulators ; 
 int regmap_read (struct regulator_dev*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mt6311_i2c_probe(struct i2c_client *i2c,
		const struct i2c_device_id *id)
{
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	struct regmap *regmap;
	int i, ret;
	unsigned int data;

	regmap = devm_regmap_init_i2c(i2c, &mt6311_regmap_config);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = regmap_read(regmap, MT6311_SWCID, &data);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to read DEVICE_ID reg: %d\n", ret);
		return ret;
	}

	switch (data) {
	case MT6311_E1_CID_CODE:
	case MT6311_E2_CID_CODE:
	case MT6311_E3_CID_CODE:
		break;
	default:
		dev_err(&i2c->dev, "Unsupported device id = 0x%x.\n", data);
		return -ENODEV;
	}

	for (i = 0; i < MT6311_MAX_REGULATORS; i++) {
		config.dev = &i2c->dev;
		config.regmap = regmap;

		rdev = devm_regulator_register(&i2c->dev,
			&mt6311_regulators[i], &config);
		if (IS_ERR(rdev)) {
			dev_err(&i2c->dev,
				"Failed to register MT6311 regulator\n");
			return PTR_ERR(rdev);
		}
	}

	return 0;
}