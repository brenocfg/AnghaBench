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
struct da9030_charger {scalar_t__ is_on; scalar_t__ chdet; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 

__attribute__((used)) static void da9030_battery_check_status(struct da9030_charger *charger,
				    union power_supply_propval *val)
{
	if (charger->chdet) {
		if (charger->is_on)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
	} else {
		val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
	}
}