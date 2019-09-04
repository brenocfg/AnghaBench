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
typedef  size_t u8 ;
struct rtl_phy {scalar_t__***** txpwr_limit_5g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 size_t HT_CHANNEL_WIDTH_20 ; 
 size_t HT_CHANNEL_WIDTH_20_40 ; 
 size_t HT_MCS0_MCS7 ; 
 size_t HT_MCS8_MCS15 ; 
 scalar_t__ MAX_POWER_INDEX ; 
 size_t MAX_RATE_SECTION_NUM ; 
 size_t RF90_PATH_A ; 
 size_t VHT_1SSMCS0_1SSMCS9 ; 
 size_t VHT_2SSMCS0_2SSMCS9 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void __rtl8822be_phy_cross_reference_core(struct ieee80211_hw *hw,
						 u8 regulation, u8 bw,
						 u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rs, ref_rs;
	s8 pwrlmt, ref_pwrlmt;

	for (rs = 0; rs < MAX_RATE_SECTION_NUM; ++rs) {
		/*5G 20M 40M VHT and HT can cross reference*/
		if (bw != HT_CHANNEL_WIDTH_20 && bw != HT_CHANNEL_WIDTH_20_40)
			continue;

		if (rs == HT_MCS0_MCS7)
			ref_rs = VHT_1SSMCS0_1SSMCS9;
		else if (rs == HT_MCS8_MCS15)
			ref_rs = VHT_2SSMCS0_2SSMCS9;
		else if (rs == VHT_1SSMCS0_1SSMCS9)
			ref_rs = HT_MCS0_MCS7;
		else if (rs == VHT_2SSMCS0_2SSMCS9)
			ref_rs = HT_MCS8_MCS15;
		else
			continue;

		ref_pwrlmt = rtlphy->txpwr_limit_5g[regulation][bw][ref_rs]
						   [channel][RF90_PATH_A];
		if (ref_pwrlmt == MAX_POWER_INDEX)
			continue;

		pwrlmt = rtlphy->txpwr_limit_5g[regulation][bw][rs][channel]
					       [RF90_PATH_A];
		if (pwrlmt != MAX_POWER_INDEX)
			continue;

		rtlphy->txpwr_limit_5g[regulation][bw][rs][channel]
				      [RF90_PATH_A] = ref_pwrlmt;
	}
}