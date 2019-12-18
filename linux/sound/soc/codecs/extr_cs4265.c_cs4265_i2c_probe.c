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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cs4265_private {scalar_t__ regmap; scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4265_CHIP_ID ; 
 unsigned int CS4265_CHIP_ID_MASK ; 
 unsigned int CS4265_CHIP_ID_VAL ; 
 int /*<<< orphan*/  CS4265_PWRCTL ; 
 unsigned int CS4265_REV_ID_MASK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  cs4265_dai ; 
 int /*<<< orphan*/  cs4265_regmap ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct cs4265_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cs4265_private*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int regmap_read (scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soc_component_cs4265 ; 

__attribute__((used)) static int cs4265_i2c_probe(struct i2c_client *i2c_client,
			     const struct i2c_device_id *id)
{
	struct cs4265_private *cs4265;
	int ret = 0;
	unsigned int devid = 0;
	unsigned int reg;

	cs4265 = devm_kzalloc(&i2c_client->dev, sizeof(struct cs4265_private),
			       GFP_KERNEL);
	if (cs4265 == NULL)
		return -ENOMEM;

	cs4265->regmap = devm_regmap_init_i2c(i2c_client, &cs4265_regmap);
	if (IS_ERR(cs4265->regmap)) {
		ret = PTR_ERR(cs4265->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	cs4265->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
		"reset", GPIOD_OUT_LOW);
	if (IS_ERR(cs4265->reset_gpio))
		return PTR_ERR(cs4265->reset_gpio);

	if (cs4265->reset_gpio) {
		mdelay(1);
		gpiod_set_value_cansleep(cs4265->reset_gpio, 1);
	}

	i2c_set_clientdata(i2c_client, cs4265);

	ret = regmap_read(cs4265->regmap, CS4265_CHIP_ID, &reg);
	devid = reg & CS4265_CHIP_ID_MASK;
	if (devid != CS4265_CHIP_ID_VAL) {
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS4265 Device ID (%X). Expected %X\n",
			devid, CS4265_CHIP_ID);
		return ret;
	}
	dev_info(&i2c_client->dev,
		"CS4265 Version %x\n",
			reg & CS4265_REV_ID_MASK);

	regmap_write(cs4265->regmap, CS4265_PWRCTL, 0x0F);

	ret = devm_snd_soc_register_component(&i2c_client->dev,
			&soc_component_cs4265, cs4265_dai,
			ARRAY_SIZE(cs4265_dai));
	return ret;
}