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
struct TYPE_2__ {int dm_flag; int undec_sm_pwdb; int undec_sm_cck; int dm_initialgain_enable; int /*<<< orphan*/  dm_rssi_sel; scalar_t__ ofdm_pkt_cnt; int /*<<< orphan*/  dm_type; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_TYPE_BYDRIVER ; 
 int DYNAMIC_FUNC_DIG ; 
 int DYNAMIC_FUNC_DISABLE ; 
 int DYNAMIC_FUNC_SS ; 
 int HAL_DM_HIPWR_DISABLE ; 
 int /*<<< orphan*/  RSSI_DEFAULT ; 
 int /*<<< orphan*/  rtl92c_dm_init_dynamic_bb_powersaving (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_init_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_init_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_init_rate_adaptive_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_initialize_txpower_tracking (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_dm_diginit (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92c_dm_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtlpriv->dm.dm_flag = DYNAMIC_FUNC_DISABLE | DYNAMIC_FUNC_DIG;
	rtlpriv->dm.undec_sm_pwdb = -1;
	rtlpriv->dm.undec_sm_cck = -1;
	rtlpriv->dm.dm_initialgain_enable = true;
	rtl_dm_diginit(hw, 0x20);

	rtlpriv->dm.dm_flag |= HAL_DM_HIPWR_DISABLE;
	rtl92c_dm_init_dynamic_txpower(hw);

	rtl92c_dm_init_edca_turbo(hw);
	rtl92c_dm_init_rate_adaptive_mask(hw);
	rtlpriv->dm.dm_flag |= DYNAMIC_FUNC_SS;
	rtl92c_dm_initialize_txpower_tracking(hw);
	rtl92c_dm_init_dynamic_bb_powersaving(hw);

	rtlpriv->dm.ofdm_pkt_cnt = 0;
	rtlpriv->dm.dm_rssi_sel = RSSI_DEFAULT;
}