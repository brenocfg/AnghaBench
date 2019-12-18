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
struct da7219_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_1 ; 
 int /*<<< orphan*/  DA7219_ACCDET_EN_MASK ; 
 int /*<<< orphan*/  DA7219_CIF_CTRL ; 
 int /*<<< orphan*/  DA7219_CIF_REG_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  DA7219_GAIN_RAMP_CTRL ; 
 int DA7219_GAIN_RAMP_RATE_NOMINAL ; 
 int /*<<< orphan*/  DA7219_SYSTEM_ACTIVE ; 
 int /*<<< orphan*/  DA7219_SYSTEM_ACTIVE_MASK ; 
 int /*<<< orphan*/  DA7219_SYSTEM_MODES_INPUT ; 
 int /*<<< orphan*/  DA7219_SYSTEM_MODES_OUTPUT ; 
 int /*<<< orphan*/  DA7219_SYSTEM_STATUS ; 
 int /*<<< orphan*/  DA7219_SYS_STAT_CHECK_DELAY ; 
 int DA7219_SYS_STAT_CHECK_RETRIES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da7219_dai ; 
 int /*<<< orphan*/  da7219_regmap_config ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct da7219_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct da7219_priv*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_component_dev_da7219 ; 

__attribute__((used)) static int da7219_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct da7219_priv *da7219;
	unsigned int system_active, system_status;
	int i, ret;

	da7219 = devm_kzalloc(&i2c->dev, sizeof(struct da7219_priv),
			      GFP_KERNEL);
	if (!da7219)
		return -ENOMEM;

	i2c_set_clientdata(i2c, da7219);

	da7219->regmap = devm_regmap_init_i2c(i2c, &da7219_regmap_config);
	if (IS_ERR(da7219->regmap)) {
		ret = PTR_ERR(da7219->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	regcache_cache_bypass(da7219->regmap, true);

	/* Disable audio paths if still active from previous start */
	regmap_read(da7219->regmap, DA7219_SYSTEM_ACTIVE, &system_active);
	if (system_active) {
		regmap_write(da7219->regmap, DA7219_GAIN_RAMP_CTRL,
			     DA7219_GAIN_RAMP_RATE_NOMINAL);
		regmap_write(da7219->regmap, DA7219_SYSTEM_MODES_INPUT, 0x00);
		regmap_write(da7219->regmap, DA7219_SYSTEM_MODES_OUTPUT, 0x01);

		for (i = 0; i < DA7219_SYS_STAT_CHECK_RETRIES; ++i) {
			regmap_read(da7219->regmap, DA7219_SYSTEM_STATUS,
				    &system_status);
			if (!system_status)
				break;

			msleep(DA7219_SYS_STAT_CHECK_DELAY);
		}
	}

	/* Soft reset component */
	regmap_write_bits(da7219->regmap, DA7219_ACCDET_CONFIG_1,
			  DA7219_ACCDET_EN_MASK, 0);
	regmap_write_bits(da7219->regmap, DA7219_CIF_CTRL,
			  DA7219_CIF_REG_SOFT_RESET_MASK,
			  DA7219_CIF_REG_SOFT_RESET_MASK);
	regmap_write_bits(da7219->regmap, DA7219_SYSTEM_ACTIVE,
			  DA7219_SYSTEM_ACTIVE_MASK, 0);

	regcache_cache_bypass(da7219->regmap, false);

	ret = devm_snd_soc_register_component(&i2c->dev,
				     &soc_component_dev_da7219,
				     &da7219_dai, 1);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to register da7219 component: %d\n",
			ret);
	}
	return ret;
}