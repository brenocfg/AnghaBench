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
typedef  int u8 ;
struct lp8788_charger {int /*<<< orphan*/  lp; } ;
typedef  enum lp8788_charging_state { ____Placeholder_lp8788_charging_state } lp8788_charging_state ;

/* Variables and functions */
#define  LP8788_CC 133 
 int LP8788_CHG_STATE_M ; 
 int LP8788_CHG_STATE_S ; 
 int /*<<< orphan*/  LP8788_CHG_STATUS ; 
#define  LP8788_CV 132 
#define  LP8788_HIGH_CURRENT 131 
#define  LP8788_MAINTENANCE 130 
#define  LP8788_OFF 129 
#define  LP8788_PRECHARGE 128 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int lp8788_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp8788_get_battery_status(struct lp8788_charger *pchg,
				union power_supply_propval *val)
{
	enum lp8788_charging_state state;
	u8 data;
	int ret;

	ret = lp8788_read_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	if (ret)
		return ret;

	state = (data & LP8788_CHG_STATE_M) >> LP8788_CHG_STATE_S;
	switch (state) {
	case LP8788_OFF:
		val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case LP8788_PRECHARGE:
	case LP8788_CC:
	case LP8788_CV:
	case LP8788_HIGH_CURRENT:
		val->intval = POWER_SUPPLY_STATUS_CHARGING;
		break;
	case LP8788_MAINTENANCE:
		val->intval = POWER_SUPPLY_STATUS_FULL;
		break;
	default:
		val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	}

	return 0;
}