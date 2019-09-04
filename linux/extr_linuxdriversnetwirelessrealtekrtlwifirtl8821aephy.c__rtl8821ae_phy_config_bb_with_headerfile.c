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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASEBAND_CONFIG_AGC_TAB ; 
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int /*<<< orphan*/  RTL8812AE_AGC_TAB_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8812AE_AGC_TAB_ARRAY ; 
 int /*<<< orphan*/  RTL8812AE_PHY_REG_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8812AE_PHY_REG_ARRAY ; 
 int /*<<< orphan*/  RTL8821AE_AGC_TAB_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8821AE_AGC_TAB_ARRAY ; 
 int /*<<< orphan*/  RTL8821AE_PHY_REG_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8821AE_PHY_REG_ARRAY ; 
 int __rtl8821ae_phy_config_with_headerfile (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl8821ae_config_bb_reg ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg_with_dwmask ; 

__attribute__((used)) static bool _rtl8821ae_phy_config_bb_with_headerfile(struct ieee80211_hw *hw,
						     u8 configtype)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 *array_table;
	u16 arraylen;

	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			arraylen = RTL8812AE_PHY_REG_1TARRAYLEN;
			array_table = RTL8812AE_PHY_REG_ARRAY;
		} else {
			arraylen = RTL8821AE_PHY_REG_1TARRAYLEN;
			array_table = RTL8821AE_PHY_REG_ARRAY;
		}

		return __rtl8821ae_phy_config_with_headerfile(hw,
				array_table, arraylen,
				_rtl8821ae_config_bb_reg);
	} else if (configtype == BASEBAND_CONFIG_AGC_TAB) {
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			arraylen = RTL8812AE_AGC_TAB_1TARRAYLEN;
			array_table = RTL8812AE_AGC_TAB_ARRAY;
		} else {
			arraylen = RTL8821AE_AGC_TAB_1TARRAYLEN;
			array_table = RTL8821AE_AGC_TAB_ARRAY;
		}

		return __rtl8821ae_phy_config_with_headerfile(hw,
				array_table, arraylen,
				rtl_set_bbreg_with_dwmask);
	}
	return true;
}