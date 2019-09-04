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
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_algorithm; int pre_algorithm; } ;

/* Variables and functions */
#define  BT_8822B_2ANT_COEX_ALGO_A2DP 138 
#define  BT_8822B_2ANT_COEX_ALGO_A2DPSINK 137 
#define  BT_8822B_2ANT_COEX_ALGO_A2DP_PANHS 136 
#define  BT_8822B_2ANT_COEX_ALGO_HID 135 
#define  BT_8822B_2ANT_COEX_ALGO_HID_A2DP 134 
#define  BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR 133 
#define  BT_8822B_2ANT_COEX_ALGO_NOPROFILEBUSY 132 
#define  BT_8822B_2ANT_COEX_ALGO_PANEDR 131 
#define  BT_8822B_2ANT_COEX_ALGO_PANEDR_A2DP 130 
#define  BT_8822B_2ANT_COEX_ALGO_PANEDR_HID 129 
#define  BT_8822B_2ANT_COEX_ALGO_SCO 128 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_a2dp_pan_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_a2dpsink (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_bt_idle (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_coex_all_off (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_hid_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_hid_a2dp_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_pan_edr_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_pan_edr_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  halbtc8822b2ant_action_sco (struct btc_coexist*) ; 

__attribute__((used)) static void halbtc8822b2ant_action_wifi_connected(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	switch (coex_dm->cur_algorithm) {
	case BT_8822B_2ANT_COEX_ALGO_SCO:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = SCO.\n");
		halbtc8822b2ant_action_sco(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_HID:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = HID.\n");
		halbtc8822b2ant_action_hid(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_A2DP:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = A2DP.\n");
		halbtc8822b2ant_action_a2dp(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_A2DPSINK:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = A2DP Sink.\n");
		halbtc8822b2ant_action_a2dpsink(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_A2DP_PANHS:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = A2DP+PAN(HS).\n");
		halbtc8822b2ant_action_a2dp_pan_hs(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_PANEDR:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = PAN(EDR).\n");
		halbtc8822b2ant_action_pan_edr(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_PANEDR_A2DP:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = PAN+A2DP.\n");
		halbtc8822b2ant_action_pan_edr_a2dp(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_PANEDR_HID:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = PAN(EDR)+HID.\n");
		halbtc8822b2ant_action_pan_edr_hid(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = HID+A2DP+PAN.\n");
		halbtc8822b2ant_action_hid_a2dp_pan_edr(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_HID_A2DP:
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant, algorithm = HID+A2DP.\n");
		halbtc8822b2ant_action_hid_a2dp(btcoexist);
		break;
	case BT_8822B_2ANT_COEX_ALGO_NOPROFILEBUSY:
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Action 2-Ant, algorithm = No-Profile busy.\n");
		halbtc8822b2ant_action_bt_idle(btcoexist);
		break;
	default:
		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Action 2-Ant, algorithm = coexist All Off!!\n");
		halbtc8822b2ant_action_coex_all_off(btcoexist);
		break;
	}

	coex_dm->pre_algorithm = coex_dm->cur_algorithm;
}