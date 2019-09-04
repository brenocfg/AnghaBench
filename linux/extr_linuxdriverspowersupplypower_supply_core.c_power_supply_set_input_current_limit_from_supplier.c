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
union power_supply_propval {int intval; int /*<<< orphan*/  member_0; } ;
struct power_supply {TYPE_1__* desc; } ;
struct TYPE_2__ {int (* set_property ) (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT ; 
 int /*<<< orphan*/  __power_supply_get_supplier_max_current ; 
 int class_for_each_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct power_supply*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_class ; 
 int stub1 (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 

int power_supply_set_input_current_limit_from_supplier(struct power_supply *psy)
{
	union power_supply_propval val = {0,};
	int curr;

	if (!psy->desc->set_property)
		return -EINVAL;

	/*
	 * This function is not intended for use with a supply with multiple
	 * suppliers, we simply pick the first supply to report a non 0
	 * max-current.
	 */
	curr = class_for_each_device(power_supply_class, NULL, psy,
				      __power_supply_get_supplier_max_current);
	if (curr <= 0)
		return (curr == 0) ? -ENODEV : curr;

	val.intval = curr;

	return psy->desc->set_property(psy,
				POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT, &val);
}