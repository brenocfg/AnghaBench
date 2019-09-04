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
typedef  scalar_t__ u32 ;
struct btc_bt_link_info {scalar_t__ sco_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; } ;
struct TYPE_2__ {scalar_t__ is_bt_multi_link; scalar_t__ is_hid_low_pri_tx_overhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
halbtc8822b1ant_action_bt_sco_hid_only_busy(struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_connected = false, wifi_busy = false;
	u32 wifi_bw = 1;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	if (bt_link_info->sco_exist) {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	} else {
		if (coex_sta->is_hid_low_pri_tx_overhead) {
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						18);
		} else if (wifi_bw == 0) { /* if 11bg mode */

			if (coex_sta->is_bt_multi_link) {
				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 11);
				halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 11);
			} else {
				halbtc8822b1ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 6);
				halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 11);
			}
		} else {
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 6);
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						11);
		}
	}
}