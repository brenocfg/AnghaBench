#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct regulator_config {struct device_node* of_node; struct fan53555_device_info* driver_data; int /*<<< orphan*/  regmap; TYPE_2__* init_data; TYPE_3__* dev; } ;
struct i2c_device_id {unsigned long driver_data; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct fan53555_platform_data {int slew_rate; TYPE_2__* regulator; } ;
struct fan53555_device_info {unsigned long vendor; unsigned int chip_id; unsigned int chip_rev; int /*<<< orphan*/  regmap; TYPE_2__* regulator; TYPE_3__* dev; int /*<<< orphan*/  desc; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  ramp_delay; } ;
struct TYPE_10__ {TYPE_1__ constraints; } ;

/* Variables and functions */
 unsigned int DIE_ID ; 
 unsigned int DIE_REV ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FAN53555_ID1 ; 
 int /*<<< orphan*/  FAN53555_ID2 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct fan53555_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,unsigned int,unsigned int) ; 
 struct fan53555_device_info* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int fan53555_device_setup (struct fan53555_device_info*,struct fan53555_platform_data*) ; 
 struct fan53555_platform_data* fan53555_parse_dt (TYPE_3__*,struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fan53555_regmap_config ; 
 int fan53555_regulator_register (struct fan53555_device_info*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct fan53555_device_info*) ; 
 scalar_t__ of_device_get_match_data (TYPE_3__*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/ * slew_rates ; 

__attribute__((used)) static int fan53555_regulator_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct device_node *np = client->dev.of_node;
	struct fan53555_device_info *di;
	struct fan53555_platform_data *pdata;
	struct regulator_config config = { };
	unsigned int val;
	int ret;

	di = devm_kzalloc(&client->dev, sizeof(struct fan53555_device_info),
					GFP_KERNEL);
	if (!di)
		return -ENOMEM;

	pdata = dev_get_platdata(&client->dev);
	if (!pdata)
		pdata = fan53555_parse_dt(&client->dev, np, &di->desc);

	if (!pdata || !pdata->regulator) {
		dev_err(&client->dev, "Platform data not found!\n");
		return -ENODEV;
	}

	di->regulator = pdata->regulator;
	if (client->dev.of_node) {
		di->vendor =
			(unsigned long)of_device_get_match_data(&client->dev);
	} else {
		/* if no ramp constraint set, get the pdata ramp_delay */
		if (!di->regulator->constraints.ramp_delay) {
			int slew_idx = (pdata->slew_rate & 0x7)
						? pdata->slew_rate : 0;

			di->regulator->constraints.ramp_delay
						= slew_rates[slew_idx];
		}

		di->vendor = id->driver_data;
	}

	di->regmap = devm_regmap_init_i2c(client, &fan53555_regmap_config);
	if (IS_ERR(di->regmap)) {
		dev_err(&client->dev, "Failed to allocate regmap!\n");
		return PTR_ERR(di->regmap);
	}
	di->dev = &client->dev;
	i2c_set_clientdata(client, di);
	/* Get chip ID */
	ret = regmap_read(di->regmap, FAN53555_ID1, &val);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to get chip ID!\n");
		return ret;
	}
	di->chip_id = val & DIE_ID;
	/* Get chip revision */
	ret = regmap_read(di->regmap, FAN53555_ID2, &val);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to get chip Rev!\n");
		return ret;
	}
	di->chip_rev = val & DIE_REV;
	dev_info(&client->dev, "FAN53555 Option[%d] Rev[%d] Detected!\n",
				di->chip_id, di->chip_rev);
	/* Device init */
	ret = fan53555_device_setup(di, pdata);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to setup device!\n");
		return ret;
	}
	/* Register regulator */
	config.dev = di->dev;
	config.init_data = di->regulator;
	config.regmap = di->regmap;
	config.driver_data = di;
	config.of_node = np;

	ret = fan53555_regulator_register(di, &config);
	if (ret < 0)
		dev_err(&client->dev, "Failed to register regulator!\n");
	return ret;

}