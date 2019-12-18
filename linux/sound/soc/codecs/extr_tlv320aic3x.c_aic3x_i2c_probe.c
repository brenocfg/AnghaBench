#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_11__ {struct device_node* of_node; struct aic3x_pdata* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct aic3x_setup_data {int /*<<< orphan*/  gpio_func; } ;
struct aic3x_priv {int gpio_reset; scalar_t__ model; int /*<<< orphan*/  list; int /*<<< orphan*/  regmap; TYPE_1__* supplies; void* micbias_vg; struct aic3x_setup_data* setup; } ;
struct aic3x_pdata {int gpio_reset; void* micbias_vg; struct aic3x_setup_data* setup; } ;
struct TYPE_10__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 void* AIC3X_MICBIAS_2_0V ; 
 void* AIC3X_MICBIAS_2_5V ; 
 void* AIC3X_MICBIAS_AVDDV ; 
 void* AIC3X_MICBIAS_OFF ; 
 scalar_t__ AIC3X_MODEL_3007 ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* aic3007_class_d ; 
 int /*<<< orphan*/  aic3x_configure_ocmv (struct i2c_client*) ; 
 int /*<<< orphan*/  aic3x_dai ; 
 int /*<<< orphan*/  aic3x_is_shared_reset (struct aic3x_priv*) ; 
 int /*<<< orphan*/  aic3x_regmap ; 
 int /*<<< orphan*/ * aic3x_supply_names ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (TYPE_2__*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct aic3x_priv*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  reset_list ; 
 int /*<<< orphan*/  soc_component_dev_aic3x ; 

__attribute__((used)) static int aic3x_i2c_probe(struct i2c_client *i2c,
			   const struct i2c_device_id *id)
{
	struct aic3x_pdata *pdata = i2c->dev.platform_data;
	struct aic3x_priv *aic3x;
	struct aic3x_setup_data *ai3x_setup;
	struct device_node *np = i2c->dev.of_node;
	int ret, i;
	u32 value;

	aic3x = devm_kzalloc(&i2c->dev, sizeof(struct aic3x_priv), GFP_KERNEL);
	if (!aic3x)
		return -ENOMEM;

	aic3x->regmap = devm_regmap_init_i2c(i2c, &aic3x_regmap);
	if (IS_ERR(aic3x->regmap)) {
		ret = PTR_ERR(aic3x->regmap);
		return ret;
	}

	regcache_cache_only(aic3x->regmap, true);

	i2c_set_clientdata(i2c, aic3x);
	if (pdata) {
		aic3x->gpio_reset = pdata->gpio_reset;
		aic3x->setup = pdata->setup;
		aic3x->micbias_vg = pdata->micbias_vg;
	} else if (np) {
		ai3x_setup = devm_kzalloc(&i2c->dev, sizeof(*ai3x_setup),
								GFP_KERNEL);
		if (!ai3x_setup)
			return -ENOMEM;

		ret = of_get_named_gpio(np, "reset-gpios", 0);
		if (ret >= 0) {
			aic3x->gpio_reset = ret;
		} else {
			ret = of_get_named_gpio(np, "gpio-reset", 0);
			if (ret > 0) {
				dev_warn(&i2c->dev, "Using deprecated property \"gpio-reset\", please update your DT");
				aic3x->gpio_reset = ret;
			} else {
				aic3x->gpio_reset = -1;
			}
		}

		if (of_property_read_u32_array(np, "ai3x-gpio-func",
					ai3x_setup->gpio_func, 2) >= 0) {
			aic3x->setup = ai3x_setup;
		}

		if (!of_property_read_u32(np, "ai3x-micbias-vg", &value)) {
			switch (value) {
			case 1 :
				aic3x->micbias_vg = AIC3X_MICBIAS_2_0V;
				break;
			case 2 :
				aic3x->micbias_vg = AIC3X_MICBIAS_2_5V;
				break;
			case 3 :
				aic3x->micbias_vg = AIC3X_MICBIAS_AVDDV;
				break;
			default :
				aic3x->micbias_vg = AIC3X_MICBIAS_OFF;
				dev_err(&i2c->dev, "Unsuitable MicBias voltage "
							"found in DT\n");
			}
		} else {
			aic3x->micbias_vg = AIC3X_MICBIAS_OFF;
		}

	} else {
		aic3x->gpio_reset = -1;
	}

	aic3x->model = id->driver_data;

	if (gpio_is_valid(aic3x->gpio_reset) &&
	    !aic3x_is_shared_reset(aic3x)) {
		ret = gpio_request(aic3x->gpio_reset, "tlv320aic3x reset");
		if (ret != 0)
			goto err;
		gpio_direction_output(aic3x->gpio_reset, 0);
	}

	for (i = 0; i < ARRAY_SIZE(aic3x->supplies); i++)
		aic3x->supplies[i].supply = aic3x_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(aic3x->supplies),
				      aic3x->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		goto err_gpio;
	}

	aic3x_configure_ocmv(i2c);

	if (aic3x->model == AIC3X_MODEL_3007) {
		ret = regmap_register_patch(aic3x->regmap, aic3007_class_d,
					    ARRAY_SIZE(aic3007_class_d));
		if (ret != 0)
			dev_err(&i2c->dev, "Failed to init class D: %d\n",
				ret);
	}

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_aic3x, &aic3x_dai, 1);

	if (ret != 0)
		goto err_gpio;

	INIT_LIST_HEAD(&aic3x->list);
	list_add(&aic3x->list, &reset_list);

	return 0;

err_gpio:
	if (gpio_is_valid(aic3x->gpio_reset) &&
	    !aic3x_is_shared_reset(aic3x))
		gpio_free(aic3x->gpio_reset);
err:
	return ret;
}