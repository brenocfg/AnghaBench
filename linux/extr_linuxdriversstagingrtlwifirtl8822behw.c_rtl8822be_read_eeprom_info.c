#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int* rfpath_rxenable; } ;
struct rtl_phy {int* rfpath_rx_enable; scalar_t__ rf_type; } ;
struct rtl_priv {TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_phydm_params {int mp_chip; int fab_ver; int /*<<< orphan*/  cut_ver; } ;
struct rtl_hal {int version; } ;
struct rtl_efuse {int autoload_failflag; int /*<<< orphan*/  epromtype; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BIT_GET_CHIP_VER_8822B (int) ; 
 int BIT_GET_VENDOR_ID_8822B (int) ; 
 int BIT_RTL_ID_8822B ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  EEPROM_93C46 ; 
 int /*<<< orphan*/  EEPROM_BOOT_EFUSE ; 
 int /*<<< orphan*/  REG_SYS_EEPROM_CTRL_8822B ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8822be_hal_customized_behavior (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_read_adapter_info (struct ieee80211_hw*) ; 
 int _rtl8822be_read_chip_version (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_read_pa_bias (struct ieee80211_hw*,struct rtl_phydm_params*) ; 
 scalar_t__ get_rf_type (struct rtl_phy*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 

void rtl8822be_read_eeprom_info(struct ieee80211_hw *hw,
				struct rtl_phydm_params *params)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp_u1b;

	rtlhal->version = _rtl8822be_read_chip_version(hw);

	params->mp_chip = (rtlhal->version & BIT_RTL_ID_8822B) ? 0 : 1;
	params->fab_ver = BIT_GET_VENDOR_ID_8822B(rtlhal->version) >> 2;
	params->cut_ver = BIT_GET_CHIP_VER_8822B(rtlhal->version);

	/* fab_ver mapping */
	if (params->fab_ver == 2)
		params->fab_ver = 1;
	else if (params->fab_ver == 1)
		params->fab_ver = 2;

	/* read PA bias: params->efuse0x3d7/efuse0x3d8 */
	_rtl8822be_read_pa_bias(hw, params);

	if (get_rf_type(rtlphy) == RF_1T1R)
		rtlpriv->dm.rfpath_rxenable[0] = true;
	else
		rtlpriv->dm.rfpath_rxenable[0] =
			rtlpriv->dm.rfpath_rxenable[1] = true;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "VersionID = 0x%4x\n",
		 rtlhal->version);
	tmp_u1b = rtl_read_byte(rtlpriv, REG_SYS_EEPROM_CTRL_8822B);
	if (tmp_u1b & BIT(4)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EEPROM\n");
		rtlefuse->epromtype = EEPROM_93C46;
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from EFUSE\n");
		rtlefuse->epromtype = EEPROM_BOOT_EFUSE;
	}
	if (tmp_u1b & BIT(5)) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload OK\n");
		rtlefuse->autoload_failflag = false;
		_rtl8822be_read_adapter_info(hw);
	} else {
		pr_err("Autoload ERR!!\n");
	}
	_rtl8822be_hal_customized_behavior(hw);

	rtlphy->rfpath_rx_enable[0] = true;
	if (rtlphy->rf_type == RF_2T2R)
		rtlphy->rfpath_rx_enable[1] = true;
}