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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RTL8723BEMAC_1T_ARRAY ; 
 int /*<<< orphan*/  RTL8723BEMAC_1T_ARRAYLEN ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rtl8723be_phy_config_with_headerfile (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte_with_val32 ; 

__attribute__((used)) static bool _rtl8723be_phy_config_mac_with_headerfile(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "Read rtl8723beMACPHY_Array\n");

	return rtl8723be_phy_config_with_headerfile(hw,
			RTL8723BEMAC_1T_ARRAY, RTL8723BEMAC_1T_ARRAYLEN,
			rtl_write_byte_with_val32);
}