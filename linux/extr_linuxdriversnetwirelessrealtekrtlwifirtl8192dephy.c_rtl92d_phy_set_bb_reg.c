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
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {scalar_t__ during_mac0init_radiob; scalar_t__ during_mac1init_radioa; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int _rtl92d_phy_calculate_bit_shift (int) ; 
 int rtl92de_read_dword_dbi (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92de_write_dword_dbi (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

void rtl92d_phy_set_bb_reg(struct ieee80211_hw *hw,
			   u32 regaddr, u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 dbi_direct = 0;
	u32 originalvalue, bitshift;

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), bitmask(%#x), data(%#x)\n",
		 regaddr, bitmask, data);
	if (rtlhal->during_mac1init_radioa)
		dbi_direct = BIT(3);
	else if (rtlhal->during_mac0init_radiob)
		/* mac0 use phy1 write radio_b. */
		dbi_direct = BIT(3) | BIT(2);
	if (bitmask != MASKDWORD) {
		if (rtlhal->during_mac1init_radioa ||
		    rtlhal->during_mac0init_radiob)
			originalvalue = rtl92de_read_dword_dbi(hw,
					(u16) regaddr,
					dbi_direct);
		else
			originalvalue = rtl_read_dword(rtlpriv, regaddr);
		bitshift = _rtl92d_phy_calculate_bit_shift(bitmask);
		data = ((originalvalue & (~bitmask)) | (data << bitshift));
	}
	if (rtlhal->during_mac1init_radioa || rtlhal->during_mac0init_radiob)
		rtl92de_write_dword_dbi(hw, (u16) regaddr, data, dbi_direct);
	else
		rtl_write_dword(rtlpriv, regaddr, data);
	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), bitmask(%#x), data(%#x)\n",
		 regaddr, bitmask, data);
}