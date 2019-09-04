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
struct max98371_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX98371_VERSION ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct max98371_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max98371_priv*) ; 
 int /*<<< orphan*/  max98371_component ; 
 int /*<<< orphan*/  max98371_dai ; 
 int /*<<< orphan*/  max98371_regmap ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int max98371_i2c_probe(struct i2c_client *i2c,
		const struct i2c_device_id *id)
{
	struct max98371_priv *max98371;
	int ret, reg;

	max98371 = devm_kzalloc(&i2c->dev,
			sizeof(*max98371), GFP_KERNEL);
	if (!max98371)
		return -ENOMEM;

	i2c_set_clientdata(i2c, max98371);
	max98371->regmap = devm_regmap_init_i2c(i2c, &max98371_regmap);
	if (IS_ERR(max98371->regmap)) {
		ret = PTR_ERR(max98371->regmap);
		dev_err(&i2c->dev,
				"Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	ret = regmap_read(max98371->regmap, MAX98371_VERSION, &reg);
	if (ret < 0) {
		dev_info(&i2c->dev, "device error %d\n", ret);
		return ret;
	}
	dev_info(&i2c->dev, "device version %x\n", reg);

	ret = devm_snd_soc_register_component(&i2c->dev, &max98371_component,
			max98371_dai, ARRAY_SIZE(max98371_dai));
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);
		return ret;
	}
	return ret;
}