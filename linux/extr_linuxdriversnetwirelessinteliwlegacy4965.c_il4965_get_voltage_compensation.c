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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ TX_POWER_IL_ILLEGAL_VOLTAGE ; 
 int /*<<< orphan*/  TX_POWER_IL_VOLTAGE_CODES_PER_03V ; 
 int /*<<< orphan*/  il4965_math_div_round (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static s32
il4965_get_voltage_compensation(s32 eeprom_voltage, s32 current_voltage)
{
	s32 comp = 0;

	if (TX_POWER_IL_ILLEGAL_VOLTAGE == eeprom_voltage ||
	    TX_POWER_IL_ILLEGAL_VOLTAGE == current_voltage)
		return 0;

	il4965_math_div_round(current_voltage - eeprom_voltage,
			      TX_POWER_IL_VOLTAGE_CODES_PER_03V, &comp);

	if (current_voltage > eeprom_voltage)
		comp *= 2;
	if ((comp < -2) || (comp > 2))
		comp = 0;

	return comp;
}