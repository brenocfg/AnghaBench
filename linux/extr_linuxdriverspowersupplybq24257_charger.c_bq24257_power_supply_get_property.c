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
union power_supply_propval {void* intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct bq24257_state {int /*<<< orphan*/  fault; void* power_good; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {size_t ichg; size_t vbat; size_t iterm; } ;
struct bq24257_device {size_t chip; TYPE_1__ init_data; int /*<<< orphan*/  lock; struct bq24257_state state; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24257_ICHG_MAP_SIZE ; 
 int /*<<< orphan*/  BQ24257_MANUFACTURER ; 
 int /*<<< orphan*/  BQ24257_VBAT_MAP_SIZE ; 
 int EINVAL ; 
#define  FAULT_BAT_OVP 144 
#define  FAULT_BAT_TS 143 
#define  FAULT_INPUT_OVP 142 
#define  FAULT_NORMAL 141 
#define  FAULT_TIMER 140 
#define  FAULT_TS 139 
 void* POWER_SUPPLY_HEALTH_GOOD ; 
 void* POWER_SUPPLY_HEALTH_OVERHEAT ; 
 void* POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 void* POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE ; 
 void* POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT 138 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 137 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX 136 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 135 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 132 
#define  POWER_SUPPLY_PROP_MANUFACTURER 131 
#define  POWER_SUPPLY_PROP_MODEL_NAME 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 void* POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_DISCHARGING ; 
 void* POWER_SUPPLY_STATUS_FULL ; 
 void* POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 void* POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  STATUS_CHARGE_DONE ; 
 int /*<<< orphan*/  STATUS_CHARGE_IN_PROGRESS ; 
 int /*<<< orphan*/  STATUS_READY ; 
 int bq24257_get_input_current_limit (struct bq24257_device*,union power_supply_propval*) ; 
 void** bq24257_ichg_map ; 
 void** bq24257_iterm_map ; 
 void** bq24257_vbat_map ; 
 int /*<<< orphan*/ * bq2425x_chip_name ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bq24257_device* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int bq24257_power_supply_get_property(struct power_supply *psy,
					     enum power_supply_property psp,
					     union power_supply_propval *val)
{
	struct bq24257_device *bq = power_supply_get_drvdata(psy);
	struct bq24257_state state;

	mutex_lock(&bq->lock);
	state = bq->state;
	mutex_unlock(&bq->lock);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (!state.power_good)
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (state.status == STATUS_READY)
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		else if (state.status == STATUS_CHARGE_IN_PROGRESS)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (state.status == STATUS_CHARGE_DONE)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else
			val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
		break;

	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ24257_MANUFACTURER;
		break;

	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq2425x_chip_name[bq->chip];
		break;

	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = state.power_good;
		break;

	case POWER_SUPPLY_PROP_HEALTH:
		switch (state.fault) {
		case FAULT_NORMAL:
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
			break;

		case FAULT_INPUT_OVP:
		case FAULT_BAT_OVP:
			val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
			break;

		case FAULT_TS:
		case FAULT_BAT_TS:
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
			break;

		case FAULT_TIMER:
			val->intval = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
			break;

		default:
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
			break;
		}

		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		val->intval = bq24257_ichg_map[bq->init_data.ichg];
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->intval = bq24257_ichg_map[BQ24257_ICHG_MAP_SIZE - 1];
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->intval = bq24257_vbat_map[bq->init_data.vbat];
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->intval = bq24257_vbat_map[BQ24257_VBAT_MAP_SIZE - 1];
		break;

	case POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		val->intval = bq24257_iterm_map[bq->init_data.iterm];
		break;

	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		return bq24257_get_input_current_limit(bq, val);

	default:
		return -EINVAL;
	}

	return 0;
}