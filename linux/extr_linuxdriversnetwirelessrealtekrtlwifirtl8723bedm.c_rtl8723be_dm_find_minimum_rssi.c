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
struct TYPE_2__ {scalar_t__ entry_min_undec_sm_pwdb; scalar_t__ undec_sm_pwdb; } ;
struct dig_t {scalar_t__ min_undec_pwdb_for_dm; } ;
struct rtl_priv {TYPE_1__ dm; struct dig_t dm_digtable; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BB_POWERSAVING ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723be_dm_find_minimum_rssi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *rtl_dm_dig = &rtlpriv->dm_digtable;
	struct rtl_mac *mac = rtl_mac(rtlpriv);

	/* Determine the minimum RSSI  */
	if ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) {
		rtl_dm_dig->min_undec_pwdb_for_dm = 0;
		RT_TRACE(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			 "Not connected to any\n");
	}
	if (mac->link_state >= MAC80211_LINKED) {
		if (mac->opmode == NL80211_IFTYPE_AP ||
		    mac->opmode == NL80211_IFTYPE_ADHOC) {
			rtl_dm_dig->min_undec_pwdb_for_dm =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			RT_TRACE(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				 "AP Client PWDB = 0x%lx\n",
			       rtlpriv->dm.entry_min_undec_sm_pwdb);
		} else {
			rtl_dm_dig->min_undec_pwdb_for_dm =
			    rtlpriv->dm.undec_sm_pwdb;
			RT_TRACE(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				 "STA Default Port PWDB = 0x%x\n",
				  rtl_dm_dig->min_undec_pwdb_for_dm);
		}
	} else {
		rtl_dm_dig->min_undec_pwdb_for_dm =
				rtlpriv->dm.entry_min_undec_sm_pwdb;
		RT_TRACE(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			 "AP Ext Port or disconnect PWDB = 0x%x\n",
			  rtl_dm_dig->min_undec_pwdb_for_dm);
	}
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "MinUndecoratedPWDBForDM =%d\n",
		 rtl_dm_dig->min_undec_pwdb_for_dm);
}