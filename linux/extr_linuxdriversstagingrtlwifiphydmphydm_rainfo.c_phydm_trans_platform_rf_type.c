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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ PHYDM_RF_1T1R ; 
 scalar_t__ PHYDM_RF_1T2R ; 
 scalar_t__ PHYDM_RF_2T2R ; 
 scalar_t__ PHYDM_RF_2T2R_GREEN ; 
 scalar_t__ PHYDM_RF_2T4R ; 
 scalar_t__ PHYDM_RF_3T3R ; 
 scalar_t__ PHYDM_RF_3T4R ; 
 scalar_t__ PHYDM_RF_4T4R ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
 scalar_t__ RF_2T2R_GREEN ; 
 scalar_t__ RF_2T3R ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ RF_3T3R ; 
 scalar_t__ RF_3T4R ; 
 scalar_t__ RF_4T4R ; 

__attribute__((used)) static u8 phydm_trans_platform_rf_type(void *dm_void, u8 rf_type)
{
	if (rf_type == RF_1T2R)
		rf_type = PHYDM_RF_1T2R;

	else if (rf_type == RF_2T4R)
		rf_type = PHYDM_RF_2T4R;

	else if (rf_type == RF_2T2R)
		rf_type = PHYDM_RF_2T2R;

	else if (rf_type == RF_1T1R)
		rf_type = PHYDM_RF_1T1R;

	else if (rf_type == RF_2T2R_GREEN)
		rf_type = PHYDM_RF_2T2R_GREEN;

	else if (rf_type == RF_3T3R)
		rf_type = PHYDM_RF_3T3R;

	else if (rf_type == RF_4T4R)
		rf_type = PHYDM_RF_4T4R;

	else if (rf_type == RF_2T3R)
		rf_type = PHYDM_RF_1T2R;

	else if (rf_type == RF_3T4R)
		rf_type = PHYDM_RF_3T4R;

	return rf_type;
}