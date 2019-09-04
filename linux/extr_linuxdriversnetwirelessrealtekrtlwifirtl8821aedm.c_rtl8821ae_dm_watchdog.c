#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {scalar_t__ p2p_ps_mode; } ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; int /*<<< orphan*/  rfchange_inprogress; TYPE_3__ p2p_ps_info; } ;
struct TYPE_11__ {scalar_t__ num_qry_beacon_pkt; } ;
struct TYPE_12__ {TYPE_5__ dbginfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  rf_ps_lock; } ;
struct rtl_priv {TYPE_6__ dm; TYPE_4__ locks; TYPE_2__* cfg; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ ERFON ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int /*<<< orphan*/  HW_VAR_FWLPS_RF_ON ; 
 int /*<<< orphan*/  HW_VAR_FW_PSMODE_STATUS ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8812ae_dm_check_txpower_tracking_thermalmeter (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_cck_packet_detection_thresh (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_check_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_check_rssi_monitor (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_check_txpower_tracking_thermalmeter (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_common_info_self_update (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_dynamic_atc_switch (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_false_alarm_counter_statistics (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_iq_calibrate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_refresh_basic_rate_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_refresh_rate_adaptive_mask (struct ieee80211_hw*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtl8821ae_dm_watchdog(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_inpsmode));

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *)(&fw_ps_awake));

	if (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	if ((ppsc->rfpwr_state == ERFON) &&
	    ((!fw_current_inpsmode) && fw_ps_awake) &&
	    (!ppsc->rfchange_inprogress)) {
		rtl8821ae_dm_common_info_self_update(hw);
		rtl8821ae_dm_false_alarm_counter_statistics(hw);
		rtl8821ae_dm_check_rssi_monitor(hw);
		rtl8821ae_dm_dig(hw);
		rtl8821ae_dm_cck_packet_detection_thresh(hw);
		rtl8821ae_dm_refresh_rate_adaptive_mask(hw);
		rtl8821ae_dm_refresh_basic_rate_mask(hw);
		rtl8821ae_dm_check_edca_turbo(hw);
		rtl8821ae_dm_dynamic_atc_switch(hw);
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_dm_check_txpower_tracking_thermalmeter(hw);
		else
			rtl8821ae_dm_check_txpower_tracking_thermalmeter(hw);
		rtl8821ae_dm_iq_calibrate(hw);
	}
	spin_unlock(&rtlpriv->locks.rf_ps_lock);

	rtlpriv->dm.dbginfo.num_qry_beacon_pkt = 0;
	RT_TRACE(rtlpriv, COMP_DIG, DBG_DMESG, "\n");
}