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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 int BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT ; 
 int BTC_RSSI_STATE_HIGH ; 
 int BTC_RSSI_STATE_LOW ; 
 int BTC_RSSI_STATE_MEDIUM ; 
 int BTC_RSSI_STATE_STAY_HIGH ; 
 int BTC_RSSI_STATE_STAY_LOW ; 
 int BTC_RSSI_STATE_STAY_MEDIUM ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u8 halbtc8822b2ant_wifi_rssi_state(struct btc_coexist *btcoexist,
					  u8 *pprewifi_rssi_state, u8 level_num,
					  u8 rssi_thresh, u8 rssi_thresh1)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	s32 wifi_rssi = 0;
	u8 wifi_rssi_state = *pprewifi_rssi_state;

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);

	if (level_num == 2) {
		if ((*pprewifi_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (*pprewifi_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		} else {
			if (wifi_rssi < rssi_thresh)
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		}
	} else if (level_num == 3) {
		if (rssi_thresh > rssi_thresh1) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], wifi RSSI thresh error!!\n");
			return *pprewifi_rssi_state;
		}

		if ((*pprewifi_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (*pprewifi_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		} else if ((*pprewifi_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
			   (*pprewifi_rssi_state ==
			    BTC_RSSI_STATE_STAY_MEDIUM)) {
			if (wifi_rssi >= (rssi_thresh1 +
					  BTC_RSSI_COEX_THRESH_TOL_8822B_2ANT))
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
			else if (wifi_rssi < rssi_thresh)
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
		} else {
			if (wifi_rssi < rssi_thresh1)
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
			else
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		}
	}

	*pprewifi_rssi_state = wifi_rssi_state;

	return wifi_rssi_state;
}