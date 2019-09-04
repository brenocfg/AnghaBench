#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtl_priv {int dummy; } ;
struct TYPE_2__ {int bt_ctrl_buf_size; int agg_buf_size; int increase_scan_dev_num; } ;
struct btc_coexist {int /*<<< orphan*/  bt_mp_comp; int /*<<< orphan*/  btc_get_bt_afh_map_from_bt; int /*<<< orphan*/  btc_get_ble_scan_para_from_bt; int /*<<< orphan*/  btc_get_ble_scan_type_from_bt; int /*<<< orphan*/  btc_get_ant_det_val_from_bt; int /*<<< orphan*/  btc_phydm_query_phy_counter; int /*<<< orphan*/  btc_phydm_modify_ra_pcr_threshold; int /*<<< orphan*/  btc_get_bt_phydm_version; int /*<<< orphan*/  btc_get_bt_coex_supported_version; int /*<<< orphan*/  btc_get_bt_coex_supported_feature; TYPE_1__ bt_info; int /*<<< orphan*/  btc_get_bt_reg; int /*<<< orphan*/  btc_set_bt_reg; int /*<<< orphan*/  btc_set; int /*<<< orphan*/  btc_get; int /*<<< orphan*/  btc_disp_dbg_msg; int /*<<< orphan*/  btc_fill_h2c; int /*<<< orphan*/  btc_get_rf_reg; int /*<<< orphan*/  btc_set_rf_reg; int /*<<< orphan*/  btc_get_bb_reg; int /*<<< orphan*/  btc_set_bb_reg; int /*<<< orphan*/  btc_write_local_reg_1byte; int /*<<< orphan*/  btc_write_4byte; int /*<<< orphan*/  btc_read_4byte; int /*<<< orphan*/  btc_write_2byte; int /*<<< orphan*/  btc_read_2byte; int /*<<< orphan*/  btc_write_1byte_bitmask; int /*<<< orphan*/  btc_write_1byte; int /*<<< orphan*/  btc_read_1byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc_bitmask_write_1byte ; 
 int /*<<< orphan*/  halbtc_dbg_init () ; 
 int /*<<< orphan*/  halbtc_display_dbg_msg ; 
 int /*<<< orphan*/  halbtc_fill_h2c_cmd ; 
 int /*<<< orphan*/  halbtc_get ; 
 int /*<<< orphan*/  halbtc_get_ant_det_val_from_bt ; 
 int /*<<< orphan*/  halbtc_get_bbreg ; 
 int /*<<< orphan*/  halbtc_get_ble_scan_para_from_bt ; 
 int /*<<< orphan*/  halbtc_get_ble_scan_type_from_bt ; 
 int /*<<< orphan*/  halbtc_get_bt_afh_map_from_bt ; 
 int /*<<< orphan*/  halbtc_get_bt_coex_supported_feature ; 
 int /*<<< orphan*/  halbtc_get_bt_coex_supported_version ; 
 int /*<<< orphan*/  halbtc_get_bt_reg ; 
 int /*<<< orphan*/  halbtc_get_phydm_version ; 
 int /*<<< orphan*/  halbtc_get_rfreg ; 
 int /*<<< orphan*/  halbtc_phydm_modify_ra_pcr_threshold ; 
 int /*<<< orphan*/  halbtc_phydm_query_phy_counter ; 
 int /*<<< orphan*/  halbtc_read_1byte ; 
 int /*<<< orphan*/  halbtc_read_2byte ; 
 int /*<<< orphan*/  halbtc_read_4byte ; 
 int /*<<< orphan*/  halbtc_set ; 
 int /*<<< orphan*/  halbtc_set_bbreg ; 
 int /*<<< orphan*/  halbtc_set_bt_reg ; 
 int /*<<< orphan*/  halbtc_set_rfreg ; 
 int /*<<< orphan*/  halbtc_write_1byte ; 
 int /*<<< orphan*/  halbtc_write_2byte ; 
 int /*<<< orphan*/  halbtc_write_4byte ; 
 int /*<<< orphan*/  halbtc_write_local_reg_1byte ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

bool exhalbtc_initlize_variables(struct rtl_priv *rtlpriv)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	if (!btcoexist)
		return false;

	halbtc_dbg_init();

	btcoexist->btc_read_1byte = halbtc_read_1byte;
	btcoexist->btc_write_1byte = halbtc_write_1byte;
	btcoexist->btc_write_1byte_bitmask = halbtc_bitmask_write_1byte;
	btcoexist->btc_read_2byte = halbtc_read_2byte;
	btcoexist->btc_write_2byte = halbtc_write_2byte;
	btcoexist->btc_read_4byte = halbtc_read_4byte;
	btcoexist->btc_write_4byte = halbtc_write_4byte;
	btcoexist->btc_write_local_reg_1byte = halbtc_write_local_reg_1byte;

	btcoexist->btc_set_bb_reg = halbtc_set_bbreg;
	btcoexist->btc_get_bb_reg = halbtc_get_bbreg;

	btcoexist->btc_set_rf_reg = halbtc_set_rfreg;
	btcoexist->btc_get_rf_reg = halbtc_get_rfreg;

	btcoexist->btc_fill_h2c = halbtc_fill_h2c_cmd;
	btcoexist->btc_disp_dbg_msg = halbtc_display_dbg_msg;

	btcoexist->btc_get = halbtc_get;
	btcoexist->btc_set = halbtc_set;
	btcoexist->btc_set_bt_reg = halbtc_set_bt_reg;
	btcoexist->btc_get_bt_reg = halbtc_get_bt_reg;

	btcoexist->bt_info.bt_ctrl_buf_size = false;
	btcoexist->bt_info.agg_buf_size = 5;

	btcoexist->bt_info.increase_scan_dev_num = false;

	btcoexist->btc_get_bt_coex_supported_feature =
					halbtc_get_bt_coex_supported_feature;
	btcoexist->btc_get_bt_coex_supported_version =
					halbtc_get_bt_coex_supported_version;
	btcoexist->btc_get_bt_phydm_version = halbtc_get_phydm_version;
	btcoexist->btc_phydm_modify_ra_pcr_threshold =
					halbtc_phydm_modify_ra_pcr_threshold;
	btcoexist->btc_phydm_query_phy_counter = halbtc_phydm_query_phy_counter;
	btcoexist->btc_get_ant_det_val_from_bt = halbtc_get_ant_det_val_from_bt;
	btcoexist->btc_get_ble_scan_type_from_bt =
					halbtc_get_ble_scan_type_from_bt;
	btcoexist->btc_get_ble_scan_para_from_bt =
					halbtc_get_ble_scan_para_from_bt;
	btcoexist->btc_get_bt_afh_map_from_bt =
					halbtc_get_bt_afh_map_from_bt;

	init_completion(&btcoexist->bt_mp_comp);

	return true;
}