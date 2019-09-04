#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regulator_desc {int dummy; } ;
struct gpio_regulator_state {int dummy; } ;
struct gpio_regulator_config {int enable_high; int enabled_at_boot; int enable_gpio; int nr_gpios; int nr_states; void* type; TYPE_3__* states; TYPE_2__* gpios; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  startup_delay; TYPE_4__* init_data; } ;
struct gpio {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ constraints; } ;
struct TYPE_7__ {int value; int gpios; } ;
struct TYPE_6__ {int gpio; int /*<<< orphan*/  flags; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct gpio_regulator_config* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 void* REGULATOR_CURRENT ; 
 void* REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct gpio_regulator_config* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* of_get_named_gpio (struct device_node*,char*,int) ; 
 TYPE_4__* of_get_regulator_init_data (struct device*,struct device_node*,struct regulator_desc const*) ; 
 int of_gpio_count (struct device_node*) ; 
 int of_property_count_u32_elems (struct device_node*,char*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static struct gpio_regulator_config *
of_get_gpio_regulator_config(struct device *dev, struct device_node *np,
			     const struct regulator_desc *desc)
{
	struct gpio_regulator_config *config;
	const char *regtype;
	int proplen, gpio, i;
	int ret;

	config = devm_kzalloc(dev,
			sizeof(struct gpio_regulator_config),
			GFP_KERNEL);
	if (!config)
		return ERR_PTR(-ENOMEM);

	config->init_data = of_get_regulator_init_data(dev, np, desc);
	if (!config->init_data)
		return ERR_PTR(-EINVAL);

	config->supply_name = config->init_data->constraints.name;

	if (of_property_read_bool(np, "enable-active-high"))
		config->enable_high = true;

	if (of_property_read_bool(np, "enable-at-boot"))
		config->enabled_at_boot = true;

	of_property_read_u32(np, "startup-delay-us", &config->startup_delay);

	config->enable_gpio = of_get_named_gpio(np, "enable-gpio", 0);
	if (config->enable_gpio < 0 && config->enable_gpio != -ENOENT)
		return ERR_PTR(config->enable_gpio);

	/* Fetch GPIOs. - optional property*/
	ret = of_gpio_count(np);
	if ((ret < 0) && (ret != -ENOENT))
		return ERR_PTR(ret);

	if (ret > 0) {
		config->nr_gpios = ret;
		config->gpios = devm_kcalloc(dev,
					config->nr_gpios, sizeof(struct gpio),
					GFP_KERNEL);
		if (!config->gpios)
			return ERR_PTR(-ENOMEM);

		proplen = of_property_count_u32_elems(np, "gpios-states");
		/* optional property */
		if (proplen < 0)
			proplen = 0;

		if (proplen > 0 && proplen != config->nr_gpios) {
			dev_warn(dev, "gpios <-> gpios-states mismatch\n");
			proplen = 0;
		}

		for (i = 0; i < config->nr_gpios; i++) {
			gpio = of_get_named_gpio(np, "gpios", i);
			if (gpio < 0) {
				if (gpio != -ENOENT)
					return ERR_PTR(gpio);
				break;
			}
			config->gpios[i].gpio = gpio;
			config->gpios[i].label = config->supply_name;
			if (proplen > 0) {
				of_property_read_u32_index(np, "gpios-states",
							   i, &ret);
				if (ret)
					config->gpios[i].flags =
							   GPIOF_OUT_INIT_HIGH;
			}
		}
	}

	/* Fetch states. */
	proplen = of_property_count_u32_elems(np, "states");
	if (proplen < 0) {
		dev_err(dev, "No 'states' property found\n");
		return ERR_PTR(-EINVAL);
	}

	config->states = devm_kcalloc(dev,
				proplen / 2,
				sizeof(struct gpio_regulator_state),
				GFP_KERNEL);
	if (!config->states)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < proplen / 2; i++) {
		of_property_read_u32_index(np, "states", i * 2,
					   &config->states[i].value);
		of_property_read_u32_index(np, "states", i * 2 + 1,
					   &config->states[i].gpios);
	}
	config->nr_states = i;

	config->type = REGULATOR_VOLTAGE;
	ret = of_property_read_string(np, "regulator-type", &regtype);
	if (ret >= 0) {
		if (!strncmp("voltage", regtype, 7))
			config->type = REGULATOR_VOLTAGE;
		else if (!strncmp("current", regtype, 7))
			config->type = REGULATOR_CURRENT;
		else
			dev_warn(dev, "Unknown regulator-type '%s'\n",
				 regtype);
	}

	return config;
}