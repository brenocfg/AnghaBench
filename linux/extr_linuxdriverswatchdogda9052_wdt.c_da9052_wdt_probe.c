#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {TYPE_1__* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; int /*<<< orphan*/  timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct da9052_wdt_data {struct watchdog_device wdt; struct da9052* da9052; } ;
struct da9052 {TYPE_1__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_CONTROLD_TWDSCALE ; 
 int /*<<< orphan*/  DA9052_CONTROL_D_REG ; 
 int /*<<< orphan*/  DA9052_DEF_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int da9052_reg_update (struct da9052*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_wdt_info ; 
 int /*<<< orphan*/  da9052_wdt_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct da9052* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9052_wdt_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (TYPE_1__*,struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct da9052_wdt_data*) ; 

__attribute__((used)) static int da9052_wdt_probe(struct platform_device *pdev)
{
	struct da9052 *da9052 = dev_get_drvdata(pdev->dev.parent);
	struct da9052_wdt_data *driver_data;
	struct watchdog_device *da9052_wdt;
	int ret;

	driver_data = devm_kzalloc(&pdev->dev, sizeof(*driver_data),
				   GFP_KERNEL);
	if (!driver_data)
		return -ENOMEM;
	driver_data->da9052 = da9052;

	da9052_wdt = &driver_data->wdt;

	da9052_wdt->timeout = DA9052_DEF_TIMEOUT;
	da9052_wdt->info = &da9052_wdt_info;
	da9052_wdt->ops = &da9052_wdt_ops;
	da9052_wdt->parent = &pdev->dev;
	watchdog_set_drvdata(da9052_wdt, driver_data);

	ret = da9052_reg_update(da9052, DA9052_CONTROL_D_REG,
				DA9052_CONTROLD_TWDSCALE, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to disable watchdog bits, %d\n",
			ret);
		return ret;
	}

	ret = devm_watchdog_register_device(&pdev->dev, &driver_data->wdt);
	if (ret != 0) {
		dev_err(da9052->dev, "watchdog_register_device() failed: %d\n",
			ret);
		return ret;
	}

	return ret;
}