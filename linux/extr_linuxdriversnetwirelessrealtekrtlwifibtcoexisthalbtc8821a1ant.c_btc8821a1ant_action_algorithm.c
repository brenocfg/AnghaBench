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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ a2dp_exist; scalar_t__ pan_exist; scalar_t__ hid_exist; scalar_t__ sco_exist; int /*<<< orphan*/  bt_link_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int BT_8821A_1ANT_COEX_ALGO_A2DP ; 
 int BT_8821A_1ANT_COEX_ALGO_A2DP_PANHS ; 
 int BT_8821A_1ANT_COEX_ALGO_HID ; 
 int BT_8821A_1ANT_COEX_ALGO_HID_A2DP ; 
 int BT_8821A_1ANT_COEX_ALGO_HID_A2DP_PANEDR ; 
 int BT_8821A_1ANT_COEX_ALGO_PANEDR ; 
 int BT_8821A_1ANT_COEX_ALGO_PANEDR_A2DP ; 
 int BT_8821A_1ANT_COEX_ALGO_PANEDR_HID ; 
 int BT_8821A_1ANT_COEX_ALGO_PANHS ; 
 int BT_8821A_1ANT_COEX_ALGO_SCO ; 
 int BT_8821A_1ANT_COEX_ALGO_UNDEFINED ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u8 btc8821a1ant_action_algorithm(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	u8 algorithm = BT_8821A_1ANT_COEX_ALGO_UNDEFINED;
	u8 num_of_diff_profile = 0;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	if (!bt_link_info->bt_link_exist) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], No BT link exists!!!\n");
		return algorithm;
	}

	if (bt_link_info->sco_exist)
		num_of_diff_profile++;
	if (bt_link_info->hid_exist)
		num_of_diff_profile++;
	if (bt_link_info->pan_exist)
		num_of_diff_profile++;
	if (bt_link_info->a2dp_exist)
		num_of_diff_profile++;

	if (num_of_diff_profile == 1) {
		if (bt_link_info->sco_exist) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], BT Profile = SCO only\n");
			algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
		} else {
			if (bt_link_info->hid_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT Profile = HID only\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID;
			} else if (bt_link_info->a2dp_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT Profile = A2DP only\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_A2DP;
			} else if (bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = PAN(HS) only\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANHS;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = PAN(EDR) only\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR;
				}
			}
		}
	} else if (num_of_diff_profile == 2) {
		if (bt_link_info->sco_exist) {
			if (bt_link_info->hid_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT Profile = SCO + HID\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID;
			} else if (bt_link_info->a2dp_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT Profile = SCO + A2DP ==> SCO\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
			} else if (bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				}
			}
		} else {
			if (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT Profile = HID + A2DP\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
			} else if (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = HID + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = HID + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				}
			} else if (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = A2DP + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_A2DP_PANHS;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = A2DP + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_A2DP;
				}
			}
		}
	} else if (num_of_diff_profile == 3) {
		if (bt_link_info->sco_exist) {
			if (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "[BTCoex], BT Profile = SCO + HID + A2DP ==> HID\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID;
			} else if (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + HID + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + HID + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				}
			} else if (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + A2DP + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + A2DP + PAN(EDR) ==> HID\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				}
			}
		} else {
			if (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = HID + A2DP + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = HID + A2DP + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP_PANEDR;
				}
			}
		}
	} else if (num_of_diff_profile >= 3) {
		if (bt_link_info->sco_exist) {
			if (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) {
				if (bt_hs_on) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], Error!!! BT Profile = SCO + HID + A2DP + PAN(HS)\n");

				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], BT Profile = SCO + HID + A2DP + PAN(EDR)==>PAN(EDR)+HID\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				}
			}
		}
	}
	return algorithm;
}