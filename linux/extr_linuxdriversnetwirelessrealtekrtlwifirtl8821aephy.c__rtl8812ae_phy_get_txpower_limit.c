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
typedef  size_t u16 ;
struct rtl_phy {int /*<<< orphan*/ ***** txpwr_limit_5g; int /*<<< orphan*/ ***** txpwr_limit_2_4g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_efuse {int eeprom_regulatory; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int BAND_ON_2_4G ; 
 int BAND_ON_5G ; 
 int BAND_ON_BOTH ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DESC_RATE11M 175 
#define  DESC_RATE12M 174 
#define  DESC_RATE18M 173 
#define  DESC_RATE1M 172 
#define  DESC_RATE24M 171 
#define  DESC_RATE2M 170 
#define  DESC_RATE36M 169 
#define  DESC_RATE48M 168 
#define  DESC_RATE54M 167 
#define  DESC_RATE5_5M 166 
#define  DESC_RATE6M 165 
#define  DESC_RATE9M 164 
#define  DESC_RATEMCS0 163 
#define  DESC_RATEMCS1 162 
#define  DESC_RATEMCS10 161 
#define  DESC_RATEMCS11 160 
#define  DESC_RATEMCS12 159 
#define  DESC_RATEMCS13 158 
#define  DESC_RATEMCS14 157 
#define  DESC_RATEMCS15 156 
#define  DESC_RATEMCS2 155 
#define  DESC_RATEMCS3 154 
#define  DESC_RATEMCS4 153 
#define  DESC_RATEMCS5 152 
#define  DESC_RATEMCS6 151 
#define  DESC_RATEMCS7 150 
#define  DESC_RATEMCS8 149 
#define  DESC_RATEMCS9 148 
#define  DESC_RATEVHT1SS_MCS0 147 
#define  DESC_RATEVHT1SS_MCS1 146 
#define  DESC_RATEVHT1SS_MCS2 145 
#define  DESC_RATEVHT1SS_MCS3 144 
#define  DESC_RATEVHT1SS_MCS4 143 
#define  DESC_RATEVHT1SS_MCS5 142 
#define  DESC_RATEVHT1SS_MCS6 141 
#define  DESC_RATEVHT1SS_MCS7 140 
#define  DESC_RATEVHT1SS_MCS8 139 
#define  DESC_RATEVHT1SS_MCS9 138 
#define  DESC_RATEVHT2SS_MCS0 137 
#define  DESC_RATEVHT2SS_MCS1 136 
#define  DESC_RATEVHT2SS_MCS2 135 
#define  DESC_RATEVHT2SS_MCS3 134 
#define  DESC_RATEVHT2SS_MCS4 133 
#define  DESC_RATEVHT2SS_MCS5 132 
#define  DESC_RATEVHT2SS_MCS6 131 
#define  DESC_RATEVHT2SS_MCS7 130 
#define  DESC_RATEVHT2SS_MCS8 129 
#define  DESC_RATEVHT2SS_MCS9 128 
 int HT_CHANNEL_WIDTH_20 ; 
 int HT_CHANNEL_WIDTH_20_40 ; 
 int HT_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  MAX_POWER_INDEX ; 
 int MAX_REGULATION_NUM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 short TXPWR_LMT_WW ; 
 short _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl8812ae_phy_get_world_wide_limit (int /*<<< orphan*/ *) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static s8 _rtl8812ae_phy_get_txpower_limit(struct ieee80211_hw *hw,
					     u8 band,
					     enum ht_channel_width bandwidth,
					     enum radio_path rf_path,
					     u8 rate, u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	short band_temp = -1, regulation = -1, bandwidth_temp = -1,
		 rate_section = -1, channel_temp = -1;
	u16 bd, regu, bdwidth, sec, chnl;
	s8 power_limit = MAX_POWER_INDEX;

	if (rtlefuse->eeprom_regulatory == 2)
		return MAX_POWER_INDEX;

	regulation = TXPWR_LMT_WW;

	if (band == BAND_ON_2_4G)
		band_temp = 0;
	else if (band == BAND_ON_5G)
		band_temp = 1;

	if (bandwidth == HT_CHANNEL_WIDTH_20)
		bandwidth_temp = 0;
	else if (bandwidth == HT_CHANNEL_WIDTH_20_40)
		bandwidth_temp = 1;
	else if (bandwidth == HT_CHANNEL_WIDTH_80)
		bandwidth_temp = 2;

	switch (rate) {
	case DESC_RATE1M:
	case DESC_RATE2M:
	case DESC_RATE5_5M:
	case DESC_RATE11M:
		rate_section = 0;
		break;
	case DESC_RATE6M:
	case DESC_RATE9M:
	case DESC_RATE12M:
	case DESC_RATE18M:
	case DESC_RATE24M:
	case DESC_RATE36M:
	case DESC_RATE48M:
	case DESC_RATE54M:
		rate_section = 1;
		break;
	case DESC_RATEMCS0:
	case DESC_RATEMCS1:
	case DESC_RATEMCS2:
	case DESC_RATEMCS3:
	case DESC_RATEMCS4:
	case DESC_RATEMCS5:
	case DESC_RATEMCS6:
	case DESC_RATEMCS7:
		rate_section = 2;
		break;
	case DESC_RATEMCS8:
	case DESC_RATEMCS9:
	case DESC_RATEMCS10:
	case DESC_RATEMCS11:
	case DESC_RATEMCS12:
	case DESC_RATEMCS13:
	case DESC_RATEMCS14:
	case DESC_RATEMCS15:
		rate_section = 3;
		break;
	case DESC_RATEVHT1SS_MCS0:
	case DESC_RATEVHT1SS_MCS1:
	case DESC_RATEVHT1SS_MCS2:
	case DESC_RATEVHT1SS_MCS3:
	case DESC_RATEVHT1SS_MCS4:
	case DESC_RATEVHT1SS_MCS5:
	case DESC_RATEVHT1SS_MCS6:
	case DESC_RATEVHT1SS_MCS7:
	case DESC_RATEVHT1SS_MCS8:
	case DESC_RATEVHT1SS_MCS9:
		rate_section = 4;
		break;
	case DESC_RATEVHT2SS_MCS0:
	case DESC_RATEVHT2SS_MCS1:
	case DESC_RATEVHT2SS_MCS2:
	case DESC_RATEVHT2SS_MCS3:
	case DESC_RATEVHT2SS_MCS4:
	case DESC_RATEVHT2SS_MCS5:
	case DESC_RATEVHT2SS_MCS6:
	case DESC_RATEVHT2SS_MCS7:
	case DESC_RATEVHT2SS_MCS8:
	case DESC_RATEVHT2SS_MCS9:
		rate_section = 5;
		break;
	default:
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			"Wrong rate 0x%x\n", rate);
		break;
	}

