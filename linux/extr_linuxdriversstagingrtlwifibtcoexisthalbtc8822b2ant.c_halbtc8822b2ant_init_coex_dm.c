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
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  switch_band_notify_to; scalar_t__ cnt_role_switch; scalar_t__ cnt_page; scalar_t__ cnt_ign_wlan_act; scalar_t__ cnt_setup_link; scalar_t__ cnt_reinit; scalar_t__ cnt_remote_name_req; scalar_t__ pop_event_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_NOT_SWITCH ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_low_penalty_ra (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_query_bt_info (struct btc_coexist*) ; 

__attribute__((used)) static void halbtc8822b2ant_init_coex_dm(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Coex Mechanism Init!!\n");

	halbtc8822b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, false);

	halbtc8822b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);

	/* fw all off */
	halbtc8822b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	halbtc8822b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 0xd8);

	coex_sta->pop_event_cnt = 0;
	coex_sta->cnt_remote_name_req = 0;
	coex_sta->cnt_reinit = 0;
	coex_sta->cnt_setup_link = 0;
	coex_sta->cnt_ign_wlan_act = 0;
	coex_sta->cnt_page = 0;
	coex_sta->cnt_role_switch = 0;
	coex_sta->switch_band_notify_to = BTC_NOT_SWITCH;

	halbtc8822b2ant_query_bt_info(btcoexist);
}