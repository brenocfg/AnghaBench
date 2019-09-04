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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,TYPE_1__*) ; 
 TYPE_1__* priv_data ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  soc_codec_dev_tas5713 ; 
 int /*<<< orphan*/  tas5713_dai ; 
 int /*<<< orphan*/  tas5713_regmap_config ; 

__attribute__((used)) static int tas5713_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	int ret;

	priv_data = devm_kzalloc(&i2c->dev, sizeof *priv_data, GFP_KERNEL);
	if (!priv_data)
		return -ENOMEM;

	priv_data->regmap = devm_regmap_init_i2c(i2c, &tas5713_regmap_config);
	if (IS_ERR(priv_data->regmap)) {
		ret = PTR_ERR(priv_data->regmap);
		return ret;
	}

	i2c_set_clientdata(i2c, priv_data);

	ret = snd_soc_register_component(&i2c->dev,
				     &soc_codec_dev_tas5713, &tas5713_dai, 1);

	return ret;
}