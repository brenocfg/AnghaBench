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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {scalar_t__ manual_control; struct rtl_priv* adapter; } ;
struct TYPE_4__ {int cur_algorithm; int auto_tdma_adjust; int pre_algorithm; } ;
struct TYPE_3__ {scalar_t__ c2h_bt_inquiry_page; scalar_t__ under_ips; } ;

/* Variables and functions */
#define  BT_8192E_2ANT_COEX_ALGO_A2DP 138 
#define  BT_8192E_2ANT_COEX_ALGO_A2DP_PANHS 137 
#define  BT_8192E_2ANT_COEX_ALGO_HID 136 
#define  BT_8192E_2ANT_COEX_ALGO_HID_A2DP 135 
#define  BT_8192E_2ANT_COEX_ALGO_HID_A2DP_PANEDR 134 
#define  BT_8192E_2ANT_COEX_ALGO_PANEDR 133 
#define  BT_8192E_2ANT_COEX_ALGO_PANEDR_A2DP 132 
#define  BT_8192E_2ANT_COEX_ALGO_PANEDR_HID 131 
#define  BT_8192E_2ANT_COEX_ALGO_PANHS 130 
#define  BT_8192E_2ANT_COEX_ALGO_SCO 129 
#define  BT_8192E_2ANT_COEX_ALGO_SCO_PAN 128 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8192e2ant_action_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_a2dp_pan_hs (struct btc_coexist*) ; 
 scalar_t__ btc8192e2ant_action_algorithm (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_hid_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_hid_a2dp_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_pan_edr_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_pan_edr_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_pan_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_sco (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_action_sco_pan (struct btc_coexist*) ; 
 scalar_t__ btc8192e2ant_is_common_action (struct btc_coexist*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 

__attribute__((used)) static void btc8192e2ant_run_coexist_mechanism(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], RunCoexistMechanism()===>\n");

	if (btcoexist->manual_control) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], return for Manual CTRL <===\n");
		return;
	}

	if (coex_sta->under_ips) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], wifi is under IPS !!!\n");
		return;
	}

	algorithm = btc8192e2ant_action_algorithm(btcoexist);
	if (coex_sta->c2h_bt_inquiry_page &&
	    (BT_8192E_2ANT_COEX_ALGO_PANHS != algorithm)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under inquiry/page scan !!\n");
		btc8192e2ant_action_bt_inquiry(btcoexist);
		return;
	}

	coex_dm->cur_algorithm = algorithm;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Algorithm = %d\n", coex_dm->cur_algorithm);

	if (btc8192e2ant_is_common_action(btcoexist)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant common\n");
		coex_dm->auto_tdma_adjust = false;
	} else {
		if (coex_dm->cur_algorithm != coex_dm->pre_algorithm) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex] preAlgorithm=%d, curAlgorithm=%d\n",
				 coex_dm->pre_algorithm,
				 coex_dm->cur_algorithm);
			coex_dm->auto_tdma_adjust = false;
		}
		switch (coex_dm->cur_algorithm) {
		case BT_8192E_2ANT_COEX_ALGO_SCO:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = SCO\n");
			btc8192e2ant_action_sco(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_SCO_PAN:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = SCO+PAN(EDR)\n");
			btc8192e2ant_action_sco_pan(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = HID\n");
			btc8192e2ant_action_hid(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = A2DP\n");
			btc8192e2ant_action_a2dp(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_A2DP_PANHS:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = A2DP+PAN(HS)\n");
			btc8192e2ant_action_a2dp_pan_hs(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_PANEDR:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = PAN(EDR)\n");
			btc8192e2ant_action_pan_edr(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_PANHS:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = HS mode\n");
			btc8192e2ant_action_pan_hs(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_PANEDR_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = PAN+A2DP\n");
			btc8192e2ant_action_pan_edr_a2dp(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_PANEDR_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = PAN(EDR)+HID\n");
			btc8192e2ant_action_pan_edr_hid(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = HID+A2DP+PAN\n");
			btc8192e2ant_action_hid_a2dp_pan_edr(btcoexist);
			break;
		case BT_8192E_2ANT_COEX_ALGO_HID_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = HID+A2DP\n");
			btc8192e2ant_action_hid_a2dp(btcoexist);
			break;
		default:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "Action 2-Ant, algorithm = unknown!!\n");
			/* btc8192e2ant_coex_all_off(btcoexist); */
			break;
		}
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	}
}