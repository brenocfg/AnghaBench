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
struct TYPE_3__ {scalar_t__ vbat_low; scalar_t__ vbat_crit; } ;
struct TYPE_4__ {scalar_t__ vbat_res; } ;
struct da9030_charger {int /*<<< orphan*/  (* battery_critical ) () ;TYPE_1__ thresholds; TYPE_2__ adc; int /*<<< orphan*/  (* battery_low ) () ;int /*<<< orphan*/  master; scalar_t__ is_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_VBATMON ; 
 int /*<<< orphan*/  da9030_read_adc (struct da9030_charger*,TYPE_2__*) ; 
 int /*<<< orphan*/  da903x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void da9030_battery_vbat_event(struct da9030_charger *charger)
{
	da9030_read_adc(charger, &charger->adc);

	if (charger->is_on)
		return;

	if (charger->adc.vbat_res < charger->thresholds.vbat_low) {
		/* set VBAT threshold for critical */
		da903x_write(charger->master, DA9030_VBATMON,
			     charger->thresholds.vbat_crit);
		if (charger->battery_low)
			charger->battery_low();
	} else if (charger->adc.vbat_res <
		   charger->thresholds.vbat_crit) {
		/* notify the system of battery critical */
		if (charger->battery_critical)
			charger->battery_critical();
	}
}