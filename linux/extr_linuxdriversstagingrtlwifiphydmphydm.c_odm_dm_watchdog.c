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
struct phy_dm_struct {scalar_t__* is_power_saving; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_COMMON ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_DIG (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_antenna_diversity (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_cck_packet_detection_thresh (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_cfo_tracking (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_common_info_self_reset (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_common_info_self_update (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dig_by_rssi_lps (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dtc (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dynamic_tx_power (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_edca_turbo_check (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_false_alarm_counter_statistics (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_hw_setting (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_rssi_monitor_check (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_update_power_training_state (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_adaptivity (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_basic_dbg_message (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_beamforming_watchdog (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_check_adaptivity (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_noisy_detection (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_ra_info_watchdog (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_rf_watchdog (struct phy_dm_struct*) ; 

void odm_dm_watchdog(struct phy_dm_struct *dm)
{
	odm_common_info_self_update(dm);
	phydm_basic_dbg_message(dm);
	odm_hw_setting(dm);

	odm_false_alarm_counter_statistics(dm);
	phydm_noisy_detection(dm);

	odm_rssi_monitor_check(dm);

	if (*dm->is_power_saving) {
		odm_dig_by_rssi_lps(dm);
		phydm_adaptivity(dm);
		odm_antenna_diversity(
			dm); /*enable AntDiv in PS mode, request from SD4 Jeff*/
		ODM_RT_TRACE(dm, ODM_COMP_COMMON,
			     "DMWatchdog in power saving mode\n");
		return;
	}

	phydm_check_adaptivity(dm);
	odm_update_power_training_state(dm);
	odm_DIG(dm);
	phydm_adaptivity(dm);
	odm_cck_packet_detection_thresh(dm);

	phydm_ra_info_watchdog(dm);
	odm_edca_turbo_check(dm);
	odm_cfo_tracking(dm);
	odm_dynamic_tx_power(dm);
	odm_antenna_diversity(dm);

	phydm_beamforming_watchdog(dm);

	phydm_rf_watchdog(dm);

	odm_dtc(dm);

	odm_common_info_self_reset(dm);
}