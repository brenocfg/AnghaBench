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
typedef  int u8 ;

/* Variables and functions */
 int BAT_S0_DISCHRG_CRITICAL ; 
 int BAT_S0_LOW ; 
 int BAT_S1_EMPTY ; 
 int BAT_S1_FULL ; 
 int BAT_S2_LOW_LOW ; 
 int /*<<< orphan*/  BAT_STATUS0 ; 
 int /*<<< orphan*/  BAT_STATUS1 ; 
 int /*<<< orphan*/  BAT_STATUS2 ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_FULL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_LOW ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_NORMAL ; 
 int ec_read_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bat_capacity_level(void)
{
	u8 status0 = ec_read_u8(BAT_STATUS0);
	u8 status1 = ec_read_u8(BAT_STATUS1);
	u8 status2 = ec_read_u8(BAT_STATUS2);

	if (status0 & BAT_S0_DISCHRG_CRITICAL
			|| status1 & BAT_S1_EMPTY
			|| status2 & BAT_S2_LOW_LOW)
		return POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
	if (status0 & BAT_S0_LOW)
		return POWER_SUPPLY_CAPACITY_LEVEL_LOW;
	if (status1 & BAT_S1_FULL)
		return POWER_SUPPLY_CAPACITY_LEVEL_FULL;
	return POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
}