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
typedef  size_t u8 ;
struct dm_rf_calibration_struct {int default_ofdm_index; size_t* absolute_ofdm_swing_idx; size_t* remnant_ofdm_swing_idx; size_t* bb_swing_idx_ofdm; } ;
struct phy_dm_struct {struct dm_rf_calibration_struct rf_calibrate_info; } ;
typedef  size_t s8 ;
typedef  enum pwrtrack_method { ____Placeholder_pwrtrack_method } pwrtrack_method ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,size_t,size_t,size_t,...) ; 

__attribute__((used)) static bool
get_mix_mode_tx_agc_bb_swing_offset_8822b(void *dm_void,
					  enum pwrtrack_method method,
					  u8 rf_path, u8 tx_power_index_offset)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_rf_calibration_struct *cali_info = &dm->rf_calibrate_info;

	u8 bb_swing_upper_bound = cali_info->default_ofdm_index + 10;
	u8 bb_swing_lower_bound = 0;

	s8 tx_agc_index = 0;
	u8 tx_bb_swing_index = cali_info->default_ofdm_index;

	ODM_RT_TRACE(
		dm, ODM_COMP_TX_PWR_TRACK,
		"Path_%d cali_info->absolute_ofdm_swing_idx[rf_path]=%d, tx_power_index_offset=%d\n",
		rf_path, cali_info->absolute_ofdm_swing_idx[rf_path],
		tx_power_index_offset);

	if (tx_power_index_offset > 0XF)
		tx_power_index_offset = 0XF;

	if (cali_info->absolute_ofdm_swing_idx[rf_path] >= 0 &&
	    cali_info->absolute_ofdm_swing_idx[rf_path] <=
		    tx_power_index_offset) {
		tx_agc_index = cali_info->absolute_ofdm_swing_idx[rf_path];
		tx_bb_swing_index = cali_info->default_ofdm_index;
	} else if (cali_info->absolute_ofdm_swing_idx[rf_path] >
		   tx_power_index_offset) {
		tx_agc_index = tx_power_index_offset;
		cali_info->remnant_ofdm_swing_idx[rf_path] =
			cali_info->absolute_ofdm_swing_idx[rf_path] -
			tx_power_index_offset;
		tx_bb_swing_index = cali_info->default_ofdm_index +
				    cali_info->remnant_ofdm_swing_idx[rf_path];

		if (tx_bb_swing_index > bb_swing_upper_bound)
			tx_bb_swing_index = bb_swing_upper_bound;
	} else {
		tx_agc_index = 0;

		if (cali_info->default_ofdm_index >
		    (cali_info->absolute_ofdm_swing_idx[rf_path] * (-1)))
			tx_bb_swing_index =
				cali_info->default_ofdm_index +
				cali_info->absolute_ofdm_swing_idx[rf_path];
		else
			tx_bb_swing_index = bb_swing_lower_bound;

		if (tx_bb_swing_index < bb_swing_lower_bound)
			tx_bb_swing_index = bb_swing_lower_bound;
	}

	cali_info->absolute_ofdm_swing_idx[rf_path] = tx_agc_index;
	cali_info->bb_swing_idx_ofdm[rf_path] = tx_bb_swing_index;

	ODM_RT_TRACE(
		dm, ODM_COMP_TX_PWR_TRACK,
		"MixMode Offset Path_%d   cali_info->absolute_ofdm_swing_idx[rf_path]=%d   cali_info->bb_swing_idx_ofdm[rf_path]=%d   tx_power_index_offset=%d\n",
		rf_path, cali_info->absolute_ofdm_swing_idx[rf_path],
		cali_info->bb_swing_idx_ofdm[rf_path], tx_power_index_offset);

	return true;
}