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
struct st_thermal_sensor {int /*<<< orphan*/  pwr; } ;
typedef  enum st_thermal_power_state { ____Placeholder_st_thermal_power_state } st_thermal_power_state ;

/* Variables and functions */
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_syscfg_power_ctrl(struct st_thermal_sensor *sensor,
				enum st_thermal_power_state power_state)
{
	return regmap_field_write(sensor->pwr, power_state);
}