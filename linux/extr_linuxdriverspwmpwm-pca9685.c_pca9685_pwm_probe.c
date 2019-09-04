#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int base; int /*<<< orphan*/ * dev; scalar_t__ npwm; int /*<<< orphan*/ * ops; } ;
struct pca9685 {TYPE_1__ chip; int /*<<< orphan*/  regmap; int /*<<< orphan*/  period_ns; scalar_t__ duty_ns; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MODE2_INVRT ; 
 int MODE2_OUTDRV ; 
 int /*<<< orphan*/  PCA9685_ALL_LED_OFF_H ; 
 int /*<<< orphan*/  PCA9685_ALL_LED_OFF_L ; 
 int /*<<< orphan*/  PCA9685_DEFAULT_PERIOD ; 
 scalar_t__ PCA9685_MAXCHAN ; 
 int /*<<< orphan*/  PCA9685_MODE2 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 struct pca9685* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pca9685*) ; 
 int pca9685_pwm_gpio_probe (struct pca9685*) ; 
 int /*<<< orphan*/  pca9685_pwm_ops ; 
 int /*<<< orphan*/  pca9685_regmap_i2c_config ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  pwmchip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pca9685_pwm_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct pca9685 *pca;
	int ret;
	int mode2;

	pca = devm_kzalloc(&client->dev, sizeof(*pca), GFP_KERNEL);
	if (!pca)
		return -ENOMEM;

	pca->regmap = devm_regmap_init_i2c(client, &pca9685_regmap_i2c_config);
	if (IS_ERR(pca->regmap)) {
		ret = PTR_ERR(pca->regmap);
		dev_err(&client->dev, "Failed to initialize register map: %d\n",
			ret);
		return ret;
	}
	pca->duty_ns = 0;
	pca->period_ns = PCA9685_DEFAULT_PERIOD;

	i2c_set_clientdata(client, pca);

	regmap_read(pca->regmap, PCA9685_MODE2, &mode2);

	if (device_property_read_bool(&client->dev, "invert"))
		mode2 |= MODE2_INVRT;
	else
		mode2 &= ~MODE2_INVRT;

	if (device_property_read_bool(&client->dev, "open-drain"))
		mode2 &= ~MODE2_OUTDRV;
	else
		mode2 |= MODE2_OUTDRV;

	regmap_write(pca->regmap, PCA9685_MODE2, mode2);

	/* clear all "full off" bits */
	regmap_write(pca->regmap, PCA9685_ALL_LED_OFF_L, 0);
	regmap_write(pca->regmap, PCA9685_ALL_LED_OFF_H, 0);

	pca->chip.ops = &pca9685_pwm_ops;
	/* add an extra channel for ALL_LED */
	pca->chip.npwm = PCA9685_MAXCHAN + 1;

	pca->chip.dev = &client->dev;
	pca->chip.base = -1;

	ret = pwmchip_add(&pca->chip);
	if (ret < 0)
		return ret;

	ret = pca9685_pwm_gpio_probe(pca);
	if (ret < 0) {
		pwmchip_remove(&pca->chip);
		return ret;
	}

	/* the chip comes out of power-up in the active state */
	pm_runtime_set_active(&client->dev);
	/*
	 * enable will put the chip into suspend, which is what we
	 * want as all outputs are disabled at this point
	 */
	pm_runtime_enable(&client->dev);

	return 0;
}