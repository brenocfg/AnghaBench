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
struct rt5631_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct rt5631_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rt5631_priv*) ; 
 int /*<<< orphan*/  rt5631_dai ; 
 int /*<<< orphan*/  rt5631_regmap_config ; 
 int /*<<< orphan*/  soc_component_dev_rt5631 ; 

__attribute__((used)) static int rt5631_i2c_probe(struct i2c_client *i2c,
		    const struct i2c_device_id *id)
{
	struct rt5631_priv *rt5631;
	int ret;

	rt5631 = devm_kzalloc(&i2c->dev, sizeof(struct rt5631_priv),
			      GFP_KERNEL);
	if (NULL == rt5631)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt5631);

	rt5631->regmap = devm_regmap_init_i2c(i2c, &rt5631_regmap_config);
	if (IS_ERR(rt5631->regmap))
		return PTR_ERR(rt5631->regmap);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_rt5631,
			rt5631_dai, ARRAY_SIZE(rt5631_dai));
	return ret;
}