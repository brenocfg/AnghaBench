#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tda7419_data {int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  def; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct tda7419_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tda7419_data*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda7419_component_driver ; 
 int /*<<< orphan*/  tda7419_regmap_config ; 
 TYPE_1__* tda7419_regmap_defaults ; 

__attribute__((used)) static int tda7419_probe(struct i2c_client *i2c,
			 const struct i2c_device_id *id)
{
	struct tda7419_data *tda7419;
	int i, ret;

	tda7419 = devm_kzalloc(&i2c->dev,
			       sizeof(struct tda7419_data),
			       GFP_KERNEL);
	if (tda7419 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, tda7419);

	tda7419->regmap = devm_regmap_init_i2c(i2c, &tda7419_regmap_config);
	if (IS_ERR(tda7419->regmap)) {
		ret = PTR_ERR(tda7419->regmap);
		dev_err(&i2c->dev, "error initializing regmap: %d\n",
				ret);
		return ret;
	}

	/*
	 * Reset registers to power-on defaults. The part does not provide a
	 * soft-reset function and the registers are not readable. This ensures
	 * that the cache matches register contents even if the registers have
	 * been previously initialized and not power cycled before probe.
	 */
	for (i = 0; i < ARRAY_SIZE(tda7419_regmap_defaults); i++)
		regmap_write(tda7419->regmap,
			     tda7419_regmap_defaults[i].reg,
			     tda7419_regmap_defaults[i].def);

	ret = devm_snd_soc_register_component(&i2c->dev,
		&tda7419_component_driver, NULL, 0);
	if (ret < 0) {
		dev_err(&i2c->dev, "error registering component: %d\n",
				ret);
	}

	return ret;
}