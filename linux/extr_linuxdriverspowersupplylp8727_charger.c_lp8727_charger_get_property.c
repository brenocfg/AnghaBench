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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_2__* desc; TYPE_1__ dev; } ;
struct lp8727_chg {int /*<<< orphan*/  devid; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_PROP_ONLINE ; 
 struct lp8727_chg* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp8727_is_charger_attached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8727_charger_get_property(struct power_supply *psy,
				       enum power_supply_property psp,
				       union power_supply_propval *val)
{
	struct lp8727_chg *pchg = dev_get_drvdata(psy->dev.parent);

	if (psp != POWER_SUPPLY_PROP_ONLINE)
		return -EINVAL;

	val->intval = lp8727_is_charger_attached(psy->desc->name, pchg->devid);

	return 0;
}