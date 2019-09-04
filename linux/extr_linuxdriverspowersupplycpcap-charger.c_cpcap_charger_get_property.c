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
struct cpcap_charger_ddata {int status; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int cpcap_charger_get_charge_current (struct cpcap_charger_ddata*) ; 
 int cpcap_charger_get_charge_voltage (struct cpcap_charger_ddata*) ; 
 struct cpcap_charger_ddata* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_charger_get_property(struct power_supply *psy,
				      enum power_supply_property psp,
				      union power_supply_propval *val)
{
	struct cpcap_charger_ddata *ddata = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = ddata->status;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (ddata->status == POWER_SUPPLY_STATUS_CHARGING)
			val->intval = cpcap_charger_get_charge_voltage(ddata) *
				1000;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (ddata->status == POWER_SUPPLY_STATUS_CHARGING)
			val->intval = cpcap_charger_get_charge_current(ddata) *
				1000;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = ddata->status == POWER_SUPPLY_STATUS_CHARGING;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}