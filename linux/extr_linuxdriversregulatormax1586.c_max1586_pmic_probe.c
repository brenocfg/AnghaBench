#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {struct max1586_data* driver_data; scalar_t__ init_data; TYPE_2__* dev; } ;
struct of_device_id {int dummy; } ;
struct max1586_platform_data {int v3_gain; int num_subdevs; TYPE_1__* subdevs; } ;
struct max1586_data {int min_uV; int max_uV; int v3_curr_sel; scalar_t__ v6_curr_sel; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_12__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct TYPE_13__ {int min_uV; int uV_step; int name; } ;
struct TYPE_11__ {int id; scalar_t__ platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int MAX1586_V3 ; 
 int MAX1586_V3_MAX_UV ; 
 int MAX1586_V3_MAX_VSEL ; 
 int MAX1586_V3_MIN_UV ; 
 int MAX1586_V6 ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct max1586_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct max1586_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,TYPE_4__*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max1586_data*) ; 
 int /*<<< orphan*/  max1586_of_match ; 
 TYPE_4__* max1586_reg ; 
 int of_get_max1586_platform_data (TYPE_2__*,struct max1586_platform_data*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max1586_pmic_probe(struct i2c_client *client,
					const struct i2c_device_id *i2c_id)
{
	struct max1586_platform_data *pdata, pdata_of;
	struct regulator_config config = { };
	struct max1586_data *max1586;
	int i, id, ret;
	const struct of_device_id *match;

	pdata = dev_get_platdata(&client->dev);
	if (client->dev.of_node && !pdata) {
		match = of_match_device(of_match_ptr(max1586_of_match),
					&client->dev);
		if (!match) {
			dev_err(&client->dev, "Error: No device match found\n");
			return -ENODEV;
		}
		ret = of_get_max1586_platform_data(&client->dev, &pdata_of);
		if (ret < 0)
			return ret;
		pdata = &pdata_of;
	}

	max1586 = devm_kzalloc(&client->dev, sizeof(struct max1586_data),
			GFP_KERNEL);
	if (!max1586)
		return -ENOMEM;

	max1586->client = client;

	if (!pdata->v3_gain)
		return -EINVAL;

	max1586->min_uV = MAX1586_V3_MIN_UV / 1000 * pdata->v3_gain / 1000;
	max1586->max_uV = MAX1586_V3_MAX_UV / 1000 * pdata->v3_gain / 1000;

	/* Set curr_sel to default voltage on power-up */
	max1586->v3_curr_sel = 24; /* 1.3V */
	max1586->v6_curr_sel = 0;

	for (i = 0; i < pdata->num_subdevs && i <= MAX1586_V6; i++) {
		struct regulator_dev *rdev;

		id = pdata->subdevs[i].id;
		if (!pdata->subdevs[i].platform_data)
			continue;
		if (id < MAX1586_V3 || id > MAX1586_V6) {
			dev_err(&client->dev, "invalid regulator id %d\n", id);
			return -EINVAL;
		}

		if (id == MAX1586_V3) {
			max1586_reg[id].min_uV = max1586->min_uV;
			max1586_reg[id].uV_step =
					(max1586->max_uV - max1586->min_uV) /
					MAX1586_V3_MAX_VSEL;
		}

		config.dev = &client->dev;
		config.init_data = pdata->subdevs[i].platform_data;
		config.driver_data = max1586;

		rdev = devm_regulator_register(&client->dev,
						  &max1586_reg[id], &config);
		if (IS_ERR(rdev)) {
			dev_err(&client->dev, "failed to register %s\n",
				max1586_reg[id].name);
			return PTR_ERR(rdev);
		}
	}

	i2c_set_clientdata(client, max1586);
	dev_info(&client->dev, "Maxim 1586 regulator driver loaded\n");
	return 0;
}