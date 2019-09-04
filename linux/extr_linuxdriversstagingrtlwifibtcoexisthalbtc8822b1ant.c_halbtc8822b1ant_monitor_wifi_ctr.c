#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct btc_coexist {int (* btc_phydm_query_phy_counter ) (struct btc_coexist*,char*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;
typedef  int s32 ;
struct TYPE_4__ {scalar_t__ bt_status; } ;
struct TYPE_3__ {int crc_ok_cck; int crc_ok_11g; int crc_ok_11n; int crc_ok_11n_vht; int crc_err_cck; int crc_err_11g; int crc_err_11n; int crc_err_11n_vht; int wl_noisy_level; int pre_ccklock; int cck_lock; int cck_ever_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_B_MODE ; 
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_SCO_BUSY ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int stub10 (struct btc_coexist*,char*) ; 
 int stub11 (struct btc_coexist*,char*) ; 
 int stub12 (struct btc_coexist*,char*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int stub5 (struct btc_coexist*,char*) ; 
 int stub6 (struct btc_coexist*,char*) ; 
 int stub7 (struct btc_coexist*,char*) ; 
 int stub8 (struct btc_coexist*,char*) ; 
 int stub9 (struct btc_coexist*,char*) ; 

__attribute__((used)) static void halbtc8822b1ant_monitor_wifi_ctr(struct btc_coexist *btcoexist)
{
	s32 wifi_rssi = 0;
	bool wifi_busy = false, wifi_under_b_mode = false, wifi_scan = false;
	static u8 cck_lock_counter, wl_noisy_count0, wl_noisy_count1 = 3,
						     wl_noisy_count2;
	u32 total_cnt, cck_cnt;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
			   &wifi_under_b_mode);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &wifi_scan);

	coex_sta->crc_ok_cck = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_OK_CCK");
	coex_sta->crc_ok_11g = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_OK_LEGACY");
	coex_sta->crc_ok_11n = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_OK_HT");
	coex_sta->crc_ok_11n_vht = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_OK_VHT");

	coex_sta->crc_err_cck = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_ERROR_CCK");
	coex_sta->crc_err_11g = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_ERROR_LEGACY");
	coex_sta->crc_err_11n = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_ERROR_HT");
	coex_sta->crc_err_11n_vht = btcoexist->btc_phydm_query_phy_counter(
		btcoexist, "PHYDM_INFO_CRC32_ERROR_VHT");

	cck_cnt = coex_sta->crc_ok_cck + coex_sta->crc_err_cck;

	if (cck_cnt > 250) {
		if (wl_noisy_count2 < 3)
			wl_noisy_count2++;

		if (wl_noisy_count2 == 3) {
			wl_noisy_count0 = 0;
			wl_noisy_count1 = 0;
		}

	} else if (cck_cnt < 50) {
		if (wl_noisy_count0 < 3)
			wl_noisy_count0++;

		if (wl_noisy_count0 == 3) {
			wl_noisy_count1 = 0;
			wl_noisy_count2 = 0;
		}

	} else {
		if (wl_noisy_count1 < 3)
			wl_noisy_count1++;

		if (wl_noisy_count1 == 3) {
			wl_noisy_count0 = 0;
			wl_noisy_count2 = 0;
		}
	}

	if (wl_noisy_count2 == 3)
		coex_sta->wl_noisy_level = 2;
	else if (wl_noisy_count1 == 3)
		coex_sta->wl_noisy_level = 1;
	else
		coex_sta->wl_noisy_level = 0;

	if ((wifi_busy) && (wifi_rssi >= 30) && (!wifi_under_b_mode)) {
		total_cnt = coex_sta->crc_ok_cck + coex_sta->crc_ok_11g +
			    coex_sta->crc_ok_11n + coex_sta->crc_ok_11n_vht;

		if ((coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_BUSY) ||
		    (coex_dm->bt_status ==
		     BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY) ||
		    (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_SCO_BUSY)) {
			if (coex_sta->crc_ok_cck >
			    (total_cnt - coex_sta->crc_ok_cck)) {
				if (cck_lock_counter < 3)
					cck_lock_counter++;
			} else {
				if (cck_lock_counter > 0)
					cck_lock_counter--;
			}

		} else {
			if (cck_lock_counter > 0)
				cck_lock_counter--;
		}
	} else {
		if (cck_lock_counter > 0)
			cck_lock_counter--;
	}

	if (!coex_sta->pre_ccklock) {
		if (cck_lock_counter >= 3)
			coex_sta->cck_lock = true;
		else
			coex_sta->cck_lock = false;
	} else {
		if (cck_lock_counter == 0)
			coex_sta->cck_lock = false;
		else
			coex_sta->cck_lock = true;
	}

	if (coex_sta->cck_lock)
		coex_sta->cck_ever_lock = true;

	coex_sta->pre_ccklock = coex_sta->cck_lock;
}