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
struct i2c_client {int dummy; } ;
typedef  int s32 ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int min_value; int max_value; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANUFACTURER_ACCESS_STATUS ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int POWER_SUPPLY_PROP_HEALTH ; 
 int POWER_SUPPLY_PROP_PRESENT ; 
 size_t REG_MANUFACTURER_DATA ; 
 TYPE_1__* sbs_data ; 
 int sbs_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int sbs_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbs_get_ti_battery_presence_and_health(
	struct i2c_client *client, enum power_supply_property psp,
	union power_supply_propval *val)
{
	s32 ret;

	/*
	 * Write to ManufacturerAccess with ManufacturerAccess command
	 * and then read the status.
	 */
	ret = sbs_write_word_data(client, sbs_data[REG_MANUFACTURER_DATA].addr,
				  MANUFACTURER_ACCESS_STATUS);
	if (ret < 0) {
		if (psp == POWER_SUPPLY_PROP_PRESENT)
			val->intval = 0; /* battery removed */
		return ret;
	}

	ret = sbs_read_word_data(client, sbs_data[REG_MANUFACTURER_DATA].addr);
	if (ret < 0) {
		if (psp == POWER_SUPPLY_PROP_PRESENT)
			val->intval = 0; /* battery removed */
		return ret;
	}

	if (ret < sbs_data[REG_MANUFACTURER_DATA].min_value ||
	    ret > sbs_data[REG_MANUFACTURER_DATA].max_value) {
		val->intval = 0;
		return 0;
	}

	/* Mask the upper nibble of 2nd byte and
	 * lower byte of response then
	 * shift the result by 8 to get status*/
	ret &= 0x0F00;
	ret >>= 8;
	if (psp == POWER_SUPPLY_PROP_PRESENT) {
		if (ret == 0x0F)
			/* battery removed */
			val->intval = 0;
		else
			val->intval = 1;
	} else if (psp == POWER_SUPPLY_PROP_HEALTH) {
		if (ret == 0x09)
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		else if (ret == 0x0B)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else if (ret == 0x0C)
			val->intval = POWER_SUPPLY_HEALTH_DEAD;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
	}

	return 0;
}