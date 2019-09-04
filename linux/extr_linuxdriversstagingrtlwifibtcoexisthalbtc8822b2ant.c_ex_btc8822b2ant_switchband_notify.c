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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {scalar_t__ stop_coex_dm; scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ switch_band_notify_to; } ;

/* Variables and functions */
 scalar_t__ BTC_NOT_SWITCH ; 
 int /*<<< orphan*/  BTC_SCAN_START_2G ; 
 scalar_t__ BTC_SWITCH_TO_24G_NOFORSCAN ; 
 scalar_t__ BTC_SWITCH_TO_5G ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  ex_btc8822b2ant_scan_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_wifi_under5g (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_run_coexist_mechanism (struct btc_coexist*) ; 

void ex_btc8822b2ant_switchband_notify(struct btc_coexist *btcoexist, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	if (btcoexist->manual_control || btcoexist->stop_coex_dm)
		return;
	coex_sta->switch_band_notify_to = type;

	if (type == BTC_SWITCH_TO_5G) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], switchband_notify ---  switch to 5G\n");

		halbtc8822b2ant_action_wifi_under5g(btcoexist);

	} else if (type == BTC_SWITCH_TO_24G_NOFORSCAN) {
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ********** switchband_notify BTC_SWITCH_TO_2G (no for scan)\n");

		halbtc8822b2ant_run_coexist_mechanism(btcoexist);

	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], switchband_notify ---  switch to 2G\n");

		ex_btc8822b2ant_scan_notify(btcoexist, BTC_SCAN_START_2G);
	}
	coex_sta->switch_band_notify_to = BTC_NOT_SWITCH;
}