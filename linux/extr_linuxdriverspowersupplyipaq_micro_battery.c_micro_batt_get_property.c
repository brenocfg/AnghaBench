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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct micro_battery {int temperature; int voltage; int /*<<< orphan*/  chemistry; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  MICRO_BATT_CHEM_LION 137 
#define  MICRO_BATT_CHEM_LIPOLY 136 
#define  MICRO_BATT_CHEM_NICD 135 
#define  MICRO_BATT_CHEM_NIMH 134 
#define  POWER_SUPPLY_PROP_CAPACITY 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int POWER_SUPPLY_TECHNOLOGY_LIPO ; 
 int POWER_SUPPLY_TECHNOLOGY_NiCd ; 
 int POWER_SUPPLY_TECHNOLOGY_NiMH ; 
 int POWER_SUPPLY_TECHNOLOGY_UNKNOWN ; 
 struct micro_battery* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int get_capacity (struct power_supply*) ; 
 int get_status (struct power_supply*) ; 

__attribute__((used)) static int micro_batt_get_property(struct power_supply *b,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	struct micro_battery *mb = dev_get_drvdata(b->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		switch (mb->chemistry) {
		case MICRO_BATT_CHEM_NICD:
			val->intval = POWER_SUPPLY_TECHNOLOGY_NiCd;
			break;
		case MICRO_BATT_CHEM_NIMH:
			val->intval = POWER_SUPPLY_TECHNOLOGY_NiMH;
			break;
		case MICRO_BATT_CHEM_LION:
			val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
			break;
		case MICRO_BATT_CHEM_LIPOLY:
			val->intval = POWER_SUPPLY_TECHNOLOGY_LIPO;
			break;
		default:
			val->intval = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
			break;
		};
		break;
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = get_status(b);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = 4700000;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = get_capacity(b);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = mb->temperature;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = mb->voltage;
		break;
	default:
		return -EINVAL;
	};

	return 0;
}