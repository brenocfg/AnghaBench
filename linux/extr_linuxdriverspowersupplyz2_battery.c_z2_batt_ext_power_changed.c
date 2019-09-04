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
struct z2_charger {int /*<<< orphan*/  bat_work; } ;
struct power_supply {int dummy; } ;

/* Variables and functions */
 struct z2_charger* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void z2_batt_ext_power_changed(struct power_supply *batt_ps)
{
	struct z2_charger *charger = power_supply_get_drvdata(batt_ps);

	schedule_work(&charger->bat_work);
}