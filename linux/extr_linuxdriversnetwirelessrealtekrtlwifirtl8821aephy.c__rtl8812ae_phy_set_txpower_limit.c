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
struct rtl_phy {scalar_t__***** txpwr_limit_2_4g; scalar_t__***** txpwr_limit_5g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ MAX_POWER_INDEX ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ _rtl8812ae_eq_n_byte (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  _rtl8812ae_get_integer_from_string (char*,...) ; 
 scalar_t__ _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt (struct ieee80211_hw*,int /*<<< orphan*/ ,size_t) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8812ae_phy_set_txpower_limit(struct ieee80211_hw *hw, u8 *pregulation,
				      u8 *pband, u8 *pbandwidth,
				      u8 *prate_section, u8 *prf_path,
				      u8 *pchannel, u8 *ppower_limit)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 regulation = 0, bandwidth = 0, rate_section = 0, channel;
	u8 channel_index;
	s8 power_limit = 0, prev_power_limit, ret;

	if (!_rtl8812ae_get_integer_from_string((char *)pchannel, &channel) ||
	    !_rtl8812ae_get_integer_from_string((char *)ppower_limit,
						&power_limit)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Illegal index of pwr_lmt table [chnl %d][val %d]\n",
			  channel, power_limit);
	}

	power_limit = power_limit > MAX_POWER_INDEX ?
		      MAX_POWER_INDEX : power_limit;

	if (_rtl8812ae_eq_n_byte(pregulation, (u8 *)("FCC"), 3))
		regulation = 0;
	else if (_rtl8812ae_eq_n_byte(pregulation, (u8 *)("MKK"), 3))
		regulation = 1;
	else if (_rtl8812ae_eq_n_byte(pregulation, (u8 *)("ETSI"), 4))
		regulation = 2;
	else if (_rtl8812ae_eq_n_byte(pregulation, (u8 *)("WW13"), 4))
		regulation = 3;

	if (_rtl8812ae_eq_n_byte(prate_section, (u8 *)("CCK"), 3))
		rate_section = 0;
	else if (_rtl8812ae_eq_n_byte(prate_section, (u8 *)("OFDM"), 4))
		rate_section = 1;
	else if (_rtl8812ae_eq_n_byte(prate_section, (u8 *)("HT"), 2) &&
		 _rtl8812ae_eq_n_byte(prf_path, (u8 *)("1T"), 2))
		rate_section = 2;
	else if (_rtl8812ae_eq_n_byte(prate_section, (u8 *)("HT"), 2) &&
		 _rtl8812ae_eq_n_byte(prf_path, (u8 *)("2T"), 2))
		rate_section = 3;
	else if (_rtl8812ae_eq_n_byte(prate_section, (u8 *)("VHT"), 3) &&
		 _rtl8812ae_eq_n_byte(prf_path, (u8 *)("1T"), 2))
		rate_section = 4;
	else if (_rtl8812ae_eq_n_byte(prate_section, (u8 *)("VHT"), 3) &&
		 _rtl8812ae_eq_n_byte(prf_path, (u8 *)("2T"), 2))
		rate_section = 5;

	if (_rtl8812ae_eq_n_byte(pbandwidth, (u8 *)("20M"), 3))
		bandwidth = 0;
	else if (_rtl8812ae_eq_n_byte(pbandwidth, (u8 *)("40M"), 3))
		bandwidth = 1;
	else if (_rtl8812ae_eq_n_byte(pbandwidth, (u8 *)("80M"), 3))
		bandwidth = 2;
	else if (_rtl8812ae_eq_n_byte(pbandwidth, (u8 *)("160M"), 4))
		bandwidth = 3;

	if (_rtl8812ae_eq_n_byte(pband, (u8 *)("2.4G"), 4)) {
		ret = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
							       BAND_ON_2_4G,
							       channel);

		if (ret == -1)
			return;

		channel_index = ret;

		prev_power_limit = rtlphy->txpwr_limit_2_4g[regulation]
						[bandwidth][rate_section]
						[channel_index][RF90_PATH_A];

		if (power_limit < prev_power_limit)
			rtlphy->txpwr_limit_2_4g[regulation][bandwidth]
				[rate_section][channel_index][RF90_PATH_A] =
								   power_limit;

		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "2.4G [regula %d][bw %d][sec %d][chnl %d][val %d]\n",
			  regulation, bandwidth, rate_section, channel_index,
			  rtlphy->txpwr_limit_2_4g[regulation][bandwidth]
				[rate_section][channel_index][RF90_PATH_A]);
	} else if (_rtl8812ae_eq_n_byte(pband, (u8 *)("5G"), 2)) {
		ret = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
							       BAND_ON_5G,
							       channel);

		if (ret == -1)
			return;

		channel_index = ret;

		prev_power_limit = rtlphy->txpwr_limit_5g[regulation][bandwidth]
						[rate_section][channel_index]
						[RF90_PATH_A];

		if (power_limit < prev_power_limit)
			rtlphy->txpwr_limit_5g[regulation][bandwidth]
			[rate_section][channel_index][RF90_PATH_A] = power_limit;

		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "5G: [regul %d][bw %d][sec %d][chnl %d][val %d]\n",
			  regulation, bandwidth, rate_section, channel,
			  rtlphy->txpwr_limit_5g[regulation][bandwidth]
				[rate_section][channel_index][RF90_PATH_A]);
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Cannot recognize the band info in %s\n", pband);
		return;
	}
}