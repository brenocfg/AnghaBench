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
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool btc8723b1ant_is_wifi_status_changed(struct btc_coexist *btcoexist)
{
	static bool pre_wifi_busy;
	static bool pre_under_4way, pre_bt_hs_on;
	bool wifi_busy = false, under_4way = false, bt_hs_on = false;
	bool wifi_connected = false;

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
	}

	return false;
}