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
struct wm8971_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct wm8971_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8971_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8971 ; 
 int /*<<< orphan*/  wm8971_dai ; 
 int /*<<< orphan*/  wm8971_regmap ; 

__attribute__((used)) static int wm8971_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8971_priv *wm8971;
	int ret;

	wm8971 = devm_kzalloc(&i2c->dev, sizeof(struct wm8971_priv),
			      GFP_KERNEL);
	if (wm8971 == NULL)
		return -ENOMEM;

	wm8971->regmap = devm_regmap_init_i2c(i2c, &wm8971_regmap);
	if (IS_ERR(wm8971->regmap))
		return PTR_ERR(wm8971->regmap);

	i2c_set_clientdata(i2c, wm8971);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8971, &wm8971_dai, 1);

	return ret;
}