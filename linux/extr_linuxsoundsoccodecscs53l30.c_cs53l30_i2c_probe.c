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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_device_id {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct i2c_client {struct device dev; } ;
struct device_node {int dummy; } ;
struct cs53l30_private {int use_sdout2; TYPE_1__* supplies; int /*<<< orphan*/ * regmap; int /*<<< orphan*/ * mute_gpio; int /*<<< orphan*/ * mclk; scalar_t__ mclk_rate; int /*<<< orphan*/ * reset_gpio; } ;
struct TYPE_5__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int CS53L30_DEVID ; 
 int /*<<< orphan*/  CS53L30_DEVID_AB ; 
 int /*<<< orphan*/  CS53L30_DEVID_CD ; 
 int /*<<< orphan*/  CS53L30_DEVID_E ; 
 int /*<<< orphan*/  CS53L30_MICBIAS_CTL ; 
 int /*<<< orphan*/  CS53L30_MIC_BIAS_CTRL_MASK ; 
 int /*<<< orphan*/  CS53L30_MUTEP_CTL1 ; 
 int /*<<< orphan*/  CS53L30_MUTEP_CTL1_MUTEALL ; 
 int /*<<< orphan*/  CS53L30_MUTEP_CTL2 ; 
 int /*<<< orphan*/  CS53L30_MUTE_PIN_POLARITY ; 
 int /*<<< orphan*/  CS53L30_REVID ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs53l30_dai ; 
 int /*<<< orphan*/  cs53l30_driver ; 
 int /*<<< orphan*/  cs53l30_regmap ; 
 int /*<<< orphan*/ * cs53l30_supply_names ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct cs53l30_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gpiod_is_active_low (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cs53l30_private*) ; 
 scalar_t__ of_property_read_bool (struct device_node const*,char*) ; 
 int /*<<< orphan*/  of_property_read_u8 (struct device_node const*,char*,int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 

__attribute__((used)) static int cs53l30_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	const struct device_node *np = client->dev.of_node;
	struct device *dev = &client->dev;
	struct cs53l30_private *cs53l30;
	unsigned int devid = 0;
	unsigned int reg;
	int ret = 0, i;
	u8 val;

	cs53l30 = devm_kzalloc(dev, sizeof(*cs53l30), GFP_KERNEL);
	if (!cs53l30)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(cs53l30->supplies); i++)
		cs53l30->supplies[i].supply = cs53l30_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(cs53l30->supplies),
				      cs53l30->supplies);
	if (ret) {
		dev_err(dev, "failed to get supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(cs53l30->supplies),
				    cs53l30->supplies);
	if (ret) {
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		return ret;
	}

	/* Reset the Device */
	cs53l30->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	if (IS_ERR(cs53l30->reset_gpio)) {
		ret = PTR_ERR(cs53l30->reset_gpio);
		goto error;
	}

	gpiod_set_value_cansleep(cs53l30->reset_gpio, 1);

	i2c_set_clientdata(client, cs53l30);

	cs53l30->mclk_rate = 0;

	cs53l30->regmap = devm_regmap_init_i2c(client, &cs53l30_regmap);
	if (IS_ERR(cs53l30->regmap)) {
		ret = PTR_ERR(cs53l30->regmap);
		dev_err(dev, "regmap_init() failed: %d\n", ret);
		goto error;
	}

	/* Initialize codec */
	ret = regmap_read(cs53l30->regmap, CS53L30_DEVID_AB, &reg);
	devid = reg << 12;

	ret = regmap_read(cs53l30->regmap, CS53L30_DEVID_CD, &reg);
	devid |= reg << 4;

	ret = regmap_read(cs53l30->regmap, CS53L30_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	if (devid != CS53L30_DEVID) {
		ret = -ENODEV;
		dev_err(dev, "Device ID (%X). Expected %X\n",
			devid, CS53L30_DEVID);
		goto error;
	}

	ret = regmap_read(cs53l30->regmap, CS53L30_REVID, &reg);
	if (ret < 0) {
		dev_err(dev, "failed to get Revision ID: %d\n", ret);
		goto error;
	}

	/* Check if MCLK provided */
	cs53l30->mclk = devm_clk_get(dev, "mclk");
	if (IS_ERR(cs53l30->mclk)) {
		if (PTR_ERR(cs53l30->mclk) != -ENOENT) {
			ret = PTR_ERR(cs53l30->mclk);
			goto error;
		}
		/* Otherwise mark the mclk pointer to NULL */
		cs53l30->mclk = NULL;
	}

	/* Fetch the MUTE control */
	cs53l30->mute_gpio = devm_gpiod_get_optional(dev, "mute",
						     GPIOD_OUT_HIGH);
	if (IS_ERR(cs53l30->mute_gpio)) {
		ret = PTR_ERR(cs53l30->mute_gpio);
		goto error;
	}

	if (cs53l30->mute_gpio) {
		/* Enable MUTE controls via MUTE pin */
		regmap_write(cs53l30->regmap, CS53L30_MUTEP_CTL1,
			     CS53L30_MUTEP_CTL1_MUTEALL);
		/* Flip the polarity of MUTE pin */
		if (gpiod_is_active_low(cs53l30->mute_gpio))
			regmap_update_bits(cs53l30->regmap, CS53L30_MUTEP_CTL2,
					   CS53L30_MUTE_PIN_POLARITY, 0);
	}

	if (!of_property_read_u8(np, "cirrus,micbias-lvl", &val))
		regmap_update_bits(cs53l30->regmap, CS53L30_MICBIAS_CTL,
				   CS53L30_MIC_BIAS_CTRL_MASK, val);

	if (of_property_read_bool(np, "cirrus,use-sdout2"))
		cs53l30->use_sdout2 = true;

	dev_info(dev, "Cirrus Logic CS53L30, Revision: %02X\n", reg & 0xFF);

	ret = devm_snd_soc_register_component(dev, &cs53l30_driver, &cs53l30_dai, 1);
	if (ret) {
		dev_err(dev, "failed to register component: %d\n", ret);
		goto error;
	}

	return 0;

error:
	regulator_bulk_disable(ARRAY_SIZE(cs53l30->supplies),
			       cs53l30->supplies);
	return ret;
}