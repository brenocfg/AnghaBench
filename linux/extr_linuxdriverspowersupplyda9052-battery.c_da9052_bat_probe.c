#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct da9052_battery* drv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct da9052_pdata {int use_for_apm; } ;
struct TYPE_10__ {int /*<<< orphan*/  notifier_call; } ;
struct da9052_battery {TYPE_6__* da9052; int /*<<< orphan*/  psy; TYPE_1__ nb; int /*<<< orphan*/  health; int /*<<< orphan*/  status; int /*<<< orphan*/  charger_type; } ;
typedef  int s32 ;
struct TYPE_14__ {struct da9052_pdata* platform_data; } ;
struct TYPE_13__ {TYPE_7__* dev; } ;
struct TYPE_11__ {int use_for_apm; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DA9052_NOCHARGER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_USB_current_notifier ; 
 int /*<<< orphan*/  da9052_bat_irq ; 
 int /*<<< orphan*/ * da9052_bat_irq_bits ; 
 int /*<<< orphan*/ * da9052_bat_irqs ; 
 int /*<<< orphan*/  da9052_free_irq (TYPE_6__*,int /*<<< orphan*/ ,struct da9052_battery*) ; 
 int da9052_request_irq (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da9052_battery*) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9052_battery* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9052_battery*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_3__*,TYPE_2__*,struct power_supply_config*) ; 
 TYPE_2__ psy_desc ; 

__attribute__((used)) static s32 da9052_bat_probe(struct platform_device *pdev)
{
	struct da9052_pdata *pdata;
	struct da9052_battery *bat;
	struct power_supply_config psy_cfg = {};
	int ret;
	int i;

	bat = devm_kzalloc(&pdev->dev, sizeof(struct da9052_battery),
				GFP_KERNEL);
	if (!bat)
		return -ENOMEM;

	psy_cfg.drv_data = bat;

	bat->da9052 = dev_get_drvdata(pdev->dev.parent);
	bat->charger_type = DA9052_NOCHARGER;
	bat->status = POWER_SUPPLY_STATUS_UNKNOWN;
	bat->health = POWER_SUPPLY_HEALTH_UNKNOWN;
	bat->nb.notifier_call = da9052_USB_current_notifier;

	pdata = bat->da9052->dev->platform_data;
	if (pdata != NULL && pdata->use_for_apm)
		psy_desc.use_for_apm = pdata->use_for_apm;
	else
		psy_desc.use_for_apm = 1;

	for (i = 0; i < ARRAY_SIZE(da9052_bat_irqs); i++) {
		ret = da9052_request_irq(bat->da9052,
				da9052_bat_irq_bits[i], da9052_bat_irqs[i],
				da9052_bat_irq, bat);

		if (ret != 0) {
			dev_err(bat->da9052->dev,
				"DA9052 failed to request %s IRQ: %d\n",
				da9052_bat_irqs[i], ret);
			goto err;
		}
	}

	bat->psy = power_supply_register(&pdev->dev, &psy_desc, &psy_cfg);
	if (IS_ERR(bat->psy)) {
		ret = PTR_ERR(bat->psy);
		goto err;
	}

	platform_set_drvdata(pdev, bat);
	return 0;

err:
	while (--i >= 0)
		da9052_free_irq(bat->da9052, da9052_bat_irq_bits[i], bat);

	return ret;
}