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
struct gb_power_supply_prop {int val; int previous_val; scalar_t__ prop; } ;
struct gb_power_supply_changes {scalar_t__ prop; int tolerance_change; int /*<<< orphan*/  (* prop_changed ) (struct gb_power_supply*,struct gb_power_supply_prop*) ;} ;
struct gb_power_supply {int changed; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gb_power_supply_changes*) ; 
 struct gb_power_supply_changes* psy_props_changes ; 
 int /*<<< orphan*/  stub1 (struct gb_power_supply*,struct gb_power_supply_prop*) ; 

__attribute__((used)) static void check_changed(struct gb_power_supply *gbpsy,
			  struct gb_power_supply_prop *prop)
{
	const struct gb_power_supply_changes *psyc;
	int val = prop->val;
	int prev_val = prop->previous_val;
	bool changed = false;
	int i;

	for (i = 0; i < ARRAY_SIZE(psy_props_changes); i++) {
		psyc = &psy_props_changes[i];
		if (prop->prop == psyc->prop) {
			if (!psyc->tolerance_change)
				changed = true;
			else if (val < prev_val &&
				 prev_val - val > psyc->tolerance_change)
				changed = true;
			else if (val > prev_val &&
				 val - prev_val > psyc->tolerance_change)
				changed = true;

			if (changed && psyc->prop_changed)
				psyc->prop_changed(gbpsy, prop);

			if (changed)
				gbpsy->changed = true;
			break;
		}
	}
}