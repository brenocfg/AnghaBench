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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  MASKH4BITS ; 
#define  RF90_PATH_A 129 
#define  RF90_PATH_B 128 
 int /*<<< orphan*/  ROFDM0_ECCATHRESHOLD ; 
 int /*<<< orphan*/  ROFDM0_XATXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XBTXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XCTXAFE ; 
 int /*<<< orphan*/  ROFDM0_XDTXAFE ; 
 int* ofdmswing_table ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl88e_set_iqk_matrix(struct ieee80211_hw *hw,
				  u8 ofdm_index, u8 rfpath,
				  long iqk_result_x, long iqk_result_y)
{
	long ele_a = 0, ele_d, ele_c = 0, value32;

	ele_d = (ofdmswing_table[ofdm_index] & 0xFFC00000)>>22;

	if (iqk_result_x != 0) {
		if ((iqk_result_x & 0x00000200) != 0)
			iqk_result_x = iqk_result_x | 0xFFFFFC00;
		ele_a = ((iqk_result_x * ele_d)>>8)&0x000003FF;

		if ((iqk_result_y & 0x00000200) != 0)
			iqk_result_y = iqk_result_y | 0xFFFFFC00;
		ele_c = ((iqk_result_y * ele_d)>>8)&0x000003FF;

		switch (rfpath) {
		case RF90_PATH_A:
			value32 = (ele_d << 22)|((ele_c & 0x3F)<<16) | ele_a;
			rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
				      MASKDWORD, value32);
			value32 = (ele_c & 0x000003C0) >> 6;
			rtl_set_bbreg(hw, ROFDM0_XCTXAFE, MASKH4BITS,
				      value32);
			value32 = ((iqk_result_x * ele_d) >> 7) & 0x01;
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(24),
				      value32);
			break;
		case RF90_PATH_B:
			value32 = (ele_d << 22)|((ele_c & 0x3F)<<16) | ele_a;
			rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, MASKDWORD,
				      value32);
			value32 = (ele_c & 0x000003C0) >> 6;
			rtl_set_bbreg(hw, ROFDM0_XDTXAFE, MASKH4BITS, value32);
			value32 = ((iqk_result_x * ele_d) >> 7) & 0x01;
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(28),
				      value32);
			break;
		default:
			break;
		}
	} else {
		switch (rfpath) {
		case RF90_PATH_A:
			rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
				      MASKDWORD, ofdmswing_table[ofdm_index]);
			rtl_set_bbreg(hw, ROFDM0_XCTXAFE,
				      MASKH4BITS, 0x00);
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
				      BIT(24), 0x00);
			break;
		case RF90_PATH_B:
			rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE,
				      MASKDWORD, ofdmswing_table[ofdm_index]);
			rtl_set_bbreg(hw, ROFDM0_XDTXAFE,
				      MASKH4BITS, 0x00);
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
				      BIT(28), 0x00);
			break;
		default:
			break;
		}
	}
}