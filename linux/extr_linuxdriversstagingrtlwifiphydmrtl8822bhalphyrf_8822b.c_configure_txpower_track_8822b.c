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
struct txpwrtrack_cfg {int /*<<< orphan*/  get_delta_swing_table; int /*<<< orphan*/  phy_lc_calibrate; int /*<<< orphan*/  do_iqk; int /*<<< orphan*/  odm_tx_pwr_track_set_pwr; int /*<<< orphan*/  thermal_reg_addr; int /*<<< orphan*/  rf_path_count; int /*<<< orphan*/  average_thermal_num; int /*<<< orphan*/  threshold_dpk; int /*<<< orphan*/  threshold_iqk; void* swing_table_size_ofdm; void* swing_table_size_cck; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVG_THERMAL_NUM_8822B ; 
 int /*<<< orphan*/  DPK_THRESHOLD ; 
 int /*<<< orphan*/  IQK_THRESHOLD ; 
 int /*<<< orphan*/  MAX_PATH_NUM_8822B ; 
 int /*<<< orphan*/  RF_T_METER_8822B ; 
 void* TXSCALE_TABLE_SIZE ; 
 int /*<<< orphan*/  do_iqk_8822b ; 
 int /*<<< orphan*/  get_delta_swing_table_8822b ; 
 int /*<<< orphan*/  odm_tx_pwr_track_set_pwr8822b ; 
 int /*<<< orphan*/  phy_lc_calibrate_8822b ; 

void configure_txpower_track_8822b(struct txpwrtrack_cfg *config)
{
	config->swing_table_size_cck = TXSCALE_TABLE_SIZE;
	config->swing_table_size_ofdm = TXSCALE_TABLE_SIZE;
	config->threshold_iqk = IQK_THRESHOLD;
	config->threshold_dpk = DPK_THRESHOLD;
	config->average_thermal_num = AVG_THERMAL_NUM_8822B;
	config->rf_path_count = MAX_PATH_NUM_8822B;
	config->thermal_reg_addr = RF_T_METER_8822B;

	config->odm_tx_pwr_track_set_pwr = odm_tx_pwr_track_set_pwr8822b;
	config->do_iqk = do_iqk_8822b;
	config->phy_lc_calibrate = phy_lc_calibrate_8822b;

	config->get_delta_swing_table = get_delta_swing_table_8822b;
}