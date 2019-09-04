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
struct power_supply_config {struct lego_ev3_battery* drv_data; int /*<<< orphan*/  of_node; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct lego_ev3_battery {int v_max; int v_min; void* psy; int /*<<< orphan*/  technology; void* rechargeable_gpio; void* iio_i; void* iio_v; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  POWER_SUPPLY_TECHNOLOGY_LION ; 
 int /*<<< orphan*/  POWER_SUPPLY_TECHNOLOGY_UNKNOWN ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_iio_channel_get (struct device*,char*) ; 
 struct lego_ev3_battery* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_power_supply_register (struct device*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 scalar_t__ gpiod_get_value (void*) ; 
 int /*<<< orphan*/  lego_ev3_battery_desc ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lego_ev3_battery*) ; 

__attribute__((used)) static int lego_ev3_battery_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct lego_ev3_battery *batt;
	struct power_supply_config psy_cfg = {};
	int err;

	batt = devm_kzalloc(dev, sizeof(*batt), GFP_KERNEL);
	if (!batt)
		return -ENOMEM;

	platform_set_drvdata(pdev, batt);

	batt->iio_v = devm_iio_channel_get(dev, "voltage");
	err = PTR_ERR_OR_ZERO(batt->iio_v);
	if (err) {
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get voltage iio channel\n");
		return err;
	}

	batt->iio_i = devm_iio_channel_get(dev, "current");
	err = PTR_ERR_OR_ZERO(batt->iio_i);
	if (err) {
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get current iio channel\n");
		return err;
	}

	batt->rechargeable_gpio = devm_gpiod_get(dev, "rechargeable", GPIOD_IN);
	err = PTR_ERR_OR_ZERO(batt->rechargeable_gpio);
	if (err) {
		if (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get rechargeable gpio\n");
		return err;
	}

	/*
	 * The rechargeable battery indication switch cannot be changed without
	 * removing the battery, so we only need to read it once.
	 */
	if (gpiod_get_value(batt->rechargeable_gpio)) {
		/* 2-cell Li-ion, 7.4V nominal */
		batt->technology = POWER_SUPPLY_TECHNOLOGY_LION;
		batt->v_max = 84000000;
		batt->v_min = 60000000;
	} else {
		/* 6x AA Alkaline, 9V nominal */
		batt->technology = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		batt->v_max = 90000000;
		batt->v_min = 48000000;
	}

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = batt;

	batt->psy = devm_power_supply_register(dev, &lego_ev3_battery_desc,
					       &psy_cfg);
	err = PTR_ERR_OR_ZERO(batt->psy);
	if (err) {
		dev_err(dev, "failed to register power supply\n");
		return err;
	}

	return 0;
}