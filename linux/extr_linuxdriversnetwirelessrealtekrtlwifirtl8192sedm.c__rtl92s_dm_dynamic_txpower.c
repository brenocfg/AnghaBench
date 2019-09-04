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
struct rtl_phy {scalar_t__ rf_type; int /*<<< orphan*/  current_channel; } ;
struct rtl_priv {TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int HAL_DM_HIPWR_DISABLE ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* TX_HIGHPWR_LEVEL_NORMAL ; 
 scalar_t__ TX_HIGHPWR_LEVEL_NORMAL1 ; 
 scalar_t__ TX_HIGHPWR_LEVEL_NORMAL2 ; 
 long TX_POWER_NEAR_FIELD_THRESH_LVL1 ; 
 long TX_POWER_NEAR_FIELD_THRESH_LVL2 ; 
 int /*<<< orphan*/  rtl92s_phy_set_txpower (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_dm_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	long undec_sm_pwdb;
	long txpwr_threshold_lv1, txpwr_threshold_lv2;

	/* 2T2R TP issue */
	if (rtlphy->rf_type == RF_2T2R)
		return;

	if (!rtlpriv->dm.dynamic_txpower_enable ||
	    rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL;
		return;
	}

	if ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
			 "Not connected to any\n");

		rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TX_HIGHPWR_LEVEL_NORMAL;
		return;
	}

	if (mac->link_state >= MAC80211_LINKED) {
		if (mac->opmode == NL80211_IFTYPE_ADHOC) {
			undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "AP Client PWDB = 0x%lx\n",
				 undec_sm_pwdb);
		} else {
			undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "STA Default Port PWDB = 0x%lx\n",
				 undec_sm_pwdb);
		}
	} else {
		undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;

		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "AP Ext Port PWDB = 0x%lx\n",
			 undec_sm_pwdb);
	}

	txpwr_threshold_lv2 = TX_POWER_NEAR_FIELD_THRESH_LVL2;
	txpwr_threshold_lv1 = TX_POWER_NEAR_FIELD_THRESH_LVL1;

	if (rtl_get_bbreg(hw, 0xc90, MASKBYTE0) == 1)
		rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL;
	else if (undec_sm_pwdb >= txpwr_threshold_lv2)
		rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL2;
	else if ((undec_sm_pwdb < (txpwr_threshold_lv2 - 3)) &&
		(undec_sm_pwdb >= txpwr_threshold_lv1))
		rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL1;
	else if (undec_sm_pwdb < (txpwr_threshold_lv1 - 3))
		rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL;

	if ((rtlpriv->dm.dynamic_txhighpower_lvl != rtlpriv->dm.last_dtp_lvl))
		rtl92s_phy_set_txpower(hw, rtlphy->current_channel);

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighpower_lvl;
}