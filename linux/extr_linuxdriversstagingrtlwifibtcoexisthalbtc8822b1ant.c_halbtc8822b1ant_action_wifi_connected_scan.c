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
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ pan_exist; scalar_t__ a2dp_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; } ;
struct TYPE_3__ {scalar_t__ c2h_bt_inquiry_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_AUTO ; 
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_SCO_BUSY ; 
 int /*<<< orphan*/  BT_8822B_1ANT_PHASE_2G_RUNTIME ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_bt_sco_hid_only_busy (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_action_wifi_multi_port (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_limited_tx (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8822b1ant_set_ant_path (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
halbtc8822b1ant_action_wifi_connected_scan(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	u32 wifi_link_status = 0;
	u32 num_of_wifi_link = 0;
	bool bt_ctrl_agg_buf_size = false;
	u8 agg_buf_size = 5;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], ********** (wifi connect scan) **********\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);

	num_of_wifi_link = wifi_link_status >> 16;

	if (num_of_wifi_link >= 2) {
		halbtc8822b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8822b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);

		if (coex_sta->c2h_bt_inquiry_page) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "############# [BTCoex],  BT Is Inquirying\n");
			halbtc8822b1ant_action_bt_inquiry(btcoexist);
		} else {
			halbtc8822b1ant_action_wifi_multi_port(btcoexist);
		}
		return;
	}

	if (coex_sta->c2h_bt_inquiry_page) {
		halbtc8822b1ant_action_bt_inquiry(btcoexist);
		return;
	} else if (bt_hs_on) {
		halbtc8822b1ant_action_hs(btcoexist);
		return;
	}

	/* tdma and coex table */
	if (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_BUSY) {
		if (bt_link_info->a2dp_exist) {
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						32);
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		} else if (bt_link_info->a2dp_exist &&
			   bt_link_info->pan_exist) {
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						22);
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		} else {
			halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						20);
			halbtc8822b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		}
	} else if ((coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_SCO_BUSY) ||
		   (BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ==
		    coex_dm->bt_status)) {
		halbtc8822b1ant_action_bt_sco_hid_only_busy(btcoexist);
	} else {
		halbtc8822b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);

		halbtc8822b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_AUTO,
					     NORMAL_EXEC,
					     BT_8822B_1ANT_PHASE_2G_RUNTIME);

		halbtc8822b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 6);
	}
}