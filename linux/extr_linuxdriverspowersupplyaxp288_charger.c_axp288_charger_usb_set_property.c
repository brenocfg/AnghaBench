#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct axp288_chrg_info {TYPE_1__* pdev; int /*<<< orphan*/  max_cv; int /*<<< orphan*/  max_cc; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 130 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 129 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 128 
 int axp288_charger_set_cc (struct axp288_chrg_info*,int) ; 
 int axp288_charger_set_cv (struct axp288_chrg_info*,int) ; 
 int axp288_charger_set_vbus_inlmt (struct axp288_chrg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axp288_chrg_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int axp288_charger_usb_set_property(struct power_supply *psy,
				    enum power_supply_property psp,
				    const union power_supply_propval *val)
{
	struct axp288_chrg_info *info = power_supply_get_drvdata(psy);
	int ret = 0;
	int scaled_val;

	switch (psp) {
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		scaled_val = min(val->intval, info->max_cc);
		scaled_val = DIV_ROUND_CLOSEST(scaled_val, 1000);
		ret = axp288_charger_set_cc(info, scaled_val);
		if (ret < 0)
			dev_warn(&info->pdev->dev, "set charge current failed\n");
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		scaled_val = min(val->intval, info->max_cv);
		scaled_val = DIV_ROUND_CLOSEST(scaled_val, 1000);
		ret = axp288_charger_set_cv(info, scaled_val);
		if (ret < 0)
			dev_warn(&info->pdev->dev, "set charge voltage failed\n");
		break;
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = axp288_charger_set_vbus_inlmt(info, val->intval);
		if (ret < 0)
			dev_warn(&info->pdev->dev, "set input current limit failed\n");
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}