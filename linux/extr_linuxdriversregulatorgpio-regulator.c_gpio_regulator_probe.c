#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct regulator_config {int ena_gpio_initialized; int ena_gpio_invert; int ena_gpio_flags; int /*<<< orphan*/  ena_gpio; struct device_node* of_node; struct gpio_regulator_data* driver_data; int /*<<< orphan*/  init_data; TYPE_2__* dev; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct gpio_regulator_state {int dummy; } ;
struct TYPE_8__ {int type; int n_voltages; int /*<<< orphan*/ * name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  enable_time; int /*<<< orphan*/  owner; } ;
struct gpio_regulator_data {int nr_gpios; int nr_states; int state; TYPE_1__ desc; int /*<<< orphan*/ * gpios; int /*<<< orphan*/ * states; struct gpio_regulator_config* dev; } ;
struct gpio_regulator_config {int nr_gpios; int nr_states; int type; scalar_t__ enable_high; scalar_t__ enabled_at_boot; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  init_data; TYPE_4__* gpios; int /*<<< orphan*/  startup_delay; TYPE_4__* states; int /*<<< orphan*/  supply_name; } ;
struct gpio {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOF_OUT_INIT_HIGH ; 
 int GPIOF_OUT_INIT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_regulator_config*) ; 
 int PTR_ERR (struct gpio_regulator_config*) ; 
#define  REGULATOR_CURRENT 129 
#define  REGULATOR_VOLTAGE 128 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct gpio_regulator_config* dev_get_platdata (TYPE_2__*) ; 
 struct gpio_regulator_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ *,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_regulator_current_ops ; 
 int /*<<< orphan*/  gpio_regulator_voltage_ops ; 
 int gpio_request_array (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmemdup (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpio_regulator_config* of_get_gpio_regulator_config (TYPE_2__*,struct device_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_regulator_data*) ; 
 struct gpio_regulator_config* regulator_register (TYPE_1__*,struct regulator_config*) ; 

__attribute__((used)) static int gpio_regulator_probe(struct platform_device *pdev)
{
	struct gpio_regulator_config *config = dev_get_platdata(&pdev->dev);
	struct device_node *np = pdev->dev.of_node;
	struct gpio_regulator_data *drvdata;
	struct regulator_config cfg = { };
	int ptr, ret, state;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct gpio_regulator_data),
			       GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	if (np) {
		config = of_get_gpio_regulator_config(&pdev->dev, np,
						      &drvdata->desc);
		if (IS_ERR(config))
			return PTR_ERR(config);
	}

	drvdata->desc.name = kstrdup(config->supply_name, GFP_KERNEL);
	if (drvdata->desc.name == NULL) {
		dev_err(&pdev->dev, "Failed to allocate supply name\n");
		return -ENOMEM;
	}

	if (config->nr_gpios != 0) {
		drvdata->gpios = kmemdup(config->gpios,
					 config->nr_gpios * sizeof(struct gpio),
					 GFP_KERNEL);
		if (drvdata->gpios == NULL) {
			dev_err(&pdev->dev, "Failed to allocate gpio data\n");
			ret = -ENOMEM;
			goto err_name;
		}

		drvdata->nr_gpios = config->nr_gpios;
		ret = gpio_request_array(drvdata->gpios, drvdata->nr_gpios);
		if (ret) {
			if (ret != -EPROBE_DEFER)
				dev_err(&pdev->dev,
					"Could not obtain regulator setting GPIOs: %d\n",
					ret);
			goto err_memgpio;
		}
	}

	drvdata->states = kmemdup(config->states,
				  config->nr_states *
					 sizeof(struct gpio_regulator_state),
				  GFP_KERNEL);
	if (drvdata->states == NULL) {
		dev_err(&pdev->dev, "Failed to allocate state data\n");
		ret = -ENOMEM;
		goto err_stategpio;
	}
	drvdata->nr_states = config->nr_states;

	drvdata->desc.owner = THIS_MODULE;
	drvdata->desc.enable_time = config->startup_delay;

	/* handle regulator type*/
	switch (config->type) {
	case REGULATOR_VOLTAGE:
		drvdata->desc.type = REGULATOR_VOLTAGE;
		drvdata->desc.ops = &gpio_regulator_voltage_ops;
		drvdata->desc.n_voltages = config->nr_states;
		break;
	case REGULATOR_CURRENT:
		drvdata->desc.type = REGULATOR_CURRENT;
		drvdata->desc.ops = &gpio_regulator_current_ops;
		break;
	default:
		dev_err(&pdev->dev, "No regulator type set\n");
		ret = -EINVAL;
		goto err_memstate;
	}

	/* build initial state from gpio init data. */
	state = 0;
	for (ptr = 0; ptr < drvdata->nr_gpios; ptr++) {
		if (config->gpios[ptr].flags & GPIOF_OUT_INIT_HIGH)
			state |= (1 << ptr);
	}
	drvdata->state = state;

	cfg.dev = &pdev->dev;
	cfg.init_data = config->init_data;
	cfg.driver_data = drvdata;
	cfg.of_node = np;

	if (gpio_is_valid(config->enable_gpio)) {
		cfg.ena_gpio = config->enable_gpio;
		cfg.ena_gpio_initialized = true;
	}
	cfg.ena_gpio_invert = !config->enable_high;
	if (config->enabled_at_boot) {
		if (config->enable_high)
			cfg.ena_gpio_flags |= GPIOF_OUT_INIT_HIGH;
		else
			cfg.ena_gpio_flags |= GPIOF_OUT_INIT_LOW;
	} else {
		if (config->enable_high)
			cfg.ena_gpio_flags |= GPIOF_OUT_INIT_LOW;
		else
			cfg.ena_gpio_flags |= GPIOF_OUT_INIT_HIGH;
	}

	drvdata->dev = regulator_register(&drvdata->desc, &cfg);
	if (IS_ERR(drvdata->dev)) {
		ret = PTR_ERR(drvdata->dev);
		dev_err(&pdev->dev, "Failed to register regulator: %d\n", ret);
		goto err_memstate;
	}

	platform_set_drvdata(pdev, drvdata);

	return 0;

err_memstate:
	kfree(drvdata->states);
err_stategpio:
	gpio_free_array(drvdata->gpios, drvdata->nr_gpios);
err_memgpio:
	kfree(drvdata->gpios);
err_name:
	kfree(drvdata->desc.name);
	return ret;
}