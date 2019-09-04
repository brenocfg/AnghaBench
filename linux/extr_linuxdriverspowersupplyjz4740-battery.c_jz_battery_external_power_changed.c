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
struct jz_battery {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct jz_battery* psy_to_jz_battery (struct power_supply*) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void jz_battery_external_power_changed(struct power_supply *psy)
{
	struct jz_battery *jz_battery = psy_to_jz_battery(psy);

	mod_delayed_work(system_wq, &jz_battery->work, 0);
}