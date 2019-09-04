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
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int /*<<< orphan*/  eeprom_thermalmeter; } ;
struct dm_rf_calibration_struct {int is_txpowertracking; int is_txpowertracking_init; int txpowertrack_control; int default_bb_swing_index_flag; int default_ofdm_index; int default_cck_index; int bb_swing_idx_cck_base; int CCK_index; int* bb_swing_idx_ofdm_base; int* OFDM_index; scalar_t__ modify_tx_agc_value_cck; scalar_t__ modify_tx_agc_value_ofdm; scalar_t__* power_index_offset; scalar_t__* delta_power_index_last; scalar_t__* delta_power_index; int /*<<< orphan*/  thermal_value_lck; int /*<<< orphan*/  thermal_value_iqk; int /*<<< orphan*/  thermal_value; scalar_t__ tx_powercount; } ;
struct phy_dm_struct {scalar_t__ support_ic_type; int /*<<< orphan*/  mp_mode; scalar_t__ adapter; struct dm_rf_calibration_struct rf_calibrate_info; } ;

/* Variables and functions */
 int MAX_RF_PATH ; 
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int ODM_RF_PATH_A ; 
 scalar_t__ ODM_RTL8188E ; 
 scalar_t__ ODM_RTL8188F ; 
 scalar_t__ ODM_RTL8192E ; 
 scalar_t__ ODM_RTL8703B ; 
 scalar_t__ ODM_RTL8710B ; 
 scalar_t__ ODM_RTL8723B ; 
 scalar_t__ ODM_RTL8723D ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int) ; 
 int OFDM_TABLE_SIZE ; 
 int TXSCALE_TABLE_SIZE ; 
 int get_swing_index (struct phy_dm_struct*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 

void odm_txpowertracking_thermal_meter_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 default_swing_index = get_swing_index(dm);
	u8 p = 0;
	struct dm_rf_calibration_struct *cali_info = &dm->rf_calibrate_info;
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
	struct rtl_efuse *rtlefu = rtl_efuse(rtlpriv);

	cali_info->is_txpowertracking = true;
	cali_info->tx_powercount = 0;
	cali_info->is_txpowertracking_init = false;

	if (!dm->mp_mode)
		cali_info->txpowertrack_control = true;
	else
		cali_info->txpowertrack_control = false;

	if (!dm->mp_mode)
		cali_info->txpowertrack_control = true;

	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION, "dm txpowertrack_control = %d\n",
		     cali_info->txpowertrack_control);

	/* dm->rf_calibrate_info.txpowertrack_control = true; */
	cali_info->thermal_value = rtlefu->eeprom_thermalmeter;
	cali_info->thermal_value_iqk = rtlefu->eeprom_thermalmeter;
	cali_info->thermal_value_lck = rtlefu->eeprom_thermalmeter;

	if (!cali_info->default_bb_swing_index_flag) {
		/*The index of "0 dB" in SwingTable.*/
		if (dm->support_ic_type == ODM_RTL8188E ||
		    dm->support_ic_type == ODM_RTL8723B ||
		    dm->support_ic_type == ODM_RTL8192E ||
		    dm->support_ic_type == ODM_RTL8703B) {
			cali_info->default_ofdm_index =
				(default_swing_index >= OFDM_TABLE_SIZE) ?
					30 :
					default_swing_index;
			cali_info->default_cck_index = 20;
		} else if (dm->support_ic_type ==
			   ODM_RTL8188F) { /*add by Mingzhi.Guo  2015-03-23*/
			cali_info->default_ofdm_index = 28; /*OFDM: -1dB*/
			cali_info->default_cck_index = 20; /*CCK:-6dB*/
		} else if (dm->support_ic_type ==
			   ODM_RTL8723D) { /*add by zhaohe  2015-10-27*/
			cali_info->default_ofdm_index = 28; /*OFDM: -1dB*/
			cali_info->default_cck_index = 28; /*CCK:   -6dB*/
		} else if (dm->support_ic_type ==
			   ODM_RTL8710B) { /* JJ ADD 20161014 */
			cali_info->default_ofdm_index = 28; /*OFDM: -1dB*/
			cali_info->default_cck_index = 28; /*CCK:   -6dB*/
		} else {
			cali_info->default_ofdm_index =
				(default_swing_index >= TXSCALE_TABLE_SIZE) ?
					24 :
					default_swing_index;
			cali_info->default_cck_index = 24;
		}
		cali_info->default_bb_swing_index_flag = true;
	}

	cali_info->bb_swing_idx_cck_base = cali_info->default_cck_index;
	cali_info->CCK_index = cali_info->default_cck_index;

	for (p = ODM_RF_PATH_A; p < MAX_RF_PATH; ++p) {
		cali_info->bb_swing_idx_ofdm_base[p] =
			cali_info->default_ofdm_index;
		cali_info->OFDM_index[p] = cali_info->default_ofdm_index;
		cali_info->delta_power_index[p] = 0;
		cali_info->delta_power_index_last[p] = 0;
		cali_info->power_index_offset[p] = 0;
	}
	cali_info->modify_tx_agc_value_ofdm = 0;
	cali_info->modify_tx_agc_value_cck = 0;
}