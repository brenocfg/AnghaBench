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
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  odm_iq_calibrate (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_txpowertracking_check (struct phy_dm_struct*) ; 

void phydm_rf_watchdog(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	odm_txpowertracking_check(dm);
	if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		odm_iq_calibrate(dm);
}