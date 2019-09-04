#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct rtl_phy {int dummy; } ;
struct rtl_priv {TYPE_3__* cfg; struct rtl_phy phy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_mcs_map; } ;
struct TYPE_5__ {TYPE_1__ vht_mcs; } ;
struct ieee80211_sta {TYPE_2__ vht_cap; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * maps; } ;

/* Variables and functions */
 int IEEE80211_VHT_MCS_SUPPORT_0_7 ; 
 int IEEE80211_VHT_MCS_SUPPORT_0_8 ; 
 scalar_t__ RF_2T2R ; 
 size_t RTL_RC_VHT_RATE_1SS_MCS7 ; 
 size_t RTL_RC_VHT_RATE_1SS_MCS8 ; 
 size_t RTL_RC_VHT_RATE_1SS_MCS9 ; 
 size_t RTL_RC_VHT_RATE_2SS_MCS7 ; 
 size_t RTL_RC_VHT_RATE_2SS_MCS8 ; 
 size_t RTL_RC_VHT_RATE_2SS_MCS9 ; 
 scalar_t__ get_rf_type (struct rtl_phy*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl_get_vht_highest_n_rate(struct ieee80211_hw *hw,
				      struct ieee80211_sta *sta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 hw_rate;
	u16 tx_mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.tx_mcs_map);

	if ((get_rf_type(rtlphy) == RF_2T2R) &&
	    (tx_mcs_map & 0x000c) != 0x000c) {
		if ((tx_mcs_map & 0x000c) >> 2 ==
			IEEE80211_VHT_MCS_SUPPORT_0_7)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS7];
		else if ((tx_mcs_map  & 0x000c) >> 2 ==
			IEEE80211_VHT_MCS_SUPPORT_0_8)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS8];
		else
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS9];
	} else {
		if ((tx_mcs_map  & 0x0003) ==
			IEEE80211_VHT_MCS_SUPPORT_0_7)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS7];
		else if ((tx_mcs_map  & 0x0003) ==
			IEEE80211_VHT_MCS_SUPPORT_0_8)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS8];
		else
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS9];
	}

	return hw_rate;
}