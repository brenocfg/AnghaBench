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
struct btc_bt_link_info {scalar_t__ pan_exist; scalar_t__ a2dp_exist; scalar_t__ hid_exist; scalar_t__ sco_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; } ;
struct TYPE_2__ {int num_of_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8723b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_action_wifi_connected_special_packet(
						struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	/* no special packet process for both WiFi and BT very busy */
	if ((wifi_busy) &&
	    ((bt_link_info->pan_exist) || (coex_sta->num_of_profile >= 2)))
		return;

	halbtc8723b1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	if ((bt_link_info->sco_exist) || (bt_link_info->hid_exist)) {
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	} else if (bt_link_info->a2dp_exist) {
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	} else if (bt_link_info->pan_exist) {
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	} else {
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	}
}