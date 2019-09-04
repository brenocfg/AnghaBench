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
struct wm8974_priv {int dummy; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct wm8974_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8974_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8974 ; 
 int /*<<< orphan*/  wm8974_dai ; 
 int /*<<< orphan*/  wm8974_regmap ; 

__attribute__((used)) static int wm8974_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8974_priv *priv;
	struct regmap *regmap;
	int ret;

	priv = devm_kzalloc(&i2c->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	i2c_set_clientdata(i2c, priv);

	regmap = devm_regmap_init_i2c(i2c, &wm8974_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8974, &wm8974_dai, 1);

	return ret;
}