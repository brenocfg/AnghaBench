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
struct sta350_priv {void* regmap; TYPE_1__* supplies; void* gpiod_power_down; void* gpiod_nreset; int /*<<< orphan*/  pdata; int /*<<< orphan*/  coeff_lock; } ;
struct i2c_device_id {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_get_platdata (struct device*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sta350_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sta350_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta350_component ; 
 int /*<<< orphan*/  sta350_dai ; 
 int sta350_probe_dt (struct device*,struct sta350_priv*) ; 
 int /*<<< orphan*/  sta350_regmap ; 
 int /*<<< orphan*/ * sta350_supply_names ; 

__attribute__((used)) static int sta350_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct sta350_priv *sta350;
	int ret, i;

	sta350 = devm_kzalloc(dev, sizeof(struct sta350_priv), GFP_KERNEL);
	if (!sta350)
		return -ENOMEM;

	mutex_init(&sta350->coeff_lock);
	sta350->pdata = dev_get_platdata(dev);

#ifdef CONFIG_OF
	if (dev->of_node) {
		ret = sta350_probe_dt(dev, sta350);
		if (ret < 0)
			return ret;
	}
#endif

	/* GPIOs */
	sta350->gpiod_nreset = devm_gpiod_get_optional(dev, "reset",
						       GPIOD_OUT_LOW);
	if (IS_ERR(sta350->gpiod_nreset))
		return PTR_ERR(sta350->gpiod_nreset);

	sta350->gpiod_power_down = devm_gpiod_get_optional(dev, "power-down",
							   GPIOD_OUT_LOW);
	if (IS_ERR(sta350->gpiod_power_down))
		return PTR_ERR(sta350->gpiod_power_down);

	/* regulators */
	for (i = 0; i < ARRAY_SIZE(sta350->supplies); i++)
		sta350->supplies[i].supply = sta350_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(sta350->supplies),
				      sta350->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to request supplies: %d\n", ret);
		return ret;
	}

	sta350->regmap = devm_regmap_init_i2c(i2c, &sta350_regmap);
	if (IS_ERR(sta350->regmap)) {
		ret = PTR_ERR(sta350->regmap);
		dev_err(dev, "Failed to init regmap: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(i2c, sta350);

	ret = devm_snd_soc_register_component(dev, &sta350_component, &sta350_dai, 1);
	if (ret < 0)
		dev_err(dev, "Failed to register component (%d)\n", ret);

	return ret;
}