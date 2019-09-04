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
struct rtl_phy {scalar_t__**** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 size_t TX_PWR_BY_RATE_NUM_RATE ; 
 size_t TX_PWR_BY_RATE_NUM_RF ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8822be_phy_init_tx_power_by_rate(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	u8 band, rfpath, txnum, rate;

	for (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band)
		for (rfpath = 0; rfpath < TX_PWR_BY_RATE_NUM_RF; ++rfpath)
			for (txnum = 0; txnum < TX_PWR_BY_RATE_NUM_RF; ++txnum)
				for (rate = 0; rate < TX_PWR_BY_RATE_NUM_RATE;
				     ++rate)
					rtlphy->tx_power_by_rate_offset
						[band][rfpath][txnum][rate] = 0;
}