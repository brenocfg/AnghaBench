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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum band_type { ____Placeholder_band_type } band_type ;

/* Variables and functions */
 int BAND_ON_2_4G ; 
 int BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  MGN_11M 175 
#define  MGN_12M 174 
#define  MGN_18M 173 
#define  MGN_1M 172 
#define  MGN_24M 171 
#define  MGN_2M 170 
#define  MGN_36M 169 
#define  MGN_48M 168 
#define  MGN_54M 167 
#define  MGN_5_5M 166 
#define  MGN_6M 165 
#define  MGN_9M 164 
#define  MGN_MCS0 163 
#define  MGN_MCS1 162 
#define  MGN_MCS10 161 
#define  MGN_MCS11 160 
#define  MGN_MCS12 159 
#define  MGN_MCS13 158 
#define  MGN_MCS14 157 
#define  MGN_MCS15 156 
#define  MGN_MCS2 155 
#define  MGN_MCS3 154 
#define  MGN_MCS4 153 
#define  MGN_MCS5 152 
#define  MGN_MCS6 151 
#define  MGN_MCS7 150 
#define  MGN_MCS8 149 
#define  MGN_MCS9 148 
#define  MGN_VHT1SS_MCS0 147 
#define  MGN_VHT1SS_MCS1 146 
#define  MGN_VHT1SS_MCS2 145 
#define  MGN_VHT1SS_MCS3 144 
#define  MGN_VHT1SS_MCS4 143 
#define  MGN_VHT1SS_MCS5 142 
#define  MGN_VHT1SS_MCS6 141 
#define  MGN_VHT1SS_MCS7 140 
#define  MGN_VHT1SS_MCS8 139 
#define  MGN_VHT1SS_MCS9 138 
#define  MGN_VHT2SS_MCS0 137 
#define  MGN_VHT2SS_MCS1 136 
#define  MGN_VHT2SS_MCS2 135 
#define  MGN_VHT2SS_MCS3 134 
#define  MGN_VHT2SS_MCS4 133 
#define  MGN_VHT2SS_MCS5 132 
#define  MGN_VHT2SS_MCS6 131 
#define  MGN_VHT2SS_MCS7 130 
#define  MGN_VHT2SS_MCS8 129 
#define  MGN_VHT2SS_MCS9 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl8812ae_phy_get_txpower_by_rate_base_index(struct ieee80211_hw *hw,
						   enum band_type band, u8 rate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 index = 0;
	if (band == BAND_ON_2_4G) {
		switch (rate) {
		case MGN_1M:
		case MGN_2M:
		case MGN_5_5M:
		case MGN_11M:
			index = 0;
			break;

		case MGN_6M:
		case MGN_9M:
		case MGN_12M:
		case MGN_18M:
		case MGN_24M:
		case MGN_36M:
		case MGN_48M:
		case MGN_54M:
			index = 1;
			break;

		case MGN_MCS0:
		case MGN_MCS1:
		case MGN_MCS2:
		case MGN_MCS3:
		case MGN_MCS4:
		case MGN_MCS5:
		case MGN_MCS6:
		case MGN_MCS7:
			index = 2;
			break;

		case MGN_MCS8:
		case MGN_MCS9:
		case MGN_MCS10:
		case MGN_MCS11:
		case MGN_MCS12:
		case MGN_MCS13:
		case MGN_MCS14:
		case MGN_MCS15:
			index = 3;
			break;

		default:
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				"Wrong rate 0x%x to obtain index in 2.4G in PHY_GetTxPowerByRateBaseIndex()\n",
				rate);
			break;
		}
	} else if (band == BAND_ON_5G) {
		switch (rate) {
		case MGN_6M:
		case MGN_9M:
		case MGN_12M:
		case MGN_18M:
		case MGN_24M:
		case MGN_36M:
		case MGN_48M:
		case MGN_54M:
			index = 0;
			break;

		case MGN_MCS0:
		case MGN_MCS1:
		case MGN_MCS2:
		case MGN_MCS3:
		case MGN_MCS4:
		case MGN_MCS5:
		case MGN_MCS6:
		case MGN_MCS7:
			index = 1;
			break;

		case MGN_MCS8:
		case MGN_MCS9:
		case MGN_MCS10:
		case MGN_MCS11:
		case MGN_MCS12:
		case MGN_MCS13:
		case MGN_MCS14:
		case MGN_MCS15:
			index = 2;
			break;

		case MGN_VHT1SS_MCS0:
		case MGN_VHT1SS_MCS1:
		case MGN_VHT1SS_MCS2:
		case MGN_VHT1SS_MCS3:
		case MGN_VHT1SS_MCS4:
		case MGN_VHT1SS_MCS5:
		case MGN_VHT1SS_MCS6:
		case MGN_VHT1SS_MCS7:
		case MGN_VHT1SS_MCS8:
		case MGN_VHT1SS_MCS9:
			index = 3;
			break;

		case MGN_VHT2SS_MCS0:
		case MGN_VHT2SS_MCS1:
		case MGN_VHT2SS_MCS2:
		case MGN_VHT2SS_MCS3:
		case MGN_VHT2SS_MCS4:
		case MGN_VHT2SS_MCS5:
		case MGN_VHT2SS_MCS6:
		case MGN_VHT2SS_MCS7:
		case MGN_VHT2SS_MCS8:
		case MGN_VHT2SS_MCS9:
			index = 4;
			break;

		default:
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				"Wrong rate 0x%x to obtain index in 5G in PHY_GetTxPowerByRateBaseIndex()\n",
				rate);
			break;
		}
	}

	return index;
}