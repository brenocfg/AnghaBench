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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct adp5061_state {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT 135 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 134 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 133 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 132 
#define  POWER_SUPPLY_PROP_PRECHARGE_CURRENT 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 128 
 int adp5061_set_const_chg_current (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_const_chg_vmax (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_input_current_limit (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_max_voltage (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_min_voltage (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_prechg_current (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_termination_current (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 int adp5061_set_vweak_th (struct adp5061_state*,int /*<<< orphan*/ ) ; 
 struct adp5061_state* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int adp5061_set_property(struct power_supply *psy,
				enum power_supply_property psp,
				const union power_supply_propval *val)
{
	struct adp5061_state *st = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		return adp5061_set_input_current_limit(st, val->intval);
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		return adp5061_set_max_voltage(st, val->intval);
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		return adp5061_set_min_voltage(st, val->intval);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		return adp5061_set_const_chg_vmax(st, val->intval);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		return adp5061_set_const_chg_current(st, val->intval);
	case POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		return adp5061_set_prechg_current(st, val->intval);
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		return adp5061_set_vweak_th(st, val->intval);
	case POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		return adp5061_set_termination_current(st, val->intval);
	default:
		return -EINVAL;
	}

	return 0;
}