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
struct power_supply_config {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct max8925_power_pdata {int /*<<< orphan*/  no_insert_detect; int /*<<< orphan*/  no_temp_support; int /*<<< orphan*/  set_charger; int /*<<< orphan*/  fast_charge; int /*<<< orphan*/  topoff_threshold; int /*<<< orphan*/  batt_detect; int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; } ;
struct max8925_power_info {TYPE_2__* ac; TYPE_2__* usb; int /*<<< orphan*/  no_insert_detect; int /*<<< orphan*/  no_temp_support; int /*<<< orphan*/  set_charger; int /*<<< orphan*/  fast_charge; int /*<<< orphan*/  topoff_threshold; int /*<<< orphan*/  batt_detect; TYPE_2__* battery; int /*<<< orphan*/  adc; int /*<<< orphan*/  gpm; struct max8925_chip* chip; } ;
struct max8925_chip {int /*<<< orphan*/  adc; int /*<<< orphan*/  i2c; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  ac_desc ; 
 int /*<<< orphan*/  battery_desc ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct max8925_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct max8925_power_info* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8925_init_charger (struct max8925_chip*,struct max8925_power_info*) ; 
 struct max8925_power_pdata* max8925_power_dt_init (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8925_power_info*) ; 
 void* power_supply_register (TYPE_3__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_desc ; 

__attribute__((used)) static int max8925_power_probe(struct platform_device *pdev)
{
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {}; /* Only for ac and usb */
	struct max8925_power_pdata *pdata = NULL;
	struct max8925_power_info *info;
	int ret;

	pdata = max8925_power_dt_init(pdev);
	if (!pdata) {
		dev_err(&pdev->dev, "platform data isn't assigned to "
			"power supply\n");
		return -EINVAL;
	}

	info = devm_kzalloc(&pdev->dev, sizeof(struct max8925_power_info),
				GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	info->chip = chip;
	info->gpm = chip->i2c;
	info->adc = chip->adc;
	platform_set_drvdata(pdev, info);

	psy_cfg.supplied_to = pdata->supplied_to;
	psy_cfg.num_supplicants = pdata->num_supplicants;

	info->ac = power_supply_register(&pdev->dev, &ac_desc, &psy_cfg);
	if (IS_ERR(info->ac)) {
		ret = PTR_ERR(info->ac);
		goto out;
	}
	info->ac->dev.parent = &pdev->dev;

	info->usb = power_supply_register(&pdev->dev, &usb_desc, &psy_cfg);
	if (IS_ERR(info->usb)) {
		ret = PTR_ERR(info->usb);
		goto out_unregister_ac;
	}
	info->usb->dev.parent = &pdev->dev;

	info->battery = power_supply_register(&pdev->dev, &battery_desc, NULL);
	if (IS_ERR(info->battery)) {
		ret = PTR_ERR(info->battery);
		goto out_unregister_usb;
	}
	info->battery->dev.parent = &pdev->dev;

	info->batt_detect = pdata->batt_detect;
	info->topoff_threshold = pdata->topoff_threshold;
	info->fast_charge = pdata->fast_charge;
	info->set_charger = pdata->set_charger;
	info->no_temp_support = pdata->no_temp_support;
	info->no_insert_detect = pdata->no_insert_detect;

	max8925_init_charger(chip, info);
	return 0;
out_unregister_usb:
	power_supply_unregister(info->usb);
out_unregister_ac:
	power_supply_unregister(info->ac);
out:
	return ret;
}