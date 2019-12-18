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
struct adau1373 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1373_SOFT_RESET ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adau1373_component_driver ; 
 int /*<<< orphan*/  adau1373_dai_driver ; 
 int /*<<< orphan*/  adau1373_regmap_config ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct adau1373*) ; 
 struct adau1373* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adau1373_i2c_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct adau1373 *adau1373;
	int ret;

	adau1373 = devm_kzalloc(&client->dev, sizeof(*adau1373), GFP_KERNEL);
	if (!adau1373)
		return -ENOMEM;

	adau1373->regmap = devm_regmap_init_i2c(client,
		&adau1373_regmap_config);
	if (IS_ERR(adau1373->regmap))
		return PTR_ERR(adau1373->regmap);

	regmap_write(adau1373->regmap, ADAU1373_SOFT_RESET, 0x00);

	dev_set_drvdata(&client->dev, adau1373);

	ret = devm_snd_soc_register_component(&client->dev,
			&adau1373_component_driver,
			adau1373_dai_driver, ARRAY_SIZE(adau1373_dai_driver));
	return ret;
}