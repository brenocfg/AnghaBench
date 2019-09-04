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
struct TYPE_2__ {int min_volt; int max_volt; int max_curr; } ;
struct tcpm_port {TYPE_1__ pps_data; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 struct tcpm_port* power_supply_get_drvdata (struct power_supply*) ; 
 int tcpm_pps_set_op_curr (struct tcpm_port*,int) ; 
 int tcpm_pps_set_out_volt (struct tcpm_port*,int) ; 
 int tcpm_psy_set_online (struct tcpm_port*,union power_supply_propval const*) ; 

__attribute__((used)) static int tcpm_psy_set_prop(struct power_supply *psy,
			     enum power_supply_property psp,
			     const union power_supply_propval *val)
{
	struct tcpm_port *port = power_supply_get_drvdata(psy);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		ret = tcpm_psy_set_online(port, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (val->intval < port->pps_data.min_volt * 1000 ||
		    val->intval > port->pps_data.max_volt * 1000)
			ret = -EINVAL;
		else
			ret = tcpm_pps_set_out_volt(port, val->intval / 1000);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (val->intval > port->pps_data.max_curr * 1000)
			ret = -EINVAL;
		else
			ret = tcpm_pps_set_op_curr(port, val->intval / 1000);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}