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
struct gb_power_supply {int id; struct gb_power_supplies* supplies; } ;
struct gb_power_supplies {struct gb_power_supply* supply; } ;

/* Variables and functions */
 int gb_power_supply_description_get (struct gb_power_supply*) ; 
 int gb_power_supply_prop_descriptors_get (struct gb_power_supply*) ; 

__attribute__((used)) static int gb_power_supply_config(struct gb_power_supplies *supplies, int id)
{
	struct gb_power_supply *gbpsy = &supplies->supply[id];
	int ret;

	gbpsy->supplies = supplies;
	gbpsy->id = id;

	ret = gb_power_supply_description_get(gbpsy);
	if (ret < 0)
		return ret;

	return gb_power_supply_prop_descriptors_get(gbpsy);
}