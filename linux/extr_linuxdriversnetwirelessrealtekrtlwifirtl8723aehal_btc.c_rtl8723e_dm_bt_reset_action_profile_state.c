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
struct TYPE_2__ {int cstate; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BT_COEX_STATE_BTINFO_B_FTP_A2DP ; 
 int BT_COEX_STATE_BTINFO_B_HID_SCOESCO ; 
 int BT_COEX_STATE_BTINFO_COMMON ; 
 int BT_COEX_STATE_PROFILE_A2DP ; 
 int BT_COEX_STATE_PROFILE_HID ; 
 int BT_COEX_STATE_PROFILE_PAN ; 
 int BT_COEX_STATE_PROFILE_SCO ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_bt_reset_action_profile_state(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.cstate &= ~
		(BT_COEX_STATE_PROFILE_HID | BT_COEX_STATE_PROFILE_A2DP|
		BT_COEX_STATE_PROFILE_PAN | BT_COEX_STATE_PROFILE_SCO);

	rtlpriv->btcoexist.cstate &= ~
		(BT_COEX_STATE_BTINFO_COMMON |
		BT_COEX_STATE_BTINFO_B_HID_SCOESCO|
		BT_COEX_STATE_BTINFO_B_FTP_A2DP);
}