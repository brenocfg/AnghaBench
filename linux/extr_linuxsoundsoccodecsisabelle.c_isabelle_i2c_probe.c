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
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct regmap*) ; 
 int /*<<< orphan*/  isabelle_dai ; 
 int /*<<< orphan*/  isabelle_regmap_config ; 
 int /*<<< orphan*/  soc_component_dev_isabelle ; 

__attribute__((used)) static int isabelle_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct regmap *isabelle_regmap;
	int ret = 0;

	isabelle_regmap = devm_regmap_init_i2c(i2c, &isabelle_regmap_config);
	if (IS_ERR(isabelle_regmap)) {
		ret = PTR_ERR(isabelle_regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}
	i2c_set_clientdata(i2c, isabelle_regmap);

	ret = devm_snd_soc_register_component(&i2c->dev,
				&soc_component_dev_isabelle, isabelle_dai,
				ARRAY_SIZE(isabelle_dai));
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);
		return ret;
	}

	return ret;
}