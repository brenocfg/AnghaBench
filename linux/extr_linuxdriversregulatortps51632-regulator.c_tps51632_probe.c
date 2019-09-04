#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tps51632_regulator_platform_data {scalar_t__ base_voltage_uV; scalar_t__ max_voltage_uV; int /*<<< orphan*/  reg_init_data; scalar_t__ enable_pwm_dvfs; } ;
struct TYPE_10__ {int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/  vsel_reg; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; scalar_t__ n_voltages; int /*<<< orphan*/  linear_min_sel; int /*<<< orphan*/  uV_step; scalar_t__ min_uV; int /*<<< orphan*/  ramp_delay; scalar_t__ id; int /*<<< orphan*/  name; } ;
struct tps51632_chip {struct regulator_dev* rdev; TYPE_1__* dev; TYPE_3__ desc; struct regulator_dev* regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {scalar_t__ of_node; struct regulator_dev* regmap; struct tps51632_chip* driver_data; int /*<<< orphan*/  init_data; TYPE_1__* dev; } ;
struct of_device_id {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_9__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  TPS51632_DEFAULT_RAMP_DELAY ; 
 scalar_t__ TPS51632_MAX_VOLTAGE ; 
 scalar_t__ TPS51632_MAX_VSEL ; 
 scalar_t__ TPS51632_MIN_VOLTAGE ; 
 int /*<<< orphan*/  TPS51632_MIN_VSEL ; 
 int /*<<< orphan*/  TPS51632_VOLTAGE_BASE_REG ; 
 int /*<<< orphan*/  TPS51632_VOLTAGE_SELECT_REG ; 
 int /*<<< orphan*/  TPS51632_VOLTAGE_STEP_10mV ; 
 int /*<<< orphan*/  TPS51632_VOUT_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct tps51632_regulator_platform_data* dev_get_platdata (TYPE_1__*) ; 
 struct tps51632_chip* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_3__*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps51632_chip*) ; 
 struct tps51632_regulator_platform_data* of_get_tps51632_platform_data (TYPE_1__*,TYPE_3__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps51632_dcdc_ops ; 
 int tps51632_init_dcdc (struct tps51632_chip*,struct tps51632_regulator_platform_data*) ; 
 int /*<<< orphan*/  tps51632_of_match ; 
 int /*<<< orphan*/  tps51632_regmap_config ; 

__attribute__((used)) static int tps51632_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct tps51632_regulator_platform_data *pdata;
	struct regulator_dev *rdev;
	struct tps51632_chip *tps;
	int ret;
	struct regulator_config config = { };

	if (client->dev.of_node) {
		const struct of_device_id *match;
		match = of_match_device(of_match_ptr(tps51632_of_match),
				&client->dev);
		if (!match) {
			dev_err(&client->dev, "Error: No device match found\n");
			return -ENODEV;
		}
	}

	tps = devm_kzalloc(&client->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	tps->dev = &client->dev;
	tps->desc.name = client->name;
	tps->desc.id = 0;
	tps->desc.ramp_delay = TPS51632_DEFAULT_RAMP_DELAY;
	tps->desc.min_uV = TPS51632_MIN_VOLTAGE;
	tps->desc.uV_step = TPS51632_VOLTAGE_STEP_10mV;
	tps->desc.linear_min_sel = TPS51632_MIN_VSEL;
	tps->desc.n_voltages = TPS51632_MAX_VSEL + 1;
	tps->desc.ops = &tps51632_dcdc_ops;
	tps->desc.type = REGULATOR_VOLTAGE;
	tps->desc.owner = THIS_MODULE;

	pdata = dev_get_platdata(&client->dev);
	if (!pdata && client->dev.of_node)
		pdata = of_get_tps51632_platform_data(&client->dev, &tps->desc);
	if (!pdata) {
		dev_err(&client->dev, "No Platform data\n");
		return -EINVAL;
	}

	if (pdata->enable_pwm_dvfs) {
		if ((pdata->base_voltage_uV < TPS51632_MIN_VOLTAGE) ||
		    (pdata->base_voltage_uV > TPS51632_MAX_VOLTAGE)) {
			dev_err(&client->dev, "Invalid base_voltage_uV setting\n");
			return -EINVAL;
		}

		if ((pdata->max_voltage_uV) &&
		    ((pdata->max_voltage_uV < TPS51632_MIN_VOLTAGE) ||
		     (pdata->max_voltage_uV > TPS51632_MAX_VOLTAGE))) {
			dev_err(&client->dev, "Invalid max_voltage_uV setting\n");
			return -EINVAL;
		}
	}

	if (pdata->enable_pwm_dvfs)
		tps->desc.vsel_reg = TPS51632_VOLTAGE_BASE_REG;
	else
		tps->desc.vsel_reg = TPS51632_VOLTAGE_SELECT_REG;
	tps->desc.vsel_mask = TPS51632_VOUT_MASK;

	tps->regmap = devm_regmap_init_i2c(client, &tps51632_regmap_config);
	if (IS_ERR(tps->regmap)) {
		ret = PTR_ERR(tps->regmap);
		dev_err(&client->dev, "regmap init failed, err %d\n", ret);
		return ret;
	}
	i2c_set_clientdata(client, tps);

	ret = tps51632_init_dcdc(tps, pdata);
	if (ret < 0) {
		dev_err(tps->dev, "Init failed, err = %d\n", ret);
		return ret;
	}

	/* Register the regulators */
	config.dev = &client->dev;
	config.init_data = pdata->reg_init_data;
	config.driver_data = tps;
	config.regmap = tps->regmap;
	config.of_node = client->dev.of_node;

	rdev = devm_regulator_register(&client->dev, &tps->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(tps->dev, "regulator register failed\n");
		return PTR_ERR(rdev);
	}

	tps->rdev = rdev;
	return 0;
}