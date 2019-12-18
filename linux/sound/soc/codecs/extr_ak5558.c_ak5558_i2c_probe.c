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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak5558_priv {int /*<<< orphan*/  reset_gpiod; struct i2c_client* i2c; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ak5558_dai ; 
 int /*<<< orphan*/  ak5558_regmap ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ak5558_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ak5558_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_codec_dev_ak5558 ; 

__attribute__((used)) static int ak5558_i2c_probe(struct i2c_client *i2c)
{
	struct ak5558_priv *ak5558;
	int ret = 0;

	ak5558 = devm_kzalloc(&i2c->dev, sizeof(*ak5558), GFP_KERNEL);
	if (!ak5558)
		return -ENOMEM;

	ak5558->regmap = devm_regmap_init_i2c(i2c, &ak5558_regmap);
	if (IS_ERR(ak5558->regmap))
		return PTR_ERR(ak5558->regmap);

	i2c_set_clientdata(i2c, ak5558);
	ak5558->i2c = i2c;

	ak5558->reset_gpiod = devm_gpiod_get_optional(&i2c->dev, "reset",
						      GPIOD_OUT_LOW);
	if (IS_ERR(ak5558->reset_gpiod))
		return PTR_ERR(ak5558->reset_gpiod);

	ret = devm_snd_soc_register_component(&i2c->dev,
				     &soc_codec_dev_ak5558,
				     &ak5558_dai, 1);
	if (ret)
		return ret;

	pm_runtime_enable(&i2c->dev);

	return 0;
}