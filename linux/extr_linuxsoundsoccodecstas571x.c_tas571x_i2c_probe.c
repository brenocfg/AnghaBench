#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  num_controls; int /*<<< orphan*/  controls; } ;
struct tas571x_private {TYPE_3__ component_driver; void* regmap; TYPE_1__* chip; void* reset_gpio; void* pdn_gpio; TYPE_2__* supplies; void* mclk; } ;
struct of_device_id {TYPE_1__* data; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  supply; } ;
struct TYPE_6__ {int num_supply_names; int vol_reg_size; int /*<<< orphan*/  num_controls; int /*<<< orphan*/  controls; int /*<<< orphan*/  regmap_config; int /*<<< orphan*/ * supply_names; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int TAS571X_MAX_SUPPLIES ; 
 int /*<<< orphan*/  TAS571X_MVOL_REG ; 
 int /*<<< orphan*/  TAS571X_OSC_TRIM_REG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tas571x_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init (struct device*,int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_2__*) ; 
 int devm_snd_soc_register_component (struct device*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_set_value (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tas571x_private*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int regmap_update_bits (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int regmap_write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int,TYPE_2__*) ; 
 int /*<<< orphan*/  tas571x_component ; 
 int /*<<< orphan*/  tas571x_dai ; 
 int /*<<< orphan*/  tas571x_of_match ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tas571x_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct tas571x_private *priv;
	struct device *dev = &client->dev;
	const struct of_device_id *of_id;
	int i, ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	i2c_set_clientdata(client, priv);

	of_id = of_match_device(tas571x_of_match, dev);
	if (of_id)
		priv->chip = of_id->data;
	else
		priv->chip = (void *) id->driver_data;

	priv->mclk = devm_clk_get(dev, "mclk");
	if (IS_ERR(priv->mclk) && PTR_ERR(priv->mclk) != -ENOENT) {
		dev_err(dev, "Failed to request mclk: %ld\n",
			PTR_ERR(priv->mclk));
		return PTR_ERR(priv->mclk);
	}

	if (WARN_ON(priv->chip->num_supply_names > TAS571X_MAX_SUPPLIES))
		return -EINVAL;
	for (i = 0; i < priv->chip->num_supply_names; i++)
		priv->supplies[i].supply = priv->chip->supply_names[i];

	ret = devm_regulator_bulk_get(dev, priv->chip->num_supply_names,
				      priv->supplies);
	if (ret) {
		dev_err(dev, "Failed to get supplies: %d\n", ret);
		return ret;
	}
	ret = regulator_bulk_enable(priv->chip->num_supply_names,
				    priv->supplies);
	if (ret) {
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	priv->regmap = devm_regmap_init(dev, NULL, client,
					priv->chip->regmap_config);
	if (IS_ERR(priv->regmap))
		return PTR_ERR(priv->regmap);

	priv->pdn_gpio = devm_gpiod_get_optional(dev, "pdn", GPIOD_OUT_LOW);
	if (IS_ERR(priv->pdn_gpio)) {
		dev_err(dev, "error requesting pdn_gpio: %ld\n",
			PTR_ERR(priv->pdn_gpio));
		return PTR_ERR(priv->pdn_gpio);
	}

	priv->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						   GPIOD_OUT_HIGH);
	if (IS_ERR(priv->reset_gpio)) {
		dev_err(dev, "error requesting reset_gpio: %ld\n",
			PTR_ERR(priv->reset_gpio));
		return PTR_ERR(priv->reset_gpio);
	} else if (priv->reset_gpio) {
		/* pulse the active low reset line for ~100us */
		usleep_range(100, 200);
		gpiod_set_value(priv->reset_gpio, 0);
		usleep_range(13500, 20000);
	}

	ret = regmap_write(priv->regmap, TAS571X_OSC_TRIM_REG, 0);
	if (ret)
		return ret;

	usleep_range(50000, 60000);

	memcpy(&priv->component_driver, &tas571x_component, sizeof(priv->component_driver));
	priv->component_driver.controls = priv->chip->controls;
	priv->component_driver.num_controls = priv->chip->num_controls;

	if (priv->chip->vol_reg_size == 2) {
		/*
		 * The master volume defaults to 0x3ff (mute), but we ignore
		 * (zero) the LSB because the hardware step size is 0.125 dB
		 * and TLV_DB_SCALE_ITEM has a resolution of 0.01 dB.
		 */
		ret = regmap_update_bits(priv->regmap, TAS571X_MVOL_REG, 1, 0);
		if (ret)
			return ret;
	}

	return devm_snd_soc_register_component(&client->dev,
				      &priv->component_driver,
				      &tas571x_dai, 1);
}