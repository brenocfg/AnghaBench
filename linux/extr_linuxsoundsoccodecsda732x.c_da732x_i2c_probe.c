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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct da732x_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int DA732X_ID_MAJOR_MASK ; 
 unsigned int DA732X_ID_MINOR_MASK ; 
 int /*<<< orphan*/  DA732X_REG_ID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da732x_dai ; 
 int /*<<< orphan*/  da732x_regmap ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 struct da732x_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct da732x_priv*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  soc_component_dev_da732x ; 

__attribute__((used)) static int da732x_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct da732x_priv *da732x;
	unsigned int reg;
	int ret;

	da732x = devm_kzalloc(&i2c->dev, sizeof(struct da732x_priv),
			      GFP_KERNEL);
	if (!da732x)
		return -ENOMEM;

	i2c_set_clientdata(i2c, da732x);

	da732x->regmap = devm_regmap_init_i2c(i2c, &da732x_regmap);
	if (IS_ERR(da732x->regmap)) {
		ret = PTR_ERR(da732x->regmap);
		dev_err(&i2c->dev, "Failed to initialize regmap\n");
		goto err;
	}

	ret = regmap_read(da732x->regmap, DA732X_REG_ID, &reg);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to read ID register: %d\n", ret);
		goto err;
	}

	dev_info(&i2c->dev, "Revision: %d.%d\n",
		 (reg & DA732X_ID_MAJOR_MASK) >> 4,
		 (reg & DA732X_ID_MINOR_MASK));

	ret = devm_snd_soc_register_component(&i2c->dev,
				     &soc_component_dev_da732x,
				     da732x_dai, ARRAY_SIZE(da732x_dai));
	if (ret != 0)
		dev_err(&i2c->dev, "Failed to register component.\n");

err:
	return ret;
}