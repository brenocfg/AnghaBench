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
typedef  int u8 ;
struct regmap {int dummy; } ;
struct max14577_charger {TYPE_1__* max14577; } ;
typedef  enum max14577_muic_charger_type { ____Placeholder_max14577_muic_charger_type } max14577_muic_charger_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev_type; struct regmap* regmap; } ;

/* Variables and functions */
 int MAX14577_CHARGER_TYPE_DEAD_BATTERY ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_STATUS3 ; 
 int /*<<< orphan*/  MAX14577_MUIC_REG_STATUS2 ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int STATUS2_CHGTYP_MASK ; 
 int STATUS2_CHGTYP_SHIFT ; 
 int STATUS3_OVP_MASK ; 
 int max14577_read_reg (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int maxim_get_charger_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max14577_get_battery_health(struct max14577_charger *chg, int *val)
{
	struct regmap *rmap = chg->max14577->regmap;
	int ret;
	u8 reg_data;
	enum max14577_muic_charger_type chg_type;

	ret = max14577_read_reg(rmap, MAX14577_MUIC_REG_STATUS2, &reg_data);
	if (ret < 0)
		goto out;

	reg_data = ((reg_data & STATUS2_CHGTYP_MASK) >> STATUS2_CHGTYP_SHIFT);
	chg_type = maxim_get_charger_type(chg->max14577->dev_type, reg_data);
	if (chg_type == MAX14577_CHARGER_TYPE_DEAD_BATTERY) {
		*val = POWER_SUPPLY_HEALTH_DEAD;
		goto out;
	}

	ret = max14577_read_reg(rmap, MAX14577_CHG_REG_STATUS3, &reg_data);
	if (ret < 0)
		goto out;

	if (reg_data & STATUS3_OVP_MASK) {
		*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		goto out;
	}

	/* Not dead, not overvoltage */
	*val = POWER_SUPPLY_HEALTH_GOOD;

out:
	return ret;
}