	if (band_temp == BAND_ON_5G  && rate_section == 0)
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Wrong rate 0x%x: No CCK in 5G Band\n", rate);

	/*workaround for wrong index combination to obtain tx power limit,
	  OFDM only exists in BW 20M*/
	if (rate_section == 1)
		bandwidth_temp = 0;

	/*workaround for wrong index combination to obtain tx power limit,
	 *HT on 80M will reference to HT on 40M
	 */
	if ((rate_section == 2 || rate_section == 3) && band == BAND_ON_5G &&
	    bandwidth_temp == 2)
		bandwidth_temp = 1;

	if (band == BAND_ON_2_4G)
		channel_temp = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
		BAND_ON_2_4G, channel);
	else if (band == BAND_ON_5G)
		channel_temp = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
		BAND_ON_5G, channel);
	else if (band == BAND_ON_BOTH)
		;/* BAND_ON_BOTH don't care temporarily */

	if (band_temp == -1 || regulation == -1 || bandwidth_temp == -1 ||
		rate_section == -1 || channel_temp == -1) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Wrong index value to access power limit table [band %d][regulation %d][bandwidth %d][rf_path %d][rate_section %d][chnl %d]\n",
			 band_temp, regulation, bandwidth_temp, rf_path,
			 rate_section, channel_temp);
		return MAX_POWER_INDEX;
	}

	bd = band_temp;
	regu = regulation;
	bdwidth = bandwidth_temp;
	sec = rate_section;
	chnl = channel_temp;

	if (band == BAND_ON_2_4G) {
		s8 limits[10] = {0};
		u8 i;

		for (i = 0; i < 4; ++i)
			limits[i] = rtlphy->txpwr_limit_2_4g[i][bdwidth]
			[sec][chnl][rf_path];

		power_limit = (regulation == TXPWR_LMT_WW) ?
			_rtl8812ae_phy_get_world_wide_limit(limits) :
			rtlphy->txpwr_limit_2_4g[regu][bdwidth]
					[sec][chnl][rf_path];
	} else if (band == BAND_ON_5G) {
		s8 limits[10] = {0};
		u8 i;

		for (i = 0; i < MAX_REGULATION_NUM; ++i)
			limits[i] = rtlphy->txpwr_limit_5g[i][bdwidth]
			[sec][chnl][rf_path];

		power_limit = (regulation == TXPWR_LMT_WW) ?
			_rtl8812ae_phy_get_world_wide_limit(limits) :
			rtlphy->txpwr_limit_5g[regu][chnl]
			[sec][chnl][rf_path];
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "No power limit table of the specified band\n");
	}
	return power_limit;
}