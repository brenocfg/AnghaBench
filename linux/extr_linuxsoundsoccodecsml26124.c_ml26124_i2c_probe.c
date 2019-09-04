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
struct ml26124_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ml26124_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ml26124_priv*) ; 
 int /*<<< orphan*/  ml26124_dai ; 
 int /*<<< orphan*/  ml26124_i2c_regmap ; 
 int /*<<< orphan*/  soc_component_dev_ml26124 ; 

__attribute__((used)) static int ml26124_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct ml26124_priv *priv;
	int ret;

	priv = devm_kzalloc(&i2c->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	i2c_set_clientdata(i2c, priv);

	priv->regmap = devm_regmap_init_i2c(i2c, &ml26124_i2c_regmap);
	if (IS_ERR(priv->regmap)) {
		ret = PTR_ERR(priv->regmap);
		dev_err(&i2c->dev, "regmap_init_i2c() failed: %d\n", ret);
		return ret;
	}

	return devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_ml26124, &ml26124_dai, 1);
}