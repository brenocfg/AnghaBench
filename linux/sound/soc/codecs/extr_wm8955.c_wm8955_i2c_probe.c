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
struct wm8955_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct wm8955_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8955_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8955 ; 
 int /*<<< orphan*/  wm8955_dai ; 
 int /*<<< orphan*/  wm8955_regmap ; 

__attribute__((used)) static int wm8955_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8955_priv *wm8955;
	int ret;

	wm8955 = devm_kzalloc(&i2c->dev, sizeof(struct wm8955_priv),
			      GFP_KERNEL);
	if (wm8955 == NULL)
		return -ENOMEM;

	wm8955->regmap = devm_regmap_init_i2c(i2c, &wm8955_regmap);
	if (IS_ERR(wm8955->regmap)) {
		ret = PTR_ERR(wm8955->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	i2c_set_clientdata(i2c, wm8955);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8955, &wm8955_dai, 1);

	return ret;
}