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
union power_supply_propval {int intval; } ;
struct TYPE_2__ {int flags; } ;
struct bq27xxx_device_info {int opts; TYPE_1__ cache; int /*<<< orphan*/  bat; } ;

/* Variables and functions */
 int BQ27000_FLAG_CHGS ; 
 int BQ27000_FLAG_FC ; 
 int BQ27XXX_FLAG_DSC ; 
 int BQ27XXX_FLAG_FC ; 
 int BQ27XXX_O_ZERO ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 scalar_t__ power_supply_am_i_supplied (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq27xxx_battery_status(struct bq27xxx_device_info *di,
				  union power_supply_propval *val)
{
	int status;

	if (di->opts & BQ27XXX_O_ZERO) {
		if (di->cache.flags & BQ27000_FLAG_FC)
			status = POWER_SUPPLY_STATUS_FULL;
		else if (di->cache.flags & BQ27000_FLAG_CHGS)
			status = POWER_SUPPLY_STATUS_CHARGING;
		else if (power_supply_am_i_supplied(di->bat) > 0)
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		else
			status = POWER_SUPPLY_STATUS_DISCHARGING;
	} else {
		if (di->cache.flags & BQ27XXX_FLAG_FC)
			status = POWER_SUPPLY_STATUS_FULL;
		else if (di->cache.flags & BQ27XXX_FLAG_DSC)
			status = POWER_SUPPLY_STATUS_DISCHARGING;
		else
			status = POWER_SUPPLY_STATUS_CHARGING;
	}

	val->intval = status;

	return 0;
}