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
struct TYPE_2__ {scalar_t__ resistor_sense; } ;
struct bq2415x_device {TYPE_1__ init_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_BOOST_MODE_DISABLE ; 
 int /*<<< orphan*/  BQ2415X_CHARGER_DISABLE ; 
 int /*<<< orphan*/  BQ2415X_CHARGER_ENABLE ; 
 int /*<<< orphan*/  BQ2415X_CHARGE_TERMINATION_DISABLE ; 
 int /*<<< orphan*/  BQ2415X_CHARGE_TERMINATION_ENABLE ; 
 int /*<<< orphan*/  battery_regulation_voltage ; 
 int /*<<< orphan*/  bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq2415x_set_default_value (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  charge_current ; 
 int /*<<< orphan*/  current_limit ; 
 int /*<<< orphan*/  termination_current ; 
 int /*<<< orphan*/  weak_battery_voltage ; 

__attribute__((used)) static int bq2415x_set_defaults(struct bq2415x_device *bq)
{
	bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_DISABLE);
	bq2415x_exec_command(bq, BQ2415X_CHARGER_DISABLE);
	bq2415x_exec_command(bq, BQ2415X_CHARGE_TERMINATION_DISABLE);

	bq2415x_set_default_value(bq, current_limit);
	bq2415x_set_default_value(bq, weak_battery_voltage);
	bq2415x_set_default_value(bq, battery_regulation_voltage);

	if (bq->init_data.resistor_sense > 0) {
		bq2415x_set_default_value(bq, charge_current);
		bq2415x_set_default_value(bq, termination_current);
		bq2415x_exec_command(bq, BQ2415X_CHARGE_TERMINATION_ENABLE);
	}

	bq2415x_exec_command(bq, BQ2415X_CHARGER_ENABLE);
	return 0;
}