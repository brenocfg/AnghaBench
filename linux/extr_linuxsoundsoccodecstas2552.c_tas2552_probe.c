#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tas2552_data {TYPE_1__* supplies; int /*<<< orphan*/  regmap; struct i2c_client* tas2552_client; int /*<<< orphan*/  enable_gpio; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct tas2552_data*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tas2552_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  soc_component_dev_tas2552 ; 
 TYPE_1__* tas2552_dai ; 
 int /*<<< orphan*/  tas2552_regmap_config ; 
 int /*<<< orphan*/ * tas2552_supply_names ; 

__attribute__((used)) static int tas2552_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct device *dev;
	struct tas2552_data *data;
	int ret;
	int i;

	dev = &client->dev;
	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	data->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						    GPIOD_OUT_LOW);
	if (IS_ERR(data->enable_gpio))
		return PTR_ERR(data->enable_gpio);

	data->tas2552_client = client;
	data->regmap = devm_regmap_init_i2c(client, &tas2552_regmap_config);
	if (IS_ERR(data->regmap)) {
		ret = PTR_ERR(data->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	for (i = 0; i < ARRAY_SIZE(data->supplies); i++)
		data->supplies[i].supply = tas2552_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->supplies),
				      data->supplies);
	if (ret != 0) {
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	pm_runtime_set_active(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, 1000);
	pm_runtime_use_autosuspend(&client->dev);
	pm_runtime_enable(&client->dev);
	pm_runtime_mark_last_busy(&client->dev);
	pm_runtime_put_sync_autosuspend(&client->dev);

	dev_set_drvdata(&client->dev, data);

	ret = devm_snd_soc_register_component(&client->dev,
				      &soc_component_dev_tas2552,
				      tas2552_dai, ARRAY_SIZE(tas2552_dai));
	if (ret < 0)
		dev_err(&client->dev, "Failed to register component: %d\n", ret);

	return ret;
}