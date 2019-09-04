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
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DESC92C_RATE11M 155 
#define  DESC92C_RATE12M 154 
#define  DESC92C_RATE18M 153 
#define  DESC92C_RATE1M 152 
#define  DESC92C_RATE24M 151 
#define  DESC92C_RATE2M 150 
#define  DESC92C_RATE36M 149 
#define  DESC92C_RATE48M 148 
#define  DESC92C_RATE54M 147 
#define  DESC92C_RATE5_5M 146 
#define  DESC92C_RATE6M 145 
#define  DESC92C_RATE9M 144 
#define  DESC92C_RATEMCS0 143 
#define  DESC92C_RATEMCS1 142 
#define  DESC92C_RATEMCS10 141 
#define  DESC92C_RATEMCS11 140 
#define  DESC92C_RATEMCS12 139 
#define  DESC92C_RATEMCS13 138 
#define  DESC92C_RATEMCS14 137 
#define  DESC92C_RATEMCS15 136 
#define  DESC92C_RATEMCS2 135 
#define  DESC92C_RATEMCS3 134 
#define  DESC92C_RATEMCS4 133 
#define  DESC92C_RATEMCS5 132 
#define  DESC92C_RATEMCS6 131 
#define  DESC92C_RATEMCS7 130 
#define  DESC92C_RATEMCS8 129 
#define  DESC92C_RATEMCS9 128 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKBYTE1 ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int /*<<< orphan*/  RTXAGC_A_CCK1_MCS32 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS03_MCS00 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS07_MCS04 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS11_MCS08 ; 
 int /*<<< orphan*/  RTXAGC_A_MCS15_MCS12 ; 
 int /*<<< orphan*/  RTXAGC_A_RATE18_06 ; 
 int /*<<< orphan*/  RTXAGC_A_RATE54_24 ; 
 int /*<<< orphan*/  RTXAGC_B_CCK11_A_CCK2_11 ; 
 int /*<<< orphan*/  RTXAGC_B_CCK1_55_MCS32 ; 
 int /*<<< orphan*/  RTXAGC_B_MCS03_MCS00 ; 
 int /*<<< orphan*/  RTXAGC_B_MCS07_MCS04 ; 
 int /*<<< orphan*/  RTXAGC_B_MCS11_MCS08 ; 
 int /*<<< orphan*/  RTXAGC_B_MCS15_MCS12 ; 
 int /*<<< orphan*/  RTXAGC_B_RATE18_06 ; 
 int /*<<< orphan*/  RTXAGC_B_RATE54_24 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92ee_set_txpower_index(struct ieee80211_hw *hw, u8 pwr_idx,
				       enum radio_path rfpath, u8 rate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (rfpath == RF90_PATH_A) {
		switch (rate) {
		case DESC92C_RATE1M:
			rtl_set_bbreg(hw, RTXAGC_A_CCK1_MCS32, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE2M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE5_5M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATE11M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATE6M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATE9M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE12M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATE18M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATE24M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATE36M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE48M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATE54M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS0:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS1:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS2:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS3:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS4:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS5:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS6:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS7:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS8:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS9:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS10:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS11:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS12:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS13:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS14:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS15:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE3,
				      pwr_idx);
			break;
		default:
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "Invalid Rate!!\n");
			break;
		}
	} else if (rfpath == RF90_PATH_B) {
		switch (rate) {
		case DESC92C_RATE1M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE2M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATE5_5M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATE11M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATE6M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATE9M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE12M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATE18M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATE24M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATE36M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATE48M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATE54M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS0:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS1:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS2:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS3:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS4:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS5:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS6:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS7:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS8:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS9:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS10:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS11:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE3,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS12:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE0,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS13:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE1,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS14:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE2,
				      pwr_idx);
			break;
		case DESC92C_RATEMCS15:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE3,
				      pwr_idx);
			break;
		default:
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "Invalid Rate!!\n");
			break;
		}
	} else {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid RFPath!!\n");
	}
}