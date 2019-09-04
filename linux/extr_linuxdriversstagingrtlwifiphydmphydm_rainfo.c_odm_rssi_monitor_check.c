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
struct phy_dm_struct {int support_ability; int support_platform; } ;

/* Variables and functions */
#define  ODM_AP 130 
 int ODM_BB_RSSI_MONITOR ; 
#define  ODM_CE 129 
#define  ODM_WIN 128 
 int /*<<< orphan*/  odm_rssi_monitor_check_ap (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_rssi_monitor_check_ce (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_rssi_monitor_check_mp (struct phy_dm_struct*) ; 

void odm_rssi_monitor_check(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (!(dm->support_ability & ODM_BB_RSSI_MONITOR))
		return;

	switch (dm->support_platform) {
	case ODM_WIN:
		odm_rssi_monitor_check_mp(dm);
		break;

	case ODM_CE:
		odm_rssi_monitor_check_ce(dm);
		break;

	case ODM_AP:
		odm_rssi_monitor_check_ap(dm);
		break;

	default:
		break;
	}
}