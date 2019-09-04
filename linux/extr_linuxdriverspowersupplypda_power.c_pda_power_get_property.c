#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {TYPE_1__* desc; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {int /*<<< orphan*/  (* is_usb_online ) () ;int /*<<< orphan*/  (* is_ac_online ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_MAINS ; 
 TYPE_2__* pdata ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int pda_power_get_property(struct power_supply *psy,
				  enum power_supply_property psp,
				  union power_supply_propval *val)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		if (psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
			val->intval = pdata->is_ac_online ?
				      pdata->is_ac_online() : 0;
		else
			val->intval = pdata->is_usb_online ?
				      pdata->is_usb_online() : 0;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}