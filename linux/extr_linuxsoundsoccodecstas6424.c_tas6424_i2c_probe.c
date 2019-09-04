#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tas6424_data {int /*<<< orphan*/  fault_check_work; int /*<<< orphan*/ * regmap; TYPE_1__* supplies; int /*<<< orphan*/ * mute_gpio; int /*<<< orphan*/ * standby_gpio; struct device* dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAS6424_MODE_CTRL ; 
 int /*<<< orphan*/  TAS6424_RESET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct tas6424_data*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tas6424_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  soc_codec_dev_tas6424 ; 
 TYPE_1__* tas6424_dai ; 
 int /*<<< orphan*/  tas6424_fault_check_work ; 
 int /*<<< orphan*/  tas6424_regmap_config ; 
 int /*<<< orphan*/ * tas6424_supply_names ; 

__attribute__((used)) static int tas6424_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct tas6424_data *tas6424;
	int ret;
	int i;

	tas6424 = devm_kzalloc(dev, sizeof(*tas6424), GFP_KERNEL);
	if (!tas6424)
		return -ENOMEM;
	dev_set_drvdata(dev, tas6424);

	tas6424->dev = dev;

	tas6424->regmap = devm_regmap_init_i2c(client, &tas6424_regmap_config);
	if (IS_ERR(tas6424->regmap)) {
		ret = PTR_ERR(tas6424->regmap);
		dev_err(dev, "unable to allocate register map: %d\n", ret);
		return ret;
	}

	/*
	 * Get control of the standby pin and set it LOW to take the codec
	 * out of the stand-by mode.
	 * Note: The actual pin polarity is taken care of in the GPIO lib
	 * according the polarity specified in the DTS.
	 */
	tas6424->standby_gpio = devm_gpiod_get_optional(dev, "standby",
						      GPIOD_OUT_LOW);
	if (IS_ERR(tas6424->standby_gpio)) {
		if (PTR_ERR(tas6424->standby_gpio) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_info(dev, "failed to get standby GPIO: %ld\n",
			PTR_ERR(tas6424->standby_gpio));
		tas6424->standby_gpio = NULL;
	}

	/*
	 * Get control of the mute pin and set it HIGH in order to start with
	 * all the output muted.
	 * Note: The actual pin polarity is taken care of in the GPIO lib
	 * according the polarity specified in the DTS.
	 */
	tas6424->mute_gpio = devm_gpiod_get_optional(dev, "mute",
						      GPIOD_OUT_HIGH);
	if (IS_ERR(tas6424->mute_gpio)) {
		if (PTR_ERR(tas6424->mute_gpio) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_info(dev, "failed to get nmute GPIO: %ld\n",
			PTR_ERR(tas6424->mute_gpio));
		tas6424->mute_gpio = NULL;
	}

	for (i = 0; i < ARRAY_SIZE(tas6424->supplies); i++)
		tas6424->supplies[i].supply = tas6424_supply_names[i];
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(tas6424->supplies),
				      tas6424->supplies);
	if (ret) {
		dev_err(dev, "unable to request supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(tas6424->supplies),
				    tas6424->supplies);
	if (ret) {
		dev_err(dev, "unable to enable supplies: %d\n", ret);
		return ret;
	}

	/* Reset device to establish well-defined startup state */
	ret = regmap_update_bits(tas6424->regmap, TAS6424_MODE_CTRL,
				 TAS6424_RESET, TAS6424_RESET);
	if (ret) {
		dev_err(dev, "unable to reset device: %d\n", ret);
		return ret;
	}

	INIT_DELAYED_WORK(&tas6424->fault_check_work, tas6424_fault_check_work);

	ret = devm_snd_soc_register_component(dev, &soc_codec_dev_tas6424,
				     tas6424_dai, ARRAY_SIZE(tas6424_dai));
	if (ret < 0) {
		dev_err(dev, "unable to register codec: %d\n", ret);
		return ret;
	}

	return 0;
}