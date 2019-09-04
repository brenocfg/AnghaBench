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
 int ODM_IC_11N_SERIES ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  adc_smp_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_antenna_diversity_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_auto_channel_select_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_cfo_tracking_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_common_info_self_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dig_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dynamic_bb_power_saving_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dynamic_tx_power_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_edca_turbo_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_rate_adaptive_mask_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_rssi_monitor_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_txpowertracking_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_adaptivity_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_beamforming_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_init_ra_info (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_nhm_counter_statistics_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_psd_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_ra_info_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_rf_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_supportability_init (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_txcurrentcalibration (struct phy_dm_struct*) ; 

void odm_dm_init(struct phy_dm_struct *dm)
{
	phydm_supportability_init(dm);
	odm_common_info_self_init(dm);
	odm_dig_init(dm);
	phydm_nhm_counter_statistics_init(dm);
	phydm_adaptivity_init(dm);
	phydm_ra_info_init(dm);
	odm_rate_adaptive_mask_init(dm);
	odm_cfo_tracking_init(dm);
	odm_edca_turbo_init(dm);
	odm_rssi_monitor_init(dm);
	phydm_rf_init(dm);
	odm_txpowertracking_init(dm);

	if (dm->support_ic_type & ODM_RTL8822B)
		phydm_txcurrentcalibration(dm);

	odm_antenna_diversity_init(dm);
	odm_auto_channel_select_init(dm);
	odm_dynamic_tx_power_init(dm);
	phydm_init_ra_info(dm);
	adc_smp_init(dm);

	phydm_beamforming_init(dm);

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		/* 11n series */
		odm_dynamic_bb_power_saving_init(dm);
	}

	phydm_psd_init(dm);
}