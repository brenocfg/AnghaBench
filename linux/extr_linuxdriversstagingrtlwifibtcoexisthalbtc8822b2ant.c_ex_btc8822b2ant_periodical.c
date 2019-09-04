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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  auto_report_2ant; struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_relink_downcount; int is_setup_link; scalar_t__ specific_pkt_period_cnt; int wifi_is_high_pri_task; scalar_t__ is_set_ps_state_fail; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SCOREBOARD_UNDERTEST ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* coex_sta ; 
 scalar_t__ halbtc8822b2ant_is_wifibt_status_changed (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_monitor_bt_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_monitor_bt_enable_disable (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_monitor_wifi_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_post_state_to_bt (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_read_score_board (struct btc_coexist*,int*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8822b2ant_periodical(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool wifi_busy = false;
	u16 bt_scoreboard_val = 0;
	bool bt_relink_finish = false;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ************* Periodical *************\n");

	if (!btcoexist->auto_report_2ant)
		halbtc8822b2ant_query_bt_info(btcoexist);

	halbtc8822b2ant_monitor_bt_ctr(btcoexist);
	halbtc8822b2ant_monitor_wifi_ctr(btcoexist);
	halbtc8822b2ant_monitor_bt_enable_disable(btcoexist);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	halbtc8822b2ant_read_score_board(btcoexist, &bt_scoreboard_val);

	if (wifi_busy) {
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_UNDERTEST, true);
		/*for bt lps32 clock offset*/
		if (bt_scoreboard_val & BIT(6))
			halbtc8822b2ant_query_bt_info(btcoexist);
	} else {
		halbtc8822b2ant_post_state_to_bt(
			btcoexist, BT_8822B_2ANT_SCOREBOARD_UNDERTEST, false);
	}

	if (coex_sta->bt_relink_downcount != 0) {
		coex_sta->bt_relink_downcount--;

		if (coex_sta->bt_relink_downcount == 0) {
			coex_sta->is_setup_link = false;
			bt_relink_finish = true;
		}
	}

	/* for 4-way, DHCP, EAPOL packet */
	if (coex_sta->specific_pkt_period_cnt > 0) {
		coex_sta->specific_pkt_period_cnt--;

		if ((coex_sta->specific_pkt_period_cnt == 0) &&
		    (coex_sta->wifi_is_high_pri_task))
			coex_sta->wifi_is_high_pri_task = false;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ***************** Hi-Pri Task = %s*****************\n",
			(coex_sta->wifi_is_high_pri_task ? "Yes" : "No"));
	}

	if (halbtc8822b2ant_is_wifibt_status_changed(btcoexist) ||
	    (bt_relink_finish) || (coex_sta->is_set_ps_state_fail))
		halbtc8822b2ant_run_coexist_mechanism(btcoexist);
}