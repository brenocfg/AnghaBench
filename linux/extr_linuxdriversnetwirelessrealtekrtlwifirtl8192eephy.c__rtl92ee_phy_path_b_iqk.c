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
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IQK_DELAY_TIME ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RF90_PATH_B ; 
 int RFPGA0_IQK ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int RIQK_AGC_PTS ; 
 int RIQK_AGC_RSP ; 
 int RRX_IQK_PI_B ; 
 int RRX_IQK_TONE_A ; 
 int RRX_IQK_TONE_B ; 
 int RTX_IQK_PI_B ; 
 int RTX_IQK_TONE_A ; 
 int RTX_IQK_TONE_B ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 _rtl92ee_phy_path_b_iqk(struct ieee80211_hw *hw)
{
	u32 reg_eac, reg_eb4, reg_ebc;
	u8 result = 0x00;

	/* PA/PAD controlled by 0x0 */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_B, 0xdf, RFREG_OFFSET_MASK, 0x180);
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x00000000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);

	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x821403e2);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x68160000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x00462911);

	/*One shot, path B LOK & IQK*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xfa000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_eb4 = rtl_get_bbreg(hw, 0xeb4, MASKDWORD);
	reg_ebc = rtl_get_bbreg(hw, 0xebc, MASKDWORD);

	if (!(reg_eac & BIT(31)) &&
	    (((reg_eb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_ebc & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else
		return result;

	return result;
}