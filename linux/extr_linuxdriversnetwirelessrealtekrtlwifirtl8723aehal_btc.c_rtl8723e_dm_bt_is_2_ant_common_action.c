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
struct TYPE_2__ {int /*<<< orphan*/  cstate; scalar_t__ bt_busy; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;
struct btdm_8723 {int low_penalty_rate_adaptive; int rf_rx_lpf_shrink; int reject_aggre_pkt; int agc_table_en; int adc_back_off_on; int sw_dac_swing_on; int pta_on; int val_0x6c0; int val_0x6c8; int val_0x6cc; int tdma_on; int b2_ant_hid_en; int dec_bt_pwr; void* tdma_dac_swing; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_COEX_STATE_BTINFO_COMMON ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ RT_MEDIA_CONNECT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* TDMA_DAC_SWING_OFF ; 
 scalar_t__ mgnt_link_status_query (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_btdm_structure_reload (struct ieee80211_hw*,struct btdm_8723*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_btdm_structure_reload_all_off (struct ieee80211_hw*,struct btdm_8723*) ; 
 scalar_t__ rtl8723e_dm_bt_is_coexist_state_changed (struct ieee80211_hw*) ; 
 scalar_t__ rtl8723e_dm_bt_is_wifi_busy (struct ieee80211_hw*) ; 
 scalar_t__ rtl8723e_dm_bt_need_to_dec_bt_pwr (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_bt_dm (struct ieee80211_hw*,struct btdm_8723*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool rtl8723e_dm_bt_is_2_ant_common_action(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct btdm_8723 btdm8723;
	bool b_common = false;

	rtl8723e_dm_bt_btdm_structure_reload(hw, &btdm8723);

	if (!rtl8723e_dm_bt_is_wifi_busy(hw) &&
	    !rtlpriv->btcoexist.bt_busy) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			 "Wifi idle + Bt idle, bt coex mechanism always off!!\n");
		rtl8723e_dm_bt_btdm_structure_reload_all_off(hw, &btdm8723);
		b_common = true;
	} else if (rtl8723e_dm_bt_is_wifi_busy(hw) &&
		   !rtlpriv->btcoexist.bt_busy) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			 "Wifi non-idle + Bt disabled/idle!!\n");
		btdm8723.low_penalty_rate_adaptive = true;
		btdm8723.rf_rx_lpf_shrink = false;
		btdm8723.reject_aggre_pkt = false;

		/* sw mechanism */
		btdm8723.agc_table_en = false;
		btdm8723.adc_back_off_on = false;
		btdm8723.sw_dac_swing_on = false;

		btdm8723.pta_on = true;
		btdm8723.val_0x6c0 = 0x5a5aaaaa;
		btdm8723.val_0x6c8 = 0xcccc;
		btdm8723.val_0x6cc = 0x3;

		btdm8723.tdma_on = false;
		btdm8723.tdma_dac_swing = TDMA_DAC_SWING_OFF;
		btdm8723.b2_ant_hid_en = false;

		b_common = true;
	} else if (rtlpriv->btcoexist.bt_busy) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Bt non-idle!\n");
		if (mgnt_link_status_query(hw) == RT_MEDIA_CONNECT) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi connection exist\n");
			b_common = false;
		} else {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"No Wifi connection!\n");
			btdm8723.rf_rx_lpf_shrink = true;
			btdm8723.low_penalty_rate_adaptive = false;
			btdm8723.reject_aggre_pkt = false;

			/* sw mechanism */
			btdm8723.agc_table_en = false;
			btdm8723.adc_back_off_on = false;
			btdm8723.sw_dac_swing_on = false;

			btdm8723.pta_on = true;
			btdm8723.val_0x6c0 = 0x55555555;
			btdm8723.val_0x6c8 = 0x0000ffff;
			btdm8723.val_0x6cc = 0x3;

			btdm8723.tdma_on = false;
			btdm8723.tdma_dac_swing = TDMA_DAC_SWING_OFF;
			btdm8723.b2_ant_hid_en = false;

			b_common = true;
		}
	}

	if (rtl8723e_dm_bt_need_to_dec_bt_pwr(hw))
		btdm8723.dec_bt_pwr = true;

	if (b_common)
		rtlpriv->btcoexist.cstate |=
			BT_COEX_STATE_BTINFO_COMMON;

	if (b_common && rtl8723e_dm_bt_is_coexist_state_changed(hw))
		rtl8723e_dm_bt_set_bt_dm(hw, &btdm8723);

	return b_common;
}