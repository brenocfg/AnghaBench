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
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  BTC_SET_ACT_DISABLE_LOW_POWER ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_CON_IDLE ; 
 scalar_t__ BT_8821A_2ANT_BT_STATUS_IDLE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int btc8821a2ant_action_wifi_idle_process (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a2ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_sw_mechanism1 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8821a2ant_sw_mechanism2 (struct btc_coexist*,int,int,int,int) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static bool btc8821a2ant_is_common_action(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool common = false, wifi_connected = false, wifi_busy = false;
	bool low_pwr_disable = false;
	bool bt_hs_on = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	if (!wifi_connected) {
		low_pwr_disable = false;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					0x8);

		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			    "[BTCoex], Wifi non-connected idle!!\n");

		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x0);
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		btc8821a2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8821a2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		common = true;
	} else {
		if (BT_8821A_2ANT_BT_STATUS_IDLE ==
		    coex_dm->bt_status) {
			low_pwr_disable = false;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);
			btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC,
						false, false, 0x8);

			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Wifi connected + BT non connected-idle!!\n");

			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
			btc8821a2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);

			btc8821a2ant_power_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
			btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      0xb);
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);

			common = true;
		} else if (BT_8821A_2ANT_BT_STATUS_CON_IDLE ==
			   coex_dm->bt_status) {
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			if (bt_hs_on)
				return false;
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Wifi connected + BT connected-idle!!\n");
			btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC,
						false, false, 0x8);

			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
			btc8821a2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);

			btc8821a2ant_power_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
			btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      0xb);
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
			common = true;
		} else {
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			if (wifi_busy) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], Wifi Connected-Busy + BT Busy!!\n");
				common = false;
			} else {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], Wifi Connected-Idle + BT Busy!!\n");
				common =
				    btc8821a2ant_action_wifi_idle_process(
					     btcoexist);
			}
		}
	}
	return common;
}