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
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
typedef  enum gab_chan_type { ____Placeholder_gab_chan_type } gab_chan_type ;

/* Variables and functions */
 int GAB_CURRENT ; 
 int GAB_POWER ; 
 int GAB_VOLTAGE ; 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 130 
#define  POWER_SUPPLY_PROP_POWER_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static enum gab_chan_type gab_prop_to_chan(enum power_supply_property psp)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_POWER_NOW:
		return GAB_POWER;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		return GAB_VOLTAGE;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		return GAB_CURRENT;
	default:
		WARN_ON(1);
		break;
	}
	return GAB_POWER;
}