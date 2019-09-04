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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ pan_exist; scalar_t__ a2dp_exist; scalar_t__ hid_exist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_AP_NUM ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 scalar_t__ BTC_RSSI_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES ; 
 int BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8821a2ant_bt_rssi_state (struct btc_coexist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_dac_swing (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_sw_mechanism1 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_sw_mechanism2 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_wifi_rssi_state (struct btc_coexist*,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool btc8821a2ant_action_wifi_idle_process(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 wifi_rssi_state, wifi_rssi_state1, bt_rssi_state;
	u8 ap_num = 0;

	wifi_rssi_state =
		btc8821a2ant_wifi_rssi_state(btcoexist, 0, 2, 15, 0);
	wifi_rssi_state1 = btc8821a2ant_wifi_rssi_state(btcoexist, 1, 2,
			BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES - 20, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
			2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM, &ap_num);

	/* define the office environment */
	if (BTC_RSSI_HIGH(wifi_rssi_state1) && (coex_sta->hid_exist) &&
	    (coex_sta->a2dp_exist)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi  idle process for BT HID+A2DP exist!!\n");

		btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		/* sw all off */
		btc8821a2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8821a2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

		return true;
	} else if (coex_sta->pan_exist) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi  idle process for BT PAN exist!!\n");

		btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		/* sw all off */
		btc8821a2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8821a2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

		return true;
	}
	btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x18);
	return false;
}