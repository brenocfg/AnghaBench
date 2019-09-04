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
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 _rtl8723e_phy_path_a_iqk(struct ieee80211_hw *hw, bool config_pathb)
{
	u32 reg_eac, reg_e94, reg_e9c, reg_ea4;
	u8 result = 0x00;

	rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x10008c1f);
	rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x10008c1f);
	rtl_set_bbreg(hw, 0xe38, MASKDWORD, 0x82140102);
	rtl_set_bbreg(hw, 0xe3c, MASKDWORD,
		      config_pathb ? 0x28160202 : 0x28160502);

	if (config_pathb) {
		rtl_set_bbreg(hw, 0xe50, MASKDWORD, 0x10008c22);
		rtl_set_bbreg(hw, 0xe54, MASKDWORD, 0x10008c22);
		rtl_set_bbreg(hw, 0xe58, MASKDWORD, 0x82140102);
		rtl_set_bbreg(hw, 0xe5c, MASKDWORD, 0x28160202);
	}

	rtl_set_bbreg(hw, 0xe4c, MASKDWORD, 0x001028d1);
	rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);
	reg_ea4 = rtl_get_bbreg(hw, 0xea4, MASKDWORD);

	if (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else
		return result;

	if (!(reg_eac & BIT(27)) &&
	    (((reg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_eac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	return result;
}