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
struct max98088_priv {int /*<<< orphan*/  pdata; int /*<<< orphan*/  devtype; int /*<<< orphan*/  mclk; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 struct max98088_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max98088_priv*) ; 
 int /*<<< orphan*/ * max98088_dai ; 
 int /*<<< orphan*/  max98088_regmap ; 
 int /*<<< orphan*/  soc_component_dev_max98088 ; 

__attribute__((used)) static int max98088_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
       struct max98088_priv *max98088;
       int ret;

       max98088 = devm_kzalloc(&i2c->dev, sizeof(struct max98088_priv),
			       GFP_KERNEL);
       if (max98088 == NULL)
               return -ENOMEM;

       max98088->regmap = devm_regmap_init_i2c(i2c, &max98088_regmap);
       if (IS_ERR(max98088->regmap))
	       return PTR_ERR(max98088->regmap);

	max98088->mclk = devm_clk_get(&i2c->dev, "mclk");
	if (IS_ERR(max98088->mclk))
		if (PTR_ERR(max98088->mclk) == -EPROBE_DEFER)
			return PTR_ERR(max98088->mclk);

       max98088->devtype = id->driver_data;

       i2c_set_clientdata(i2c, max98088);
       max98088->pdata = i2c->dev.platform_data;

       ret = devm_snd_soc_register_component(&i2c->dev,
                       &soc_component_dev_max98088, &max98088_dai[0], 2);
       return ret;
}