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
typedef  int /*<<< orphan*/  u8 ;
struct adp5061_state {int dummy; } ;

/* Variables and functions */
 int ADP5061_CHG_STATUS_2_BAT_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL ; 
 int /*<<< orphan*/  POWER_SUPPLY_CAPACITY_LEVEL_LOW ; 
 int /*<<< orphan*/  POWER_SUPPLY_CAPACITY_LEVEL_NORMAL ; 
 int /*<<< orphan*/  POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN ; 
 int adp5061_get_status (struct adp5061_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5061_get_battery_status(struct adp5061_state *st,
				      union power_supply_propval *val)
{
	u8 status1, status2;
	int ret;

	ret = adp5061_get_status(st, &status1, &status2);
	if (ret < 0)
		return ret;

	switch (ADP5061_CHG_STATUS_2_BAT_STATUS(status2)) {
	case 0x0: /* Battery monitor off */
	case 0x1: /* No battery */
		val->intval = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		break;
	case 0x2: /* VBAT < VTRK */
		val->intval = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		break;
	case 0x3: /* VTRK < VBAT_SNS < VWEAK */
		val->intval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		break;
	case 0x4: /* VBAT_SNS > VWEAK */
		val->intval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		break;
	}

	return ret;
}