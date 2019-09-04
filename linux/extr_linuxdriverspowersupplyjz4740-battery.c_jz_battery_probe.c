#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct power_supply_desc {int use_for_apm; int /*<<< orphan*/  external_power_changed; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct power_supply_config {struct jz_battery* drv_data; } ;
struct TYPE_9__ {TYPE_3__* parent; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int voltage_max_design; int /*<<< orphan*/  name; } ;
struct jz_battery_platform_data {int /*<<< orphan*/  gpio_charge; TYPE_1__ info; } ;
struct jz_battery {int irq; int charge_irq; struct jz_battery_platform_data* pdata; int /*<<< orphan*/  work; int /*<<< orphan*/  battery; int /*<<< orphan*/  lock; int /*<<< orphan*/  read_completion; struct platform_device* pdev; struct power_supply_desc battery_desc; int /*<<< orphan*/  base; int /*<<< orphan*/  cell; } ;
struct TYPE_10__ {struct jz_battery_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_ADC_CONFIG_BAT_MB ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct jz_battery* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  free_irq (int,struct jz_battery*) ; 
 int gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4740_adc_set_config (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz_battery_charge_irq ; 
 int /*<<< orphan*/  jz_battery_external_power_changed ; 
 int /*<<< orphan*/  jz_battery_get_property ; 
 int /*<<< orphan*/  jz_battery_irq_handler ; 
 int /*<<< orphan*/  jz_battery_properties ; 
 int /*<<< orphan*/  jz_battery_work ; 
 int /*<<< orphan*/  mfd_get_cell (struct platform_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz_battery*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_2__*,struct power_supply_desc*,struct power_supply_config*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct jz_battery*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz_battery_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct jz_battery_platform_data *pdata = pdev->dev.parent->platform_data;
	struct power_supply_config psy_cfg = {};
	struct jz_battery *jz_battery;
	struct power_supply_desc *battery_desc;
	struct resource *mem;

	if (!pdata) {
		dev_err(&pdev->dev, "No platform_data supplied\n");
		return -ENXIO;
	}

	jz_battery = devm_kzalloc(&pdev->dev, sizeof(*jz_battery), GFP_KERNEL);
	if (!jz_battery) {
		dev_err(&pdev->dev, "Failed to allocate driver structure\n");
		return -ENOMEM;
	}

	jz_battery->cell = mfd_get_cell(pdev);

	jz_battery->irq = platform_get_irq(pdev, 0);
	if (jz_battery->irq < 0) {
		dev_err(&pdev->dev, "Failed to get platform irq: %d\n", ret);
		return jz_battery->irq;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	jz_battery->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(jz_battery->base))
		return PTR_ERR(jz_battery->base);

	battery_desc = &jz_battery->battery_desc;
	battery_desc->name = pdata->info.name;
	battery_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	battery_desc->properties	= jz_battery_properties;
	battery_desc->num_properties	= ARRAY_SIZE(jz_battery_properties);
	battery_desc->get_property	= jz_battery_get_property;
	battery_desc->external_power_changed =
					jz_battery_external_power_changed;
	battery_desc->use_for_apm	= 1;

	psy_cfg.drv_data = jz_battery;

	jz_battery->pdata = pdata;
	jz_battery->pdev = pdev;

	init_completion(&jz_battery->read_completion);
	mutex_init(&jz_battery->lock);

	INIT_DELAYED_WORK(&jz_battery->work, jz_battery_work);

	ret = request_irq(jz_battery->irq, jz_battery_irq_handler, 0, pdev->name,
			jz_battery);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq %d\n", ret);
		return ret;
	}
	disable_irq(jz_battery->irq);

	if (gpio_is_valid(pdata->gpio_charge)) {
		ret = gpio_request(pdata->gpio_charge, dev_name(&pdev->dev));
		if (ret) {
			dev_err(&pdev->dev, "charger state gpio request failed.\n");
			goto err_free_irq;
		}
		ret = gpio_direction_input(pdata->gpio_charge);
		if (ret) {
			dev_err(&pdev->dev, "charger state gpio set direction failed.\n");
			goto err_free_gpio;
		}

		jz_battery->charge_irq = gpio_to_irq(pdata->gpio_charge);

		if (jz_battery->charge_irq >= 0) {
			ret = request_irq(jz_battery->charge_irq,
				    jz_battery_charge_irq,
				    IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				    dev_name(&pdev->dev), jz_battery);
			if (ret) {
				dev_err(&pdev->dev, "Failed to request charge irq: %d\n", ret);
				goto err_free_gpio;
			}
		}
	} else {
		jz_battery->charge_irq = -1;
	}

	if (jz_battery->pdata->info.voltage_max_design <= 2500000)
		jz4740_adc_set_config(pdev->dev.parent, JZ_ADC_CONFIG_BAT_MB,
			JZ_ADC_CONFIG_BAT_MB);
	else
		jz4740_adc_set_config(pdev->dev.parent, JZ_ADC_CONFIG_BAT_MB, 0);

	jz_battery->battery = power_supply_register(&pdev->dev, battery_desc,
							&psy_cfg);
	if (IS_ERR(jz_battery->battery)) {
		dev_err(&pdev->dev, "power supply battery register failed.\n");
		ret = PTR_ERR(jz_battery->battery);
		goto err_free_charge_irq;
	}

	platform_set_drvdata(pdev, jz_battery);
	schedule_delayed_work(&jz_battery->work, 0);

	return 0;

err_free_charge_irq:
	if (jz_battery->charge_irq >= 0)
		free_irq(jz_battery->charge_irq, jz_battery);
err_free_gpio:
	if (gpio_is_valid(pdata->gpio_charge))
		gpio_free(jz_battery->pdata->gpio_charge);
err_free_irq:
	free_irq(jz_battery->irq, jz_battery);
	return ret;
}