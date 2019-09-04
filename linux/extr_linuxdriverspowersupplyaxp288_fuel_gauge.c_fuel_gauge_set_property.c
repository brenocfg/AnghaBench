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
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
struct axp288_fg_info {int /*<<< orphan*/  lock; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  AXP288_FG_LOW_CAP_REG ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN 128 
 int fuel_gauge_reg_readb (struct axp288_fg_info*,int /*<<< orphan*/ ) ; 
 int fuel_gauge_reg_writeb (struct axp288_fg_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct axp288_fg_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int fuel_gauge_set_property(struct power_supply *ps,
		enum power_supply_property prop,
		const union power_supply_propval *val)
{
	struct axp288_fg_info *info = power_supply_get_drvdata(ps);
	int ret = 0;

	mutex_lock(&info->lock);
	switch (prop) {
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		if ((val->intval < 0) || (val->intval > 15)) {
			ret = -EINVAL;
			break;
		}
		ret = fuel_gauge_reg_readb(info, AXP288_FG_LOW_CAP_REG);
		if (ret < 0)
			break;
		ret &= 0xf0;
		ret |= (val->intval & 0xf);
		ret = fuel_gauge_reg_writeb(info, AXP288_FG_LOW_CAP_REG, ret);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&info->lock);
	return ret;
}