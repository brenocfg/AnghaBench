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
struct tpa6130a2_platform_data {scalar_t__ power_gpio; } ;
struct tpa6130a2_data {scalar_t__ power_gpio; int id; int /*<<< orphan*/  regmap; int /*<<< orphan*/  supply; struct device* dev; } ;
struct i2c_device_id {int driver_data; } ;
struct device {struct device_node* of_node; struct tpa6130a2_platform_data* platform_data; } ;
struct i2c_client {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  TPA6130A2 129 
 int /*<<< orphan*/  TPA6130A2_REG_VERSION ; 
 unsigned int TPA6130A2_VERSION_MASK ; 
#define  TPA6140A2 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int) ; 
 int devm_gpio_request (struct device*,scalar_t__,char*) ; 
 struct tpa6130a2_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char const*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tpa6130a2_data*) ; 
 scalar_t__ of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  tpa6130a2_component_driver ; 
 int tpa6130a2_power (struct tpa6130a2_data*,int) ; 
 int /*<<< orphan*/  tpa6130a2_regmap_config ; 

__attribute__((used)) static int tpa6130a2_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct device *dev;
	struct tpa6130a2_data *data;
	struct tpa6130a2_platform_data *pdata = client->dev.platform_data;
	struct device_node *np = client->dev.of_node;
	const char *regulator;
	unsigned int version;
	int ret;

	dev = &client->dev;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->dev = dev;

	data->regmap = devm_regmap_init_i2c(client, &tpa6130a2_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	if (pdata) {
		data->power_gpio = pdata->power_gpio;
	} else if (np) {
		data->power_gpio = of_get_named_gpio(np, "power-gpio", 0);
	} else {
		dev_err(dev, "Platform data not set\n");
		dump_stack();
		return -ENODEV;
	}

	i2c_set_clientdata(client, data);

	data->id = id->driver_data;

	if (data->power_gpio >= 0) {
		ret = devm_gpio_request(dev, data->power_gpio,
					"tpa6130a2 enable");
		if (ret < 0) {
			dev_err(dev, "Failed to request power GPIO (%d)\n",
				data->power_gpio);
			return ret;
		}
		gpio_direction_output(data->power_gpio, 0);
	}

	switch (data->id) {
	default:
		dev_warn(dev, "Unknown TPA model (%d). Assuming 6130A2\n",
			 data->id);
		/* fall through */
	case TPA6130A2:
		regulator = "Vdd";
		break;
	case TPA6140A2:
		regulator = "AVdd";
		break;
	}

	data->supply = devm_regulator_get(dev, regulator);
	if (IS_ERR(data->supply)) {
		ret = PTR_ERR(data->supply);
		dev_err(dev, "Failed to request supply: %d\n", ret);
		return ret;
	}

	ret = tpa6130a2_power(data, true);
	if (ret != 0)
		return ret;


	/* Read version */
	regmap_read(data->regmap, TPA6130A2_REG_VERSION, &version);
	version &= TPA6130A2_VERSION_MASK;
	if ((version != 1) && (version != 2))
		dev_warn(dev, "UNTESTED version detected (%d)\n", version);

	/* Disable the chip */
	ret = tpa6130a2_power(data, false);
	if (ret != 0)
		return ret;

	return devm_snd_soc_register_component(&client->dev,
			&tpa6130a2_component_driver, NULL, 0);
}