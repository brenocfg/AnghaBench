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
typedef  int u32 ;
struct rtl_phy {scalar_t__ rf_mode; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int RFREG_OFFSET_MASK ; 
 scalar_t__ RF_OP_BY_FW ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int _rtl92c_phy_calculate_bit_shift (int) ; 
 int _rtl92c_phy_fw_rf_serial_read (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl92c_phy_fw_rf_serial_write (struct ieee80211_hw*,int,int,int) ; 
 int _rtl92c_phy_rf_serial_read (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl92c_phy_rf_serial_write (struct ieee80211_hw*,int,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92cu_phy_set_rf_reg(struct ieee80211_hw *hw,
			    enum radio_path rfpath,
			    u32 regaddr, u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 original_value, bitshift;

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		 regaddr, bitmask, data, rfpath);
	if (rtlphy->rf_mode != RF_OP_BY_FW) {
		if (bitmask != RFREG_OFFSET_MASK) {
			original_value = _rtl92c_phy_rf_serial_read(hw,
								    rfpath,
								    regaddr);
			bitshift = _rtl92c_phy_calculate_bit_shift(bitmask);
			data =
			    ((original_value & (~bitmask)) |
			     (data << bitshift));
		}
		_rtl92c_phy_rf_serial_write(hw, rfpath, regaddr, data);
	} else {
		if (bitmask != RFREG_OFFSET_MASK) {
			original_value = _rtl92c_phy_fw_rf_serial_read(hw,
								       rfpath,
								       regaddr);
			bitshift = _rtl92c_phy_calculate_bit_shift(bitmask);
			data =
			    ((original_value & (~bitmask)) |
			     (data << bitshift));
		}
		_rtl92c_phy_fw_rf_serial_write(hw, rfpath, regaddr, data);
	}
	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		 regaddr, bitmask, data, rfpath);
}