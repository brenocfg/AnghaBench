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
struct power_supply {int dummy; } ;
struct gb_power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int is_psy_prop_writeable (struct gb_power_supply*,int) ; 
 struct gb_power_supply* to_gb_power_supply (struct power_supply*) ; 

__attribute__((used)) static int property_is_writeable(struct power_supply *b,
				 enum power_supply_property psp)
{
	struct gb_power_supply *gbpsy = to_gb_power_supply(b);

	return is_psy_prop_writeable(gbpsy, psp);
}