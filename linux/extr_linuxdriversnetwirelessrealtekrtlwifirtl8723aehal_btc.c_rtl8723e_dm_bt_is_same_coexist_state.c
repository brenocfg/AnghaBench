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
struct TYPE_2__ {scalar_t__ previous_state; scalar_t__ cstate; scalar_t__ previous_state_h; scalar_t__ cstate_h; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool rtl8723e_dm_bt_is_same_coexist_state(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if ((rtlpriv->btcoexist.previous_state ==
	     rtlpriv->btcoexist.cstate) &&
	    (rtlpriv->btcoexist.previous_state_h ==
	     rtlpriv->btcoexist.cstate_h)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			 "[DM][BT], Coexist state do not chang!!\n");
		return true;
	} else {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			 "[DM][BT], Coexist state changed!!\n");
		return false;
	}
}