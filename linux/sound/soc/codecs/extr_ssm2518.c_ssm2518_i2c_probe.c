#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssm2518_platform_data {int enable_gpio; } ;
struct ssm2518 {int enable_gpio; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {scalar_t__ of_node; struct ssm2518_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSM2518_POWER1_RESET ; 
 int /*<<< orphan*/  SSM2518_POWER2_APWDN ; 
 int /*<<< orphan*/  SSM2518_REG_POWER1 ; 
 int /*<<< orphan*/  SSM2518_REG_POWER2 ; 
 int devm_gpio_request_one (TYPE_1__*,int,int /*<<< orphan*/ ,char*) ; 
 struct ssm2518* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ssm2518*) ; 
 int of_get_gpio (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssm2518_component_driver ; 
 int /*<<< orphan*/  ssm2518_dai ; 
 int /*<<< orphan*/  ssm2518_regmap_config ; 
 int ssm2518_set_power (struct ssm2518*,int) ; 

__attribute__((used)) static int ssm2518_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct ssm2518_platform_data *pdata = i2c->dev.platform_data;
	struct ssm2518 *ssm2518;
	int ret;

	ssm2518 = devm_kzalloc(&i2c->dev, sizeof(*ssm2518), GFP_KERNEL);
	if (ssm2518 == NULL)
		return -ENOMEM;

	if (pdata) {
		ssm2518->enable_gpio = pdata->enable_gpio;
	} else if (i2c->dev.of_node) {
		ssm2518->enable_gpio = of_get_gpio(i2c->dev.of_node, 0);
		if (ssm2518->enable_gpio < 0 && ssm2518->enable_gpio != -ENOENT)
			return ssm2518->enable_gpio;
	} else {
		ssm2518->enable_gpio = -1;
	}

	if (gpio_is_valid(ssm2518->enable_gpio)) {
		ret = devm_gpio_request_one(&i2c->dev, ssm2518->enable_gpio,
				GPIOF_OUT_INIT_HIGH, "SSM2518 nSD");
		if (ret)
			return ret;
	}

	i2c_set_clientdata(i2c, ssm2518);

	ssm2518->regmap = devm_regmap_init_i2c(i2c, &ssm2518_regmap_config);
	if (IS_ERR(ssm2518->regmap))
		return PTR_ERR(ssm2518->regmap);

	/*
	 * The reset bit is obviously volatile, but we need to be able to cache
	 * the other bits in the register, so we can't just mark the whole
	 * register as volatile. Since this is the only place where we'll ever
	 * touch the reset bit just bypass the cache for this operation.
	 */
	regcache_cache_bypass(ssm2518->regmap, true);
	ret = regmap_write(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_RESET);
	regcache_cache_bypass(ssm2518->regmap, false);
	if (ret)
		return ret;

	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER2,
				SSM2518_POWER2_APWDN, 0x00);
	if (ret)
		return ret;

	ret = ssm2518_set_power(ssm2518, false);
	if (ret)
		return ret;

	return devm_snd_soc_register_component(&i2c->dev,
			&ssm2518_component_driver,
			&ssm2518_dai, 1);
}