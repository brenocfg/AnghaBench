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
typedef  int uint8_t ;

/* Variables and functions */
 int BAT_ADDR_MFR_TYPE ; 
 int /*<<< orphan*/  EC_BAT_EEPROM ; 
 int EIO ; 
#define  POWER_SUPPLY_TECHNOLOGY_LiFe 129 
#define  POWER_SUPPLY_TECHNOLOGY_NiMH 128 
 int olpc_bat_get_tech (union power_supply_propval*) ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int*,int,int*,int) ; 

__attribute__((used)) static int olpc_bat_get_voltage_max_design(union power_supply_propval *val)
{
	uint8_t ec_byte;
	union power_supply_propval tech;
	int mfr;
	int ret;

	ret = olpc_bat_get_tech(&tech);
	if (ret)
		return ret;

	ec_byte = BAT_ADDR_MFR_TYPE;
	ret = olpc_ec_cmd(EC_BAT_EEPROM, &ec_byte, 1, &ec_byte, 1);
	if (ret)
		return ret;

	mfr = ec_byte >> 4;

	switch (tech.intval) {
	case POWER_SUPPLY_TECHNOLOGY_NiMH:
		switch (mfr) {
		case 1: /* Gold Peak */
			val->intval = 6000000;
			break;
		default:
			return -EIO;
		}
		break;

	case POWER_SUPPLY_TECHNOLOGY_LiFe:
		switch (mfr) {
		case 1: /* Gold Peak */
			val->intval = 6400000;
			break;
		case 2: /* BYD */
			val->intval = 6500000;
			break;
		default:
			return -EIO;
		}
		break;

	default:
		return -EIO;
	}

	return ret;
}