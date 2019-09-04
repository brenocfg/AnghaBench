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
struct rtl_phy {int**** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 size_t DESC_RATEMCS15 ; 
 size_t DESC_RATEMCS8 ; 
 size_t DESC_RATEVHT2SS_MCS0 ; 
 size_t DESC_RATEVHT2SS_MCS9 ; 
 size_t RF90_PATH_B ; 
 size_t RF_1TX ; 
 size_t RF_2TX ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static char
_rtl8822be_phy_get_txpower_by_rate(struct ieee80211_hw *hw, u8 band, u8 path,
				   u8 rate /* enum rtl_desc8822b_rate */)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 tx_num;
	char tx_pwr_diff = 0;

	if (band != BAND_ON_2_4G && band != BAND_ON_5G)
		return tx_pwr_diff;

	if (path > RF90_PATH_B)
		return tx_pwr_diff;

	if ((rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
	    (rate >= DESC_RATEVHT2SS_MCS0 && rate <= DESC_RATEVHT2SS_MCS9))
		tx_num = RF_2TX;
	else
		tx_num = RF_1TX;

	tx_pwr_diff = (char)(rtlphy->tx_power_by_rate_offset[band][path][tx_num]
							    [rate] &
			     0xff);

	return tx_pwr_diff;
}