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
struct sy8106a {int fixed_voltage; struct regulator_dev* rdev; struct regulator_dev* regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  init_data; int /*<<< orphan*/  of_node; struct sy8106a* driver_data; struct regulator_dev* regmap; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 unsigned int SY8106A_GO_BIT ; 
 int SY8106A_MAX_MV ; 
 int SY8106A_MIN_MV ; 
 int /*<<< orphan*/  SY8106A_REG_VOUT1_SEL ; 
 int SY8106A_STEP_MV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct sy8106a* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (struct device*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sy8106a*) ; 
 int /*<<< orphan*/  of_get_regulator_init_data (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int regmap_read (struct regulator_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regulator_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sy8106a_reg ; 
 int /*<<< orphan*/  sy8106a_regmap_config ; 

__attribute__((used)) static int sy8106a_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct sy8106a *chip;
	struct device *dev = &i2c->dev;
	struct regulator_dev *rdev = NULL;
	struct regulator_config config = { };
	unsigned int reg, vsel;
	int error;

	chip = devm_kzalloc(&i2c->dev, sizeof(struct sy8106a), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	error = of_property_read_u32(dev->of_node, "silergy,fixed-microvolt",
				     &chip->fixed_voltage);
	if (error)
		return error;

	if (chip->fixed_voltage < SY8106A_MIN_MV * 1000 ||
	    chip->fixed_voltage > SY8106A_MAX_MV * 1000)
		return -EINVAL;

	chip->regmap = devm_regmap_init_i2c(i2c, &sy8106a_regmap_config);
	if (IS_ERR(chip->regmap)) {
		error = PTR_ERR(chip->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", error);
		return error;
	}

	config.dev = &i2c->dev;
	config.regmap = chip->regmap;
	config.driver_data = chip;

	config.of_node = dev->of_node;
	config.init_data = of_get_regulator_init_data(dev, dev->of_node,
						      &sy8106a_reg);

	if (!config.init_data)
		return -ENOMEM;

	/* Ensure GO_BIT is enabled when probing */
	error = regmap_read(chip->regmap, SY8106A_REG_VOUT1_SEL, &reg);
	if (error)
		return error;

	if (!(reg & SY8106A_GO_BIT)) {
		vsel = (chip->fixed_voltage / 1000 - SY8106A_MIN_MV) /
		       SY8106A_STEP_MV;

		error = regmap_write(chip->regmap, SY8106A_REG_VOUT1_SEL,
				     vsel | SY8106A_GO_BIT);
		if (error)
			return error;
	}

	/* Probe regulator */
	rdev = devm_regulator_register(&i2c->dev, &sy8106a_reg, &config);
	if (IS_ERR(rdev)) {
		error = PTR_ERR(rdev);
		dev_err(&i2c->dev, "Failed to register SY8106A regulator: %d\n", error);
		return error;
	}

	chip->rdev = rdev;

	i2c_set_clientdata(i2c, chip);

	return 0;
}