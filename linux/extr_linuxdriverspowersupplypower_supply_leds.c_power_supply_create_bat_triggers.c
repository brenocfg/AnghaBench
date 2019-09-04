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
struct power_supply {void* charging_full_trig_name; void* charging_trig_name; void* full_trig_name; int /*<<< orphan*/  charging_blink_full_solid_trig; void* charging_blink_full_solid_trig_name; int /*<<< orphan*/  full_trig; int /*<<< orphan*/  charging_trig; int /*<<< orphan*/  charging_full_trig; TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  led_trigger_register_simple (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int power_supply_create_bat_triggers(struct power_supply *psy)
{
	psy->charging_full_trig_name = kasprintf(GFP_KERNEL,
					"%s-charging-or-full", psy->desc->name);
	if (!psy->charging_full_trig_name)
		goto charging_full_failed;

	psy->charging_trig_name = kasprintf(GFP_KERNEL,
					"%s-charging", psy->desc->name);
	if (!psy->charging_trig_name)
		goto charging_failed;

	psy->full_trig_name = kasprintf(GFP_KERNEL, "%s-full", psy->desc->name);
	if (!psy->full_trig_name)
		goto full_failed;

	psy->charging_blink_full_solid_trig_name = kasprintf(GFP_KERNEL,
		"%s-charging-blink-full-solid", psy->desc->name);
	if (!psy->charging_blink_full_solid_trig_name)
		goto charging_blink_full_solid_failed;

	led_trigger_register_simple(psy->charging_full_trig_name,
				    &psy->charging_full_trig);
	led_trigger_register_simple(psy->charging_trig_name,
				    &psy->charging_trig);
	led_trigger_register_simple(psy->full_trig_name,
				    &psy->full_trig);
	led_trigger_register_simple(psy->charging_blink_full_solid_trig_name,
				    &psy->charging_blink_full_solid_trig);

	return 0;

charging_blink_full_solid_failed:
	kfree(psy->full_trig_name);
full_failed:
	kfree(psy->charging_trig_name);
charging_failed:
	kfree(psy->charging_full_trig_name);
charging_full_failed:
	return -ENOMEM;
}