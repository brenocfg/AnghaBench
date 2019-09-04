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
struct gb_power_supply {int* props_raw; int /*<<< orphan*/  properties_count_str; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* krealloc (int*,int,int /*<<< orphan*/ ) ; 
 int total_props (struct gb_power_supply*) ; 

__attribute__((used)) static void prop_append(struct gb_power_supply *gbpsy,
			enum power_supply_property prop)
{
	enum power_supply_property *new_props_raw;

	gbpsy->properties_count_str++;
	new_props_raw = krealloc(gbpsy->props_raw, total_props(gbpsy) *
				 sizeof(enum power_supply_property),
				 GFP_KERNEL);
	if (!new_props_raw)
		return;
	gbpsy->props_raw = new_props_raw;
	gbpsy->props_raw[total_props(gbpsy) - 1] = prop;
}