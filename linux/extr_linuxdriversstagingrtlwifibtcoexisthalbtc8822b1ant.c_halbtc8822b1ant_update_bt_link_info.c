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
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {int bt_link_exist; int sco_exist; int a2dp_exist; int pan_exist; int hid_exist; int sco_only; int a2dp_only; int pan_only; int hid_only; int /*<<< orphan*/  acl_busy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; } ;
struct TYPE_3__ {int bt_info; int bt_link_exist; int pan_exist; int a2dp_exist; int hid_exist; int sco_exist; int /*<<< orphan*/  acl_busy; scalar_t__ num_of_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_TRAFFIC_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_INQ_PAGE ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_MAX ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 scalar_t__ BT_8822B_1ANT_BT_STATUS_SCO_BUSY ; 
 int BT_INFO_8822B_1ANT_B_A2DP ; 
 int BT_INFO_8822B_1ANT_B_ACL_BUSY ; 
 int BT_INFO_8822B_1ANT_B_CONNECTION ; 
 int BT_INFO_8822B_1ANT_B_FTP ; 
 int BT_INFO_8822B_1ANT_B_HID ; 
 int BT_INFO_8822B_1ANT_B_INQ_PAGE ; 
 int BT_INFO_8822B_1ANT_B_SCO_BUSY ; 
 int BT_INFO_8822B_1ANT_B_SCO_ESCO ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8822b1ant_update_bt_link_info(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	bool bt_busy = false;

	coex_sta->num_of_profile = 0;

	/* set link exist status */
	if (!(coex_sta->bt_info & BT_INFO_8822B_1ANT_B_CONNECTION)) {
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	} else { /* connection exists */
		coex_sta->bt_link_exist = true;
		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_FTP) {
			coex_sta->pan_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->pan_exist = false;
		}

		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_A2DP) {
			coex_sta->a2dp_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->a2dp_exist = false;
		}

		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_HID) {
			coex_sta->hid_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->hid_exist = false;
		}

		if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_SCO_ESCO) {
			coex_sta->sco_exist = true;
			coex_sta->num_of_profile++;
		} else {
			coex_sta->sco_exist = false;
		}
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	bt_link_info->bt_link_exist = coex_sta->bt_link_exist;
	bt_link_info->sco_exist = coex_sta->sco_exist;
	bt_link_info->a2dp_exist = coex_sta->a2dp_exist;
	bt_link_info->pan_exist = coex_sta->pan_exist;
	bt_link_info->hid_exist = coex_sta->hid_exist;
	bt_link_info->acl_busy = coex_sta->acl_busy;

	/* work around for HS mode. */
	if (bt_hs_on) {
		bt_link_info->pan_exist = true;
		bt_link_info->bt_link_exist = true;
	}

	/* check if Sco only */
	if (bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->sco_only = true;
	else
		bt_link_info->sco_only = false;

	/* check if A2dp only */
	if (!bt_link_info->sco_exist && bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->a2dp_only = true;
	else
		bt_link_info->a2dp_only = false;

	/* check if Pan only */
	if (!bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->pan_only = true;
	else
		bt_link_info->pan_only = false;

	/* check if Hid only */
	if (!bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && bt_link_info->hid_exist)
		bt_link_info->hid_only = true;
	else
		bt_link_info->hid_only = false;

	if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_INQ_PAGE) {
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_INQ_PAGE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Inq/page!!!\n");
	} else if (!(coex_sta->bt_info & BT_INFO_8822B_1ANT_B_CONNECTION)) {
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_NON_CONNECTED_IDLE;
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n");
	} else if (coex_sta->bt_info == BT_INFO_8822B_1ANT_B_CONNECTION) {
		/* connection exists but no busy */
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_CONNECTED_IDLE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	} else if (((coex_sta->bt_info & BT_INFO_8822B_1ANT_B_SCO_ESCO) ||
		    (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_SCO_BUSY)) &&
		   (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_ACL_BUSY)) {
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT ACL SCO busy!!!\n");
	} else if ((coex_sta->bt_info & BT_INFO_8822B_1ANT_B_SCO_ESCO) ||
		   (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_SCO_BUSY)) {
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_SCO_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	} else if (coex_sta->bt_info & BT_INFO_8822B_1ANT_B_ACL_BUSY) {
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_ACL_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	} else {
		coex_dm->bt_status = BT_8822B_1ANT_BT_STATUS_MAX;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n");
	}

	if ((coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_BUSY) ||
	    (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_SCO_BUSY) ||
	    (coex_dm->bt_status == BT_8822B_1ANT_BT_STATUS_ACL_SCO_BUSY))
		bt_busy = true;
	else
		bt_busy = false;

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);
}