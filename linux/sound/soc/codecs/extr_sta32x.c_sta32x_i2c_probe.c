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
struct sta32x_priv {int /*<<< orphan*/ * regmap; TYPE_1__* supplies; int /*<<< orphan*/ * gpiod_nreset; int /*<<< orphan*/ * xti_clk; int /*<<< orphan*/  pdata; int /*<<< orphan*/  coeff_lock; } ;
struct i2c_device_id {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sta32x_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sta32x_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta32x_component ; 
 int /*<<< orphan*/  sta32x_dai ; 
 int sta32x_probe_dt (struct device*,struct sta32x_priv*) ; 
 int /*<<< orphan*/  sta32x_regmap ; 
 int /*<<< orphan*/ * sta32x_supply_names ; 

__attribute__((used)) static int sta32x_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct sta32x_priv *sta32x;
	int ret, i;

	sta32x = devm_kzalloc(&i2c->dev, sizeof(struct sta32x_priv),
			      GFP_KERNEL);
	if (!sta32x)
		return -ENOMEM;

	mutex_init(&sta32x->coeff_lock);
	sta32x->pdata = dev_get_platdata(dev);

#ifdef CONFIG_OF
	if (dev->of_node) {
		ret = sta32x_probe_dt(dev, sta32x);
		if (ret < 0)
			return ret;
	}
#endif

	/* Clock */
	sta32x->xti_clk = devm_clk_get(dev, "xti");
	if (IS_ERR(sta32x->xti_clk)) {
		ret = PTR_ERR(sta32x->xti_clk);

		if (ret == -EPROBE_DEFER)
			return ret;

		sta32x->xti_clk = NULL;
	}

	/* GPIOs */
	sta32x->gpiod_nreset = devm_gpiod_get_optional(dev, "reset",
						       GPIOD_OUT_LOW);
	if (IS_ERR(sta32x->gpiod_nreset))
		return PTR_ERR(sta32x->gpiod_nreset);

	/* regulators */
	for (i = 0; i < ARRAY_SIZE(sta32x->supplies); i++)
		sta32x->supplies[i].supply = sta32x_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(sta32x->supplies),
				      sta32x->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	sta32x->regmap = devm_regmap_init_i2c(i2c, &sta32x_regmap);
	if (IS_ERR(sta32x->regmap)) {
		ret = PTR_ERR(sta32x->regmap);
		dev_err(dev, "Failed to init regmap: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(i2c, sta32x);

	ret = devm_snd_soc_register_component(dev, &sta32x_component,
					      &sta32x_dai, 1);
	if (ret < 0)
		dev_err(dev, "Failed to register component (%d)\n", ret);

	return ret;
}