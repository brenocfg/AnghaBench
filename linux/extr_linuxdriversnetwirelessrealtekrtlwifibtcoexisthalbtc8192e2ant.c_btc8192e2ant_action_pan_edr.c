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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 scalar_t__ BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_LOW ; 
 scalar_t__ BTC_RSSI_STATE_MEDIUM ; 
 scalar_t__ BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_LOW ; 
 scalar_t__ BTC_RSSI_STATE_STAY_MEDIUM ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 scalar_t__ btc8192e2ant_bt_rssi_state (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_sw_mechanism1 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_sw_mechanism2 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_switch_ss_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ btc8192e2ant_wifi_rssi_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void btc8192e2ant_action_pan_edr(struct btc_coexist *btcoexist)
{
	u8 wifi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wifi_bw;

	wifi_rssi_state = btc8192e2ant_wifi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_switch_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	if ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
	} else if ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) {
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 1);
	} else if ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 1);
	}

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);
	if (BTC_WIFI_BW_HT40 == wifi_bw) {
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	} else {
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	}
}