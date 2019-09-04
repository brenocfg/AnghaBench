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
struct work_struct {int dummy; } ;
struct s3c_adc_bat {int cable_plugged; int /*<<< orphan*/  psy; void* status; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ gpio_charge_finished; int /*<<< orphan*/  (* enable_charger ) () ;int /*<<< orphan*/  (* disable_charger ) () ;} ;

/* Variables and functions */
 void* POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_DISCHARGING ; 
 void* POWER_SUPPLY_STATUS_FULL ; 
 int charge_finished (struct s3c_adc_bat*) ; 
 struct s3c_adc_bat main_bat ; 
 int power_supply_am_i_supplied (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 

__attribute__((used)) static void s3c_adc_bat_work(struct work_struct *work)
{
	struct s3c_adc_bat *bat = &main_bat;
	int is_charged;
	int is_plugged;
	static int was_plugged;

	is_plugged = power_supply_am_i_supplied(bat->psy);
	bat->cable_plugged = is_plugged;
	if (is_plugged != was_plugged) {
		was_plugged = is_plugged;
		if (is_plugged) {
			if (bat->pdata->enable_charger)
				bat->pdata->enable_charger();
			bat->status = POWER_SUPPLY_STATUS_CHARGING;
		} else {
			if (bat->pdata->disable_charger)
				bat->pdata->disable_charger();
			bat->status = POWER_SUPPLY_STATUS_DISCHARGING;
		}
	} else {
		if ((bat->pdata->gpio_charge_finished >= 0) && is_plugged) {
			is_charged = charge_finished(&main_bat);
			if (is_charged) {
				if (bat->pdata->disable_charger)
					bat->pdata->disable_charger();
				bat->status = POWER_SUPPLY_STATUS_FULL;
			} else {
				if (bat->pdata->enable_charger)
					bat->pdata->enable_charger();
				bat->status = POWER_SUPPLY_STATUS_CHARGING;
			}
		}
	}

	power_supply_changed(bat->psy);
}