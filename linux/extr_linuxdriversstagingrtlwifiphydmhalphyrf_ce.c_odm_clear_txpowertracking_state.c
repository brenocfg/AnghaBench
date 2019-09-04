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
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int /*<<< orphan*/  eeprom_thermalmeter; } ;
struct dm_rf_calibration_struct {int modify_tx_agc_flag_path_a; int modify_tx_agc_flag_path_b; int modify_tx_agc_flag_path_c; int modify_tx_agc_flag_path_d; scalar_t__ modify_tx_agc_value_ofdm; scalar_t__ modify_tx_agc_value_cck; int /*<<< orphan*/  thermal_value; scalar_t__ remnant_cck_swing_idx; scalar_t__* kfree_offset; scalar_t__* remnant_ofdm_swing_idx; scalar_t__* absolute_ofdm_swing_idx; scalar_t__* delta_power_index_last; scalar_t__* delta_power_index; scalar_t__* power_index_offset; int /*<<< orphan*/  default_ofdm_index; int /*<<< orphan*/ * OFDM_index; int /*<<< orphan*/ * bb_swing_idx_ofdm; int /*<<< orphan*/ * bb_swing_idx_ofdm_base; scalar_t__ CCK_index; int /*<<< orphan*/  default_cck_index; int /*<<< orphan*/  bb_swing_idx_cck; int /*<<< orphan*/  bb_swing_idx_cck_base; } ;
struct phy_dm_struct {struct dm_rf_calibration_struct rf_calibrate_info; scalar_t__ adapter; } ;

/* Variables and functions */
 size_t MAX_RF_PATH ; 
 size_t ODM_RF_PATH_A ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 

void odm_clear_txpowertracking_state(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
	struct rtl_efuse *rtlefu = rtl_efuse(rtlpriv);
	u8 p = 0;
	struct dm_rf_calibration_struct *cali_info = &dm->rf_calibrate_info;

	cali_info->bb_swing_idx_cck_base = cali_info->default_cck_index;
	cali_info->bb_swing_idx_cck = cali_info->default_cck_index;
	dm->rf_calibrate_info.CCK_index = 0;

	for (p = ODM_RF_PATH_A; p < MAX_RF_PATH; ++p) {
		cali_info->bb_swing_idx_ofdm_base[p] =
			cali_info->default_ofdm_index;
		cali_info->bb_swing_idx_ofdm[p] = cali_info->default_ofdm_index;
		cali_info->OFDM_index[p] = cali_info->default_ofdm_index;

		cali_info->power_index_offset[p] = 0;
		cali_info->delta_power_index[p] = 0;
		cali_info->delta_power_index_last[p] = 0;

		cali_info->absolute_ofdm_swing_idx[p] =
			0; /* Initial Mix mode power tracking*/
		cali_info->remnant_ofdm_swing_idx[p] = 0;
		cali_info->kfree_offset[p] = 0;
	}

	cali_info->modify_tx_agc_flag_path_a =
		false; /*Initial at Modify Tx Scaling mode*/
	cali_info->modify_tx_agc_flag_path_b =
		false; /*Initial at Modify Tx Scaling mode*/
	cali_info->modify_tx_agc_flag_path_c =
		false; /*Initial at Modify Tx Scaling mode*/
	cali_info->modify_tx_agc_flag_path_d =
		false; /*Initial at Modify Tx Scaling mode*/
	cali_info->remnant_cck_swing_idx = 0;
	cali_info->thermal_value = rtlefu->eeprom_thermalmeter;

	cali_info->modify_tx_agc_value_cck = 0; /* modify by Mingzhi.Guo */
	cali_info->modify_tx_agc_value_ofdm = 0; /* modify by Mingzhi.Guo */
}