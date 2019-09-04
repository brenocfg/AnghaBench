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
struct rtl_phy {int***** txpwr_limit_2_4g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;
typedef  enum rf_tx_num { ____Placeholder_rf_tx_num } rf_tx_num ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ IS_1T_RATESEC (size_t) ; 
 int MAX_POWER_INDEX ; 
 size_t MAX_RATE_SECTION_NUM ; 
 size_t MAX_RF_PATH_NUM ; 
 size_t RF90_PATH_A ; 
 int RF_1TX ; 
 int RF_2TX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,size_t,size_t,int,int,size_t,size_t,size_t) ; 
 size_t _rtl8822be_phy_get_txpower_by_rate_base (struct ieee80211_hw*,int /*<<< orphan*/ ,size_t,int,size_t) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void __rtl8822be_txpwr_limit_to_index_2g(struct ieee80211_hw *hw,
						u8 regulation, u8 bw,
						u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 bw40_pwr_base_dbm2_4G;
	u8 rate_section;
	s8 temp_pwrlmt;
	enum rf_tx_num txnum;
	s8 temp_value;
	u8 rf_path;

	for (rate_section = 0; rate_section < MAX_RATE_SECTION_NUM;
	     ++rate_section) {
		/* obtain the base dBm values in 2.4G band
		 * CCK => 11M, OFDM => 54M, HT 1T => MCS7, HT 2T => MCS15
		 */

		temp_pwrlmt =
			rtlphy->txpwr_limit_2_4g[regulation][bw][rate_section]
						[channel][RF90_PATH_A];
		txnum = IS_1T_RATESEC(rate_section) ? RF_1TX : RF_2TX;

		if (temp_pwrlmt == MAX_POWER_INDEX)
			continue;

		for (rf_path = RF90_PATH_A; rf_path < MAX_RF_PATH_NUM;
		     ++rf_path) {
			bw40_pwr_base_dbm2_4G =
				_rtl8822be_phy_get_txpower_by_rate_base(
					hw, BAND_ON_2_4G, rf_path, txnum,
					rate_section);

			temp_value = temp_pwrlmt - bw40_pwr_base_dbm2_4G;
			rtlphy->txpwr_limit_2_4g[regulation][bw][rate_section]
						[channel][rf_path] = temp_value;

			RT_TRACE(
				rtlpriv, COMP_INIT, DBG_TRACE,
				"TxPwrLimit_2_4G[regulation %d][bw %d][rateSection %d][channel %d] = %d\n(TxPwrLimit in dBm %d - BW40PwrLmt2_4G[channel %d][rfPath %d] %d)\n",
				regulation, bw, rate_section, channel,
				rtlphy->txpwr_limit_2_4g[regulation][bw]
							[rate_section][channel]
							[rf_path],
				(temp_pwrlmt == 63) ? 0 : temp_pwrlmt / 2,
				channel, rf_path, bw40_pwr_base_dbm2_4G);
		}
	}
}