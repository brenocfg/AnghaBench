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
struct st_thermal_sensor {int /*<<< orphan*/  regmap; } ;
typedef  enum st_thermal_power_state { ____Placeholder_st_thermal_power_state } st_thermal_power_state ;

/* Variables and functions */
 int /*<<< orphan*/  STIH416_MPE_CONF ; 
 unsigned int THERMAL_PDN ; 
 unsigned int THERMAL_SRSTN ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,unsigned int const) ; 

__attribute__((used)) static int st_mmap_power_ctrl(struct st_thermal_sensor *sensor,
			      enum st_thermal_power_state power_state)
{
	const unsigned int mask = (THERMAL_PDN | THERMAL_SRSTN);
	const unsigned int val = power_state ? mask : 0;

	return regmap_update_bits(sensor->regmap, STIH416_MPE_CONF, mask, val);
}