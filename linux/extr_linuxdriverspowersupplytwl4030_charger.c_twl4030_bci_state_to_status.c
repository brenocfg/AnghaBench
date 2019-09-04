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

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int TWL4030_MSTATEC_COMPLETE1 ; 
 int TWL4030_MSTATEC_COMPLETE4 ; 
 int TWL4030_MSTATEC_MASK ; 
 int TWL4030_MSTATEC_QUICK1 ; 
 int TWL4030_MSTATEC_QUICK7 ; 

__attribute__((used)) static int twl4030_bci_state_to_status(int state)
{
	state &= TWL4030_MSTATEC_MASK;
	if (TWL4030_MSTATEC_QUICK1 <= state && state <= TWL4030_MSTATEC_QUICK7)
		return POWER_SUPPLY_STATUS_CHARGING;
	else if (TWL4030_MSTATEC_COMPLETE1 <= state &&
					state <= TWL4030_MSTATEC_COMPLETE4)
		return POWER_SUPPLY_STATUS_FULL;
	else
		return POWER_SUPPLY_STATUS_NOT_CHARGING;
}