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
struct rtl_phy {int current_channel; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_dm {int tx_rate; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTL8821AE_RX_HAL_IS_CCK_RATE (int) ; 
 int* rtl8812ae_delta_swing_table_idx_24ga_n ; 
 int* rtl8812ae_delta_swing_table_idx_24ga_p ; 
 int* rtl8812ae_delta_swing_table_idx_24gb_n ; 
 int* rtl8812ae_delta_swing_table_idx_24gb_p ; 
 int* rtl8812ae_delta_swing_table_idx_24gccka_n ; 
 int* rtl8812ae_delta_swing_table_idx_24gccka_p ; 
 int* rtl8812ae_delta_swing_table_idx_24gcckb_n ; 
 int* rtl8812ae_delta_swing_table_idx_24gcckb_p ; 
 int** rtl8812ae_delta_swing_table_idx_5ga_n ; 
 int** rtl8812ae_delta_swing_table_idx_5ga_p ; 
 int** rtl8812ae_delta_swing_table_idx_5gb_n ; 
 int** rtl8812ae_delta_swing_table_idx_5gb_p ; 
 scalar_t__ rtl8818e_delta_swing_table_idx_24gb_n ; 
 scalar_t__ rtl8818e_delta_swing_table_idx_24gb_p ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8812ae_get_delta_swing_table(struct ieee80211_hw *hw,
					    u8 **up_a, u8 **down_a,
					    u8 **up_b, u8 **down_b)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 channel = rtlphy->current_channel;
	u8 rate = rtldm->tx_rate;

	if (1 <= channel && channel <= 14) {
		if (RTL8821AE_RX_HAL_IS_CCK_RATE(rate)) {
			*up_a = rtl8812ae_delta_swing_table_idx_24gccka_p;
			*down_a = rtl8812ae_delta_swing_table_idx_24gccka_n;
			*up_b = rtl8812ae_delta_swing_table_idx_24gcckb_p;
			*down_b = rtl8812ae_delta_swing_table_idx_24gcckb_n;
		} else {
			*up_a = rtl8812ae_delta_swing_table_idx_24ga_p;
			*down_a = rtl8812ae_delta_swing_table_idx_24ga_n;
			*up_b = rtl8812ae_delta_swing_table_idx_24gb_p;
			*down_b = rtl8812ae_delta_swing_table_idx_24gb_n;
		}
	} else if (36 <= channel && channel <= 64) {
		*up_a = rtl8812ae_delta_swing_table_idx_5ga_p[0];
		*down_a = rtl8812ae_delta_swing_table_idx_5ga_n[0];
		*up_b = rtl8812ae_delta_swing_table_idx_5gb_p[0];
		*down_b = rtl8812ae_delta_swing_table_idx_5gb_n[0];
	} else if (100 <= channel && channel <= 140) {
		*up_a = rtl8812ae_delta_swing_table_idx_5ga_p[1];
		*down_a = rtl8812ae_delta_swing_table_idx_5ga_n[1];
		*up_b = rtl8812ae_delta_swing_table_idx_5gb_p[1];
		*down_b = rtl8812ae_delta_swing_table_idx_5gb_n[1];
	} else if (149 <= channel && channel <= 173) {
		*up_a = rtl8812ae_delta_swing_table_idx_5ga_p[2];
		*down_a = rtl8812ae_delta_swing_table_idx_5ga_n[2];
		*up_b = rtl8812ae_delta_swing_table_idx_5gb_p[2];
		*down_b = rtl8812ae_delta_swing_table_idx_5gb_n[2];
	} else {
	    *up_a = (u8 *)rtl8818e_delta_swing_table_idx_24gb_p;
	    *down_a = (u8 *)rtl8818e_delta_swing_table_idx_24gb_n;
	    *up_b = (u8 *)rtl8818e_delta_swing_table_idx_24gb_p;
	    *down_b = (u8 *)rtl8818e_delta_swing_table_idx_24gb_n;
	}
}