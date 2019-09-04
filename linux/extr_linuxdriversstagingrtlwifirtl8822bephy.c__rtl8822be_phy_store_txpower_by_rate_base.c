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
struct rtl_phy {size_t**** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rtl_desc_rate { ____Placeholder_rtl_desc_rate } rtl_desc_rate ;
typedef  enum rate_section { ____Placeholder_rate_section } rate_section ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 int /*<<< orphan*/  CCK ; 
 int /*<<< orphan*/  DESC_RATE11M ; 
 int /*<<< orphan*/  DESC_RATE54M ; 
 int /*<<< orphan*/  DESC_RATEMCS15 ; 
 int /*<<< orphan*/  DESC_RATEMCS7 ; 
 int /*<<< orphan*/  DESC_RATEVHT1SS_MCS7 ; 
 int /*<<< orphan*/  DESC_RATEVHT2SS_MCS7 ; 
 int /*<<< orphan*/  HT_MCS0_MCS7 ; 
 int /*<<< orphan*/  HT_MCS8_MCS15 ; 
 scalar_t__ IS_1T_RATE (size_t) ; 
 size_t MAX_RATE_SECTION ; 
 int /*<<< orphan*/  OFDM ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 size_t RF_1TX ; 
 size_t RF_2TX ; 
 scalar_t__ RX_HAL_IS_CCK_RATE (size_t) ; 
 int /*<<< orphan*/  VHT_1SSMCS0_1SSMCS9 ; 
 int /*<<< orphan*/  VHT_2SSMCS0_2SSMCS9 ; 
 int /*<<< orphan*/  _rtl8822be_phy_set_txpower_by_rate_base (struct ieee80211_hw*,size_t,size_t,size_t,size_t,size_t) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8822be_phy_store_txpower_by_rate_base(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	struct {
		enum rtl_desc_rate rate;
		enum rate_section section;
	} rate_sec_base[] = {
		{DESC_RATE11M, CCK},
		{DESC_RATE54M, OFDM},
		{DESC_RATEMCS7, HT_MCS0_MCS7},
		{DESC_RATEMCS15, HT_MCS8_MCS15},
		{DESC_RATEVHT1SS_MCS7, VHT_1SSMCS0_1SSMCS9},
		{DESC_RATEVHT2SS_MCS7, VHT_2SSMCS0_2SSMCS9},
	};

	u8 band, path, rs, tx_num, base;
	u8 rate, section;

	for (band = BAND_ON_2_4G; band <= BAND_ON_5G; band++) {
		for (path = RF90_PATH_A; path <= RF90_PATH_B; path++) {
			for (rs = 0; rs < MAX_RATE_SECTION; rs++) {
				rate = rate_sec_base[rs].rate;
				section = rate_sec_base[rs].section;

				if (IS_1T_RATE(rate))
					tx_num = RF_1TX;
				else
					tx_num = RF_2TX;

				if (band == BAND_ON_5G &&
				    RX_HAL_IS_CCK_RATE(rate))
					continue;

				base = rtlphy->tx_power_by_rate_offset
					       [band][path][tx_num][rate];
				_rtl8822be_phy_set_txpower_by_rate_base(
					hw, band, path, section, tx_num, base);
			}
		}
	}
}