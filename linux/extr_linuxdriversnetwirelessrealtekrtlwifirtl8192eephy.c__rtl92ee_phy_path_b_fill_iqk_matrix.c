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
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  ROFDM0_AGCRSSITABLE ; 
 int /*<<< orphan*/  ROFDM0_ECCATHRESHOLD ; 
 int /*<<< orphan*/  ROFDM0_XATXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XBRXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XBTXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XDTXAFE ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void _rtl92ee_phy_path_b_fill_iqk_matrix(struct ieee80211_hw *hw,
						bool b_iqk_ok, long result[][8],
						u8 final_candidate,
						bool btxonly)
{
	u32 oldval_1, x, tx1_a, reg;
	long y, tx1_c;

	if (final_candidate == 0xFF) {
		return;
	} else if (b_iqk_ok) {
		oldval_1 = (rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
					  MASKDWORD) >> 22) & 0x3FF;
		x = result[final_candidate][4];
		if ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx1_a = (x * oldval_1) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x3FF, tx1_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(27),
			      ((x * oldval_1 >> 7) & 0x1));
		y = result[final_candidate][5];
		if ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;
		tx1_c = (y * oldval_1) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XDTXAFE, 0xF0000000,
			      ((tx1_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x003F0000,
			      (tx1_c & 0x3F));
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(25),
			      ((y * oldval_1 >> 7) & 0x1));

		if (btxonly)
			return;

		reg = result[final_candidate][6];
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0x3FF, reg);

		reg = result[final_candidate][7] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0xFC00, reg);

		reg = (result[final_candidate][7] >> 6) & 0xF;
		rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, 0xF0000000, reg);
	}
}