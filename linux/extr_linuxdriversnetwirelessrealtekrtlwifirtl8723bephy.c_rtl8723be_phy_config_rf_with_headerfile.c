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
struct rtl_hal {int /*<<< orphan*/  oem_id; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  RTL8723BE_RADIOA_1TARRAY ; 
 int /*<<< orphan*/  RTL8723BE_RADIOA_1TARRAYLEN ; 
 int /*<<< orphan*/  RT_CID_819X_HP ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _rtl8723be_config_rf_radio_a (struct ieee80211_hw*,int,int) ; 
 int rtl8723be_phy_config_with_headerfile (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct ieee80211_hw*,int,int)) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl8723be_phy_config_rf_with_headerfile(struct ieee80211_hw *hw,
					     enum radio_path rfpath)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool ret = true;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	switch (rfpath) {
	case RF90_PATH_A:
		ret =  rtl8723be_phy_config_with_headerfile(hw,
				RTL8723BE_RADIOA_1TARRAY,
				RTL8723BE_RADIOA_1TARRAYLEN,
				_rtl8723be_config_rf_radio_a);

		if (rtlhal->oem_id == RT_CID_819X_HP)
			_rtl8723be_config_rf_radio_a(hw, 0x52, 0x7E4BD);
		break;
	case RF90_PATH_B:
	case RF90_PATH_C:
		break;
	case RF90_PATH_D:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
			 "switch case %#x not processed\n", rfpath);
		break;
	}
	return ret;
}