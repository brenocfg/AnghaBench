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
typedef  int u32 ;
struct rtl_phy {int current_channel; int num_total_rfpath; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BMASKBYTE0 ; 
 int BRFREGOFFSETMASK ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ HARDWARE_TYPE_RTL8821AE ; 
 int RF90_PATH_A ; 
 int /*<<< orphan*/  RFC_AREA ; 
 int /*<<< orphan*/  RF_APK ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  rtl8821ae_phy_set_rf_reg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

void rtl8821ae_phy_sw_chnl_callback(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 channel = rtlphy->current_channel;
	u8 path;
	u32 data;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE,
		 "switch to channel%d\n", rtlphy->current_channel);
	if (is_hal_stop(rtlhal))
		return;

	if (36 <= channel && channel <= 48)
		data = 0x494;
	else if (50 <= channel && channel <= 64)
		data = 0x453;
	else if (100 <= channel && channel <= 116)
		data = 0x452;
	else if (118 <= channel)
		data = 0x412;
	else
		data = 0x96a;
	rtl_set_bbreg(hw, RFC_AREA, 0x1ffe0000, data);

	for (path = RF90_PATH_A; path < rtlphy->num_total_rfpath; path++) {
		if (36 <= channel && channel <= 64)
			data = 0x101;
		else if (100 <= channel && channel <= 140)
			data = 0x301;
		else if (140 < channel)
			data = 0x501;
		else
			data = 0x000;
		rtl8821ae_phy_set_rf_reg(hw, path, RF_CHNLBW,
			BIT(18)|BIT(17)|BIT(16)|BIT(9)|BIT(8), data);

		rtl8821ae_phy_set_rf_reg(hw, path, RF_CHNLBW,
			BMASKBYTE0, channel);

		if (channel > 14) {
			if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
				if (36 <= channel && channel <= 64)
					data = 0x114E9;
				else if (100 <= channel && channel <= 140)
					data = 0x110E9;
				else
					data = 0x110E9;
				rtl8821ae_phy_set_rf_reg(hw, path, RF_APK,
					BRFREGOFFSETMASK, data);
			}
		}
	}
	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "\n");
}