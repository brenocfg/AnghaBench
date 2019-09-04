#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDMA_2ANT ; 
 int /*<<< orphan*/  TDMA_DAC_SWING_OFF ; 
 int /*<<< orphan*/  TDMA_NAV_OFF ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_2_ant_hid (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_3a (struct ieee80211_hw*,int,int,int,int,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_bt_hid_info (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_bt_retry_index (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_dac_swing_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_dec_bt_pwr (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_ignore_wlan_act (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_tdma_ctrl (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_tra_tdma_ctrl (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_fw_wlan_act (struct ieee80211_hw*,int,int) ; 

void rtl8723e_dm_bt_fw_coex_all_off_8723a(struct ieee80211_hw *hw)
{
	rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw, false);
	rtl8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);
	rtl8723e_dm_bt_set_fw_2_ant_hid(hw, false, false);
	rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(hw, false, TDMA_2ANT,
					    TDMA_NAV_OFF);
	rtl8723e_dm_bt_set_fw_tdma_ctrl(hw, false, TDMA_2ANT, TDMA_NAV_OFF,
					TDMA_DAC_SWING_OFF);
	rtl8723e_dm_bt_set_fw_dac_swing_level(hw, 0);
	rtl8723e_dm_bt_set_fw_bt_hid_info(hw, false);
	rtl8723e_dm_bt_set_fw_bt_retry_index(hw, 2);
	rtl8723e_dm_bt_set_fw_wlan_act(hw, 0x10, 0x10);
	rtl8723e_dm_bt_set_fw_dec_bt_pwr(hw, false);
}