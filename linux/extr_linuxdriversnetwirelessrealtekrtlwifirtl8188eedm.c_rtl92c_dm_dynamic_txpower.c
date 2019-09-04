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
struct TYPE_2__ {int dm_flag; scalar_t__ dynamic_txhighpower_lvl; long entry_min_undec_sm_pwdb; scalar_t__ last_dtp_lvl; long undec_sm_pwdb; int /*<<< orphan*/  dynamic_txpower_enable; } ;
struct rtl_phy {long current_channel; } ;
struct rtl_priv {TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int HAL_DM_HIPWR_DISABLE ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* TXHIGHPWRLEVEL_LEVEL1 ; 
 void* TXHIGHPWRLEVEL_NORMAL ; 
 long TX_POWER_NEAR_FIELD_THRESH_LVL1 ; 
 long TX_POWER_NEAR_FIELD_THRESH_LVL2 ; 
 int /*<<< orphan*/  rtl88e_phy_set_txpower_level (struct ieee80211_hw*,long) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92c_dm_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	long undec_sm_pwdb;

	if (!rtlpriv->dm.dynamic_txpower_enable)
		return;

	if (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
		return;
	}

	if ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
			 "Not connected to any\n");

		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
		return;
	}

	if (mac->link_state >= MAC80211_LINKED) {
		if (mac->opmode == NL80211_IFTYPE_ADHOC) {
			undec_sm_pwdb =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "AP Client PWDB = 0x%lx\n",
				  undec_sm_pwdb);
		} else {
			undec_sm_pwdb =
			    rtlpriv->dm.undec_sm_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "STA Default Port PWDB = 0x%lx\n",
				  undec_sm_pwdb);
		}
	} else {
		undec_sm_pwdb =
		    rtlpriv->dm.entry_min_undec_sm_pwdb;

		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "AP Ext Port PWDB = 0x%lx\n",
			  undec_sm_pwdb);
	}

	if (undec_sm_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL2) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_LEVEL1;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "TXHIGHPWRLEVEL_LEVEL1 (TxPwr = 0x0)\n");
	} else if ((undec_sm_pwdb <
		    (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3)) &&
		   (undec_sm_pwdb >=
		    TX_POWER_NEAR_FIELD_THRESH_LVL1)) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_LEVEL1;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "TXHIGHPWRLEVEL_LEVEL1 (TxPwr = 0x10)\n");
	} else if (undec_sm_pwdb <
		   (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "TXHIGHPWRLEVEL_NORMAL\n");
	}

	if ((rtlpriv->dm.dynamic_txhighpower_lvl !=
		rtlpriv->dm.last_dtp_lvl)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "PHY_SetTxPowerLevel8192S() Channel = %d\n",
			  rtlphy->current_channel);
		rtl88e_phy_set_txpower_level(hw, rtlphy->current_channel);
	}

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighpower_lvl;
}