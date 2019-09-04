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
typedef  int /*<<< orphan*/  u8 ;
struct btc_bt_link_info {scalar_t__ sco_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void btc8723b1ant_act_bt_sco_hid_only_busy(struct btc_coexist *btcoexist,
						  u8 wifi_status)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_connected = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);

	/* tdma and coex table */
	if (bt_link_info->sco_exist) {
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	} else {
		/* HID */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 6);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	}
}