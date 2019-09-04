#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct max77693_charger* drv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max77693_dev {int dummy; } ;
struct max77693_charger {int /*<<< orphan*/  charger; struct max77693_dev* max77693; TYPE_1__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_fast_charge_timer ; 
 int /*<<< orphan*/  dev_attr_top_off_threshold_current ; 
 int /*<<< orphan*/  dev_attr_top_off_timer ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct max77693_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct max77693_charger* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max77693_charger_desc ; 
 int max77693_dt_init (TYPE_1__*,struct max77693_charger*) ; 
 int max77693_reg_init (struct max77693_charger*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max77693_charger*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 

__attribute__((used)) static int max77693_charger_probe(struct platform_device *pdev)
{
	struct max77693_charger *chg;
	struct power_supply_config psy_cfg = {};
	struct max77693_dev *max77693 = dev_get_drvdata(pdev->dev.parent);
	int ret;

	chg = devm_kzalloc(&pdev->dev, sizeof(*chg), GFP_KERNEL);
	if (!chg)
		return -ENOMEM;

	platform_set_drvdata(pdev, chg);
	chg->dev = &pdev->dev;
	chg->max77693 = max77693;

	ret = max77693_dt_init(&pdev->dev, chg);
	if (ret)
		return ret;

	ret = max77693_reg_init(chg);
	if (ret)
		return ret;

	psy_cfg.drv_data = chg;

	ret = device_create_file(&pdev->dev, &dev_attr_fast_charge_timer);
	if (ret) {
		dev_err(&pdev->dev, "failed: create fast charge timer sysfs entry\n");
		goto err;
	}

	ret = device_create_file(&pdev->dev,
			&dev_attr_top_off_threshold_current);
	if (ret) {
		dev_err(&pdev->dev, "failed: create top off current sysfs entry\n");
		goto err;
	}

	ret = device_create_file(&pdev->dev, &dev_attr_top_off_timer);
	if (ret) {
		dev_err(&pdev->dev, "failed: create top off timer sysfs entry\n");
		goto err;
	}

	chg->charger = power_supply_register(&pdev->dev,
						&max77693_charger_desc,
						&psy_cfg);
	if (IS_ERR(chg->charger)) {
		dev_err(&pdev->dev, "failed: power supply register\n");
		ret = PTR_ERR(chg->charger);
		goto err;
	}

	return 0;

err:
	device_remove_file(&pdev->dev, &dev_attr_top_off_timer);
	device_remove_file(&pdev->dev, &dev_attr_top_off_threshold_current);
	device_remove_file(&pdev->dev, &dev_attr_fast_charge_timer);

	return ret;
}