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
 int /*<<< orphan*/  RF90_PATH_A ; 
 int RFPGA0_IQK ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RF_RCK_OS ; 
 int /*<<< orphan*/  RF_TXPA_G1 ; 
 int /*<<< orphan*/  RF_TXPA_G2 ; 
 int /*<<< orphan*/  RF_WE_LUT ; 
 int RIQK_AGC_PTS ; 
 int RIQK_AGC_RSP ; 
 int RRX_IQK ; 
 int RRX_IQK_PI_A ; 
 int RRX_IQK_PI_B ; 
 int RRX_IQK_TONE_A ; 
 int RRX_IQK_TONE_B ; 
 int RTX_IQK ; 
 int RTX_IQK_PI_A ; 
 int RTX_IQK_PI_B ; 
 int RTX_IQK_TONE_A ; 
 int RTX_IQK_TONE_B ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 _rtl8723be_phy_path_a_iqk(struct ieee80211_hw *hw)
{
	u32 reg_eac, reg_e94, reg_e9c, tmp;
	u8 result = 0x00;

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	/* switch to path A */
	rtl_set_bbreg(hw, 0x948, MASKDWORD, 0x00000000);
	/* enable path A PA in TXIQK mode */
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x20000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0003f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xc7f87);

	/* 1. TX IQK */
	/* path-A IQK setting */
	/* IQK setting */
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);
	/* path-A IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x821403ea);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28160000);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);
	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x00462911);
	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path A LOK & IQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);

	if (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else /* if Tx not OK, ignore Rx */
		return result;

	/* Allen 20131125 */
	tmp = (reg_e9c & 0x03FF0000) >> 16;
	if ((tmp & 0x200) > 0)
		tmp = 0x400 - tmp;

	if (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) < 0x110) &&
	    (((reg_e94 & 0x03FF0000) >> 16) > 0xf0) &&
	    (tmp < 0xf))
		result |= 0x01;
	else /* if Tx not OK, ignore Rx */
		return result;

	return result;
}