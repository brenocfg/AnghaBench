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
typedef  scalar_t__ u32 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;int /*<<< orphan*/  (* btc_set_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 scalar_t__ BTC_RSSI_HIGH (scalar_t__) ; 
 scalar_t__ BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 scalar_t__ BTC_WIFI_BW_LEGACY ; 
 int /*<<< orphan*/  BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 scalar_t__ btc8821a2ant_bt_rssi_state (struct btc_coexist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a2ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_sw_mechanism1 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_sw_mechanism2 (struct btc_coexist*,int,int,int,int) ; 
 scalar_t__ btc8821a2ant_wifi_rssi_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void btc8821a2ant_action_hid(struct btc_coexist *btcoexist)
{
	u8 wifi_rssi_state, bt_rssi_state;
	u32 wifi_bw;

	wifi_rssi_state = btc8821a2ant_wifi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
		2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	if (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, true);
	else
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);

	if (wifi_bw == BTC_WIFI_BW_LEGACY) {
		/* for HID at 11b/g mode */
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	} else {
		/* for HID quality & wifi performance balance at 11n mode */
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	}

	btc8821a2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 24);

	if (wifi_bw == BTC_WIFI_BW_HT40) {
		/* sw mechanism */
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	} else {
		/* sw mechanism */
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	}
}