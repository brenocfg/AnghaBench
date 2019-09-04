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
struct max9850_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct max9850_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max9850_priv*) ; 
 int /*<<< orphan*/  max9850_dai ; 
 int /*<<< orphan*/  max9850_regmap ; 
 int /*<<< orphan*/  soc_component_dev_max9850 ; 

__attribute__((used)) static int max9850_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct max9850_priv *max9850;
	int ret;

	max9850 = devm_kzalloc(&i2c->dev, sizeof(struct max9850_priv),
			       GFP_KERNEL);
	if (max9850 == NULL)
		return -ENOMEM;

	max9850->regmap = devm_regmap_init_i2c(i2c, &max9850_regmap);
	if (IS_ERR(max9850->regmap))
		return PTR_ERR(max9850->regmap);

	i2c_set_clientdata(i2c, max9850);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_max9850, &max9850_dai, 1);
	return ret;
}