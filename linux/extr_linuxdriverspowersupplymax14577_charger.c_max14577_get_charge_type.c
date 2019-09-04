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
struct max14577_charger {int dummy; } ;

/* Variables and functions */
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int max14577_get_charger_state (struct max14577_charger*,int*) ; 

__attribute__((used)) static int max14577_get_charge_type(struct max14577_charger *chg, int *val)
{
	int ret, charging;

	/*
	 * TODO: CHARGE_TYPE_TRICKLE (VCHGR_RC or EOC)?
	 * As spec says:
	 * [after reaching EOC interrupt]
	 * "When the battery is fully charged, the 30-minute (typ)
	 *  top-off timer starts. The device continues to trickle
	 *  charge the battery until the top-off timer runs out."
	 */
	ret = max14577_get_charger_state(chg, &charging);
	if (ret < 0)
		return ret;

	if (charging == POWER_SUPPLY_STATUS_CHARGING)
		*val = POWER_SUPPLY_CHARGE_TYPE_FAST;
	else
		*val = POWER_SUPPLY_CHARGE_TYPE_NONE;

	return 0;
}