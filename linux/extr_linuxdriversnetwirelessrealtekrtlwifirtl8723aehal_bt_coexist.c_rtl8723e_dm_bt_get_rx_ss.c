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
struct TYPE_4__ {long entry_min_undec_sm_pwdb; } ;
struct TYPE_3__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_2__ dm; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 long GET_UNDECORATED_AVERAGE_RSSI (struct rtl_priv*) ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,long) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

long rtl8723e_dm_bt_get_rx_ss(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	long undecoratedsmoothed_pwdb = 0;

	if (rtlpriv->mac80211.link_state >= MAC80211_LINKED) {
		undecoratedsmoothed_pwdb =
			GET_UNDECORATED_AVERAGE_RSSI(rtlpriv);
	} else {
		undecoratedsmoothed_pwdb
			= rtlpriv->dm.entry_min_undec_sm_pwdb;
	}
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		 "rtl8723e_dm_bt_get_rx_ss() = %ld\n",
		 undecoratedsmoothed_pwdb);

	return undecoratedsmoothed_pwdb;
}