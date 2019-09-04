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

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
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
 int MGN_11M ; 
 int MGN_12M ; 
 int MGN_18M ; 
 int MGN_1M ; 
 int MGN_24M ; 
 int MGN_2M ; 
 int MGN_36M ; 
 int MGN_48M ; 
 int MGN_54M ; 
 int MGN_5_5M ; 
 int MGN_6M ; 
 int MGN_9M ; 
 int MGN_MCS0 ; 
 int MGN_MCS1 ; 
 int MGN_MCS10 ; 
 int MGN_MCS11 ; 
 int MGN_MCS12 ; 
 int MGN_MCS13 ; 
 int MGN_MCS14 ; 
 int MGN_MCS15 ; 
 int MGN_MCS2 ; 
 int MGN_MCS3 ; 
 int MGN_MCS4 ; 
 int MGN_MCS5 ; 
 int MGN_MCS6 ; 
 int MGN_MCS7 ; 
 int MGN_MCS8 ; 
 int MGN_MCS9 ; 
 int MGN_VHT1SS_MCS0 ; 
 int MGN_VHT1SS_MCS1 ; 
 int MGN_VHT1SS_MCS2 ; 
 int MGN_VHT1SS_MCS3 ; 
 int MGN_VHT1SS_MCS4 ; 
 int MGN_VHT1SS_MCS5 ; 
 int MGN_VHT1SS_MCS6 ; 
 int MGN_VHT1SS_MCS7 ; 
 int MGN_VHT1SS_MCS8 ; 
 int MGN_VHT1SS_MCS9 ; 
 int MGN_VHT2SS_MCS0 ; 
 int MGN_VHT2SS_MCS1 ; 
 int MGN_VHT2SS_MCS2 ; 
 int MGN_VHT2SS_MCS3 ; 
 int MGN_VHT2SS_MCS4 ; 
 int MGN_VHT2SS_MCS5 ; 
 int MGN_VHT2SS_MCS6 ; 
 int MGN_VHT2SS_MCS7 ; 
 int MGN_VHT2SS_MCS8 ; 
 int MGN_VHT2SS_MCS9 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u8 rtl8821ae_hw_rate_to_mrate(struct ieee80211_hw *hw, u8 rate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 ret_rate = MGN_1M;

	switch (rate) {
	case DESC_RATE1M:
		ret_rate = MGN_1M;
		break;
	case DESC_RATE2M:
		ret_rate = MGN_2M;
		break;
	case DESC_RATE5_5M:
		ret_rate = MGN_5_5M;
		break;
	case DESC_RATE11M:
		ret_rate = MGN_11M;
		break;
	case DESC_RATE6M:
		ret_rate = MGN_6M;
		break;
	case DESC_RATE9M:
		ret_rate = MGN_9M;
		break;
	case DESC_RATE12M:
		ret_rate = MGN_12M;
		break;
	case DESC_RATE18M:
		ret_rate = MGN_18M;
		break;
	case DESC_RATE24M:
		ret_rate = MGN_24M;
		break;
	case DESC_RATE36M:
		ret_rate = MGN_36M;
		break;
	case DESC_RATE48M:
		ret_rate = MGN_48M;
		break;
	case DESC_RATE54M:
		ret_rate = MGN_54M;
		break;
	case DESC_RATEMCS0:
		ret_rate = MGN_MCS0;
		break;
	case DESC_RATEMCS1:
		ret_rate = MGN_MCS1;
		break;
	case DESC_RATEMCS2:
		ret_rate = MGN_MCS2;
		break;
	case DESC_RATEMCS3:
		ret_rate = MGN_MCS3;
		break;
	case DESC_RATEMCS4:
		ret_rate = MGN_MCS4;
		break;
	case DESC_RATEMCS5:
		ret_rate = MGN_MCS5;
		break;
	case DESC_RATEMCS6:
		ret_rate = MGN_MCS6;
		break;
	case DESC_RATEMCS7:
		ret_rate = MGN_MCS7;
		break;
	case DESC_RATEMCS8:
		ret_rate = MGN_MCS8;
		break;
	case DESC_RATEMCS9:
		ret_rate = MGN_MCS9;
		break;
	case DESC_RATEMCS10:
		ret_rate = MGN_MCS10;
		break;
	case DESC_RATEMCS11:
		ret_rate = MGN_MCS11;
		break;
	case DESC_RATEMCS12:
		ret_rate = MGN_MCS12;
		break;
	case DESC_RATEMCS13:
		ret_rate = MGN_MCS13;
		break;
	case DESC_RATEMCS14:
		ret_rate = MGN_MCS14;
		break;
	case DESC_RATEMCS15:
		ret_rate = MGN_MCS15;
		break;
	case DESC_RATEVHT1SS_MCS0:
		ret_rate = MGN_VHT1SS_MCS0;
		break;
	case DESC_RATEVHT1SS_MCS1:
		ret_rate = MGN_VHT1SS_MCS1;
		break;
	case DESC_RATEVHT1SS_MCS2:
		ret_rate = MGN_VHT1SS_MCS2;
		break;
	case DESC_RATEVHT1SS_MCS3:
		ret_rate = MGN_VHT1SS_MCS3;
		break;
	case DESC_RATEVHT1SS_MCS4:
		ret_rate = MGN_VHT1SS_MCS4;
		break;
	case DESC_RATEVHT1SS_MCS5:
		ret_rate = MGN_VHT1SS_MCS5;
		break;
	case DESC_RATEVHT1SS_MCS6:
		ret_rate = MGN_VHT1SS_MCS6;
		break;
	case DESC_RATEVHT1SS_MCS7:
		ret_rate = MGN_VHT1SS_MCS7;
		break;
	case DESC_RATEVHT1SS_MCS8:
		ret_rate = MGN_VHT1SS_MCS8;
		break;
	case DESC_RATEVHT1SS_MCS9:
		ret_rate = MGN_VHT1SS_MCS9;
		break;
	case DESC_RATEVHT2SS_MCS0:
		ret_rate = MGN_VHT2SS_MCS0;
		break;
	case DESC_RATEVHT2SS_MCS1:
		ret_rate = MGN_VHT2SS_MCS1;
		break;
	case DESC_RATEVHT2SS_MCS2:
		ret_rate = MGN_VHT2SS_MCS2;
		break;
	case DESC_RATEVHT2SS_MCS3:
		ret_rate = MGN_VHT2SS_MCS3;
		break;
	case DESC_RATEVHT2SS_MCS4:
		ret_rate = MGN_VHT2SS_MCS4;
		break;
	case DESC_RATEVHT2SS_MCS5:
		ret_rate = MGN_VHT2SS_MCS5;
		break;
	case DESC_RATEVHT2SS_MCS6:
		ret_rate = MGN_VHT2SS_MCS6;
		break;
	case DESC_RATEVHT2SS_MCS7:
		ret_rate = MGN_VHT2SS_MCS7;
		break;
	case DESC_RATEVHT2SS_MCS8:
		ret_rate = MGN_VHT2SS_MCS8;
		break;
	case DESC_RATEVHT2SS_MCS9:
		ret_rate = MGN_VHT2SS_MCS9;
		break;
	default:
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "HwRateToMRate8812(): Non supported Rate [%x]!!!\n",
			 rate);
		break;
	}
	return ret_rate;
}