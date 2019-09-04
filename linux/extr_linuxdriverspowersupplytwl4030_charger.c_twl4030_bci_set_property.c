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
struct twl4030_bci {int /*<<< orphan*/  ac_cur; int /*<<< orphan*/  usb_cur_target; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_2__* desc; TYPE_1__ dev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 128 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_USB ; 
 struct twl4030_bci* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_charger_update_current (struct twl4030_bci*) ; 

__attribute__((used)) static int twl4030_bci_set_property(struct power_supply *psy,
				    enum power_supply_property psp,
				    const union power_supply_propval *val)
{
	struct twl4030_bci *bci = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		if (psy->desc->type == POWER_SUPPLY_TYPE_USB)
			bci->usb_cur_target = val->intval;
		else
			bci->ac_cur = val->intval;
		twl4030_charger_update_current(bci);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}