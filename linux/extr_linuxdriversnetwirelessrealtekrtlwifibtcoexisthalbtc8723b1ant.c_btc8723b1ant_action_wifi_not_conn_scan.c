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
struct btc_bt_link_info {scalar_t__ a2dp_exist; } ;
struct btc_coexist {struct btc_bt_link_info bt_link_info; } ;
struct TYPE_2__ {scalar_t__ bt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_PTA ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_SCO_BUSY ; 
 int /*<<< orphan*/  BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8723b1ant_act_bt_sco_hid_only_busy (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  halbtc8723b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
btc8723b1ant_action_wifi_not_conn_scan(struct btc_coexist *btcoexist)
{
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	halbtc8723b1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	if (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) {
		if (bt_link_info->a2dp_exist) {
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 32);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		} else if (bt_link_info->a2dp_exist) {
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 22);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		} else {
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 20);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		}
	} else if (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
		   coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY){
		btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	} else {
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	}
}