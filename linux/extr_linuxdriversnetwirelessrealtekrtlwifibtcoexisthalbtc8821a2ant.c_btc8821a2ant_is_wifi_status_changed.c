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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 scalar_t__ BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_LOW ; 
 int /*<<< orphan*/  BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES ; 
 scalar_t__ btc8821a2ant_wifi_rssi_state (struct btc_coexist*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool btc8821a2ant_is_wifi_status_changed(struct btc_coexist *btcoexist)
{
	static bool pre_wifi_busy = true;
	static bool pre_under_4way = true;
	static bool pre_bt_hs_on = true;
	bool wifi_busy = false, under_4way = false, bt_hs_on = false;
	bool wifi_connected = false;
	u8 wifi_rssi_state = BTC_RSSI_STATE_HIGH;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	if (wifi_connected) {
		if (wifi_busy != pre_wifi_busy) {
			pre_wifi_busy = wifi_busy;
			return true;
		}
		if (under_4way != pre_under_4way) {
			pre_under_4way = under_4way;
			return true;
		}
		if (bt_hs_on != pre_bt_hs_on) {
			pre_bt_hs_on = bt_hs_on;
			return true;
		}

		wifi_rssi_state = btc8821a2ant_wifi_rssi_state(btcoexist, 3, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);

		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_LOW))
			return true;
	}

	return false;
}