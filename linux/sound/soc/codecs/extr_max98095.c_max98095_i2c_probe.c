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
struct max98095_priv {int /*<<< orphan*/  pdata; int /*<<< orphan*/  devtype; int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct max98095_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max98095_priv*) ; 
 int /*<<< orphan*/  max98095_dai ; 
 int /*<<< orphan*/  max98095_regmap ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_component_dev_max98095 ; 

__attribute__((used)) static int max98095_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct max98095_priv *max98095;
	int ret;

	max98095 = devm_kzalloc(&i2c->dev, sizeof(struct max98095_priv),
				GFP_KERNEL);
	if (max98095 == NULL)
		return -ENOMEM;

	mutex_init(&max98095->lock);

	max98095->regmap = devm_regmap_init_i2c(i2c, &max98095_regmap);
	if (IS_ERR(max98095->regmap)) {
		ret = PTR_ERR(max98095->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	max98095->devtype = id->driver_data;
	i2c_set_clientdata(i2c, max98095);
	max98095->pdata = i2c->dev.platform_data;

	ret = devm_snd_soc_register_component(&i2c->dev,
				     &soc_component_dev_max98095,
				     max98095_dai, ARRAY_SIZE(max98095_dai));
	return ret;
}