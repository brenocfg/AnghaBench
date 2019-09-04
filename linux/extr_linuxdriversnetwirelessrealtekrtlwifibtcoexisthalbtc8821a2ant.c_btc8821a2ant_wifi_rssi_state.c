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
typedef  size_t u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,long*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {size_t* pre_wifi_rssi_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 size_t BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT ; 
 size_t BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_LOW ; 
 scalar_t__ BTC_RSSI_STATE_MEDIUM ; 
 size_t BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_LOW ; 
 scalar_t__ BTC_RSSI_STATE_STAY_MEDIUM ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,long*) ; 

__attribute__((used)) static u8 btc8821a2ant_wifi_rssi_state(struct btc_coexist *btcoexist,
				       u8 index, u8 level_num,
				       u8 rssi_thresh, u8 rssi_thresh1)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	long wifi_rssi = 0;
	u8 wifi_rssi_state = coex_sta->pre_wifi_rssi_state[index];

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);

	if (level_num == 2) {
		if ((coex_sta->pre_wifi_rssi_state[index] ==
		     BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wifi_rssi_state[index] ==
		     BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >=
			    (rssi_thresh+BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) {
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state switch to High\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state stay at Low\n");
			}
		} else {
			if (wifi_rssi < rssi_thresh) {
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state switch to Low\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state stay at High\n");
			}
		}
	} else if (level_num == 3) {
		if (rssi_thresh > rssi_thresh1) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], wifi RSSI thresh error!!\n");
			return coex_sta->pre_wifi_rssi_state[index];
		}

		if ((coex_sta->pre_wifi_rssi_state[index] ==
		    BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wifi_rssi_state[index] ==
		     BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >=
			    (rssi_thresh +
			     BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) {
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state switch to Medium\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state stay at Low\n");
			}
		} else if ((coex_sta->pre_wifi_rssi_state[index] ==
			   BTC_RSSI_STATE_MEDIUM) ||
			   (coex_sta->pre_wifi_rssi_state[index] ==
			    BTC_RSSI_STATE_STAY_MEDIUM)) {
			if (wifi_rssi >= (rssi_thresh1 +
			    BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) {
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state switch to High\n");
			} else if (wifi_rssi < rssi_thresh) {
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state switch to Low\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state stay at Medium\n");
			}
		} else {
			if (wifi_rssi < rssi_thresh1) {
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state switch to Medium\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], wifi RSSI state stay at High\n");
			}
		}
	}
	coex_sta->pre_wifi_rssi_state[index] = wifi_rssi_state;

	return wifi_rssi_state;
}