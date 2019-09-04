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
struct regulator_config {int ena_gpio_initialized; int ena_gpio_invert; scalar_t__ of_node; struct fixed_voltage_data* driver_data; int /*<<< orphan*/  init_data; TYPE_1__* dev; int /*<<< orphan*/  ena_gpio_flags; int /*<<< orphan*/  ena_gpio; } ;
struct TYPE_10__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_11__ {int n_voltages; scalar_t__ fixed_uV; int /*<<< orphan*/ * name; void* supply_name; int /*<<< orphan*/  enable_time; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; } ;
struct fixed_voltage_data {TYPE_2__ desc; struct fixed_voltage_config* dev; } ;
struct fixed_voltage_config {int /*<<< orphan*/  init_data; scalar_t__ gpio_is_open_drain; scalar_t__ enable_high; scalar_t__ enabled_at_boot; int /*<<< orphan*/  gpio; scalar_t__ microvolts; scalar_t__ input_supply; int /*<<< orphan*/  startup_delay; scalar_t__ supply_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OPEN_DRAIN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 scalar_t__ IS_ERR (struct fixed_voltage_config*) ; 
 int PTR_ERR (struct fixed_voltage_config*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct fixed_voltage_config* dev_get_platdata (TYPE_1__*) ; 
 void* devm_kstrdup (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct fixed_voltage_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct fixed_voltage_config* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 int /*<<< orphan*/  fixed_voltage_ops ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct fixed_voltage_config* of_get_fixed_voltage_config (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fixed_voltage_data*) ; 

__attribute__((used)) static int reg_fixed_voltage_probe(struct platform_device *pdev)
{
	struct fixed_voltage_config *config;
	struct fixed_voltage_data *drvdata;
	struct regulator_config cfg = { };
	int ret;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct fixed_voltage_data),
			       GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	if (pdev->dev.of_node) {
		config = of_get_fixed_voltage_config(&pdev->dev,
						     &drvdata->desc);
		if (IS_ERR(config))
			return PTR_ERR(config);
	} else {
		config = dev_get_platdata(&pdev->dev);
	}

	if (!config)
		return -ENOMEM;

	drvdata->desc.name = devm_kstrdup(&pdev->dev,
					  config->supply_name,
					  GFP_KERNEL);
	if (drvdata->desc.name == NULL) {
		dev_err(&pdev->dev, "Failed to allocate supply name\n");
		return -ENOMEM;
	}
	drvdata->desc.type = REGULATOR_VOLTAGE;
	drvdata->desc.owner = THIS_MODULE;
	drvdata->desc.ops = &fixed_voltage_ops;

	drvdata->desc.enable_time = config->startup_delay;

	if (config->input_supply) {
		drvdata->desc.supply_name = devm_kstrdup(&pdev->dev,
					    config->input_supply,
					    GFP_KERNEL);
		if (!drvdata->desc.supply_name) {
			dev_err(&pdev->dev,
				"Failed to allocate input supply\n");
			return -ENOMEM;
		}
	}

	if (config->microvolts)
		drvdata->desc.n_voltages = 1;

	drvdata->desc.fixed_uV = config->microvolts;

	if (gpio_is_valid(config->gpio)) {
		cfg.ena_gpio = config->gpio;
		if (pdev->dev.of_node)
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
	if (config->gpio_is_open_drain)
		cfg.ena_gpio_flags |= GPIOF_OPEN_DRAIN;

	cfg.dev = &pdev->dev;
	cfg.init_data = config->init_data;
	cfg.driver_data = drvdata;
	cfg.of_node = pdev->dev.of_node;

	drvdata->dev = devm_regulator_register(&pdev->dev, &drvdata->desc,
					       &cfg);
	if (IS_ERR(drvdata->dev)) {
		ret = PTR_ERR(drvdata->dev);
		dev_err(&pdev->dev, "Failed to register regulator: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, drvdata);

	dev_dbg(&pdev->dev, "%s supplying %duV\n", drvdata->desc.name,
		drvdata->desc.fixed_uV);

	return 0;
}