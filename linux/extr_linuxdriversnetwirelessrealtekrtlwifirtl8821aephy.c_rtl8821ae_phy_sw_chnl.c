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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct rtl_phy {int current_channel; int sw_chnl_inprogress; scalar_t__ lck_inprogress; scalar_t__ set_bwmode_inprogress; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_CHAN ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ RT_CANNOT_IO (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8821ae_dm_clear_txpower_tracking_state (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_phy_set_txpower_level (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8821ae_phy_sw_chnl_callback (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_phy_switch_wirelessband (struct ieee80211_hw*,scalar_t__) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u8 rtl8821ae_phy_sw_chnl(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 timeout = 1000, timecount = 0;
	u8 channel = rtlphy->current_channel;

	if (rtlphy->sw_chnl_inprogress)
		return 0;
	if (rtlphy->set_bwmode_inprogress)
		return 0;

	if ((is_hal_stop(rtlhal)) || (RT_CANNOT_IO(hw))) {
		RT_TRACE(rtlpriv, COMP_CHAN, DBG_LOUD,
			 "sw_chnl_inprogress false driver sleep or unload\n");
		return 0;
	}
	while (rtlphy->lck_inprogress && timecount < timeout) {
		mdelay(50);
		timecount += 50;
	}

	if (rtlphy->current_channel > 14 && rtlhal->current_bandtype != BAND_ON_5G)
		rtl8821ae_phy_switch_wirelessband(hw, BAND_ON_5G);
	else if (rtlphy->current_channel <= 14 && rtlhal->current_bandtype != BAND_ON_2_4G)
		rtl8821ae_phy_switch_wirelessband(hw, BAND_ON_2_4G);

	rtlphy->sw_chnl_inprogress = true;
	if (channel == 0)
		channel = 1;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE,
		 "switch to channel%d, band type is %d\n",
		 rtlphy->current_channel, rtlhal->current_bandtype);

	rtl8821ae_phy_sw_chnl_callback(hw);

	rtl8821ae_dm_clear_txpower_tracking_state(hw);
	rtl8821ae_phy_set_txpower_level(hw, rtlphy->current_channel);

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "\n");
	rtlphy->sw_chnl_inprogress = false;
	return 1;
}