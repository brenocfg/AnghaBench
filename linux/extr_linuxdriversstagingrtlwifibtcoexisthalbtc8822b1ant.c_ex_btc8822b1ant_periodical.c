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
struct btc_coexist {int /*<<< orphan*/  auto_report_1ant; struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_relink_downcount; int is_setup_link; scalar_t__ specific_pkt_period_cnt; int wifi_is_high_pri_task; scalar_t__ is_set_ps_state_fail; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* coex_sta ; 
 scalar_t__ halbtc8822b1ant_is_wifi_status_changed (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_monitor_bt_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_monitor_bt_enable_disable (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_monitor_wifi_ctr (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_query_bt_info (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_run_coexist_mechanism (struct btc_coexist*) ; 

void ex_btc8822b1ant_periodical(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool bt_relink_finish = false;

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ==========================Periodical===========================\n");

	if (!btcoexist->auto_report_1ant)
		halbtc8822b1ant_query_bt_info(btcoexist);

	halbtc8822b1ant_monitor_bt_ctr(btcoexist);
	halbtc8822b1ant_monitor_wifi_ctr(btcoexist);

	halbtc8822b1ant_monitor_bt_enable_disable(btcoexist);

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

	if (halbtc8822b1ant_is_wifi_status_changed(btcoexist) ||
	    (bt_relink_finish) || (coex_sta->is_set_ps_state_fail))
		halbtc8822b1ant_run_coexist_mechanism(btcoexist);
}