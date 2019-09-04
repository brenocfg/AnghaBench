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
typedef  size_t u32 ;
struct rtl_phy {int /*<<< orphan*/ **** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 scalar_t__ IS_1T_RATE (size_t) ; 
 scalar_t__ IS_2T_RATE (size_t) ; 
 size_t MAX_RF_PATH ; 
 size_t RF_1TX ; 
 size_t RF_2TX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _rtl8822be_get_rate_values_of_tx_power_by_rate (struct ieee80211_hw*,size_t,size_t,size_t,size_t*,int /*<<< orphan*/ *,size_t*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8822be_store_tx_power_by_rate(struct ieee80211_hw *hw, u32 band,
				      u32 rfpath, u32 txnum, u32 regaddr,
				      u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i = 0, rates[4] = {0}, rate_num = 0;
	s8 pwr_by_rate_val[4] = {0};

	_rtl8822be_get_rate_values_of_tx_power_by_rate(
		hw, regaddr, bitmask, data, rates, pwr_by_rate_val, &rate_num);

	if (band != BAND_ON_2_4G && band != BAND_ON_5G) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid Band %d\n",
			 band);
		band = BAND_ON_2_4G;
	}
	if (rfpath >= MAX_RF_PATH) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid RfPath %d\n",
			 rfpath);
		rfpath = MAX_RF_PATH - 1;
	}
	if (txnum >= MAX_RF_PATH) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid TxNum %d\n",
			 txnum);
		txnum = MAX_RF_PATH - 1;
	}

	for (i = 0; i < rate_num; ++i) {
		u8 rate_idx = rates[i];

		if (IS_1T_RATE(rates[i]))
			txnum = RF_1TX;
		else if (IS_2T_RATE(rates[i]))
			txnum = RF_2TX;
		else
			WARN_ON(1);

		rtlphy->tx_power_by_rate_offset[band][rfpath][txnum][rate_idx] =
			pwr_by_rate_val[i];

		RT_TRACE(
			rtlpriv, COMP_INIT, DBG_LOUD,
			"TxPwrByRateOffset[Band %d][RfPath %d][TxNum %d][rate_idx %d] = 0x%x\n",
			band, rfpath, txnum, rate_idx,
			rtlphy->tx_power_by_rate_offset[band][rfpath][txnum]
						       [rate_idx]);
	}
}