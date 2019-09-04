#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_2__ phydm; } ;
struct rtl_efuse {int eeprom_regulatory; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int (* phydm_load_txpower_limit ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8822be_phy_convert_txpower_limit_to_power_index (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_phy_init_txpower_limit (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct rtl_priv*) ; 

bool rtl8822be_load_txpower_limit(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	bool rtstatus = true;

	_rtl8822be_phy_init_txpower_limit(hw);

	if (rtlefuse->eeprom_regulatory == 1)
		;
	else
		return true;

	rtstatus = rtlpriv->phydm.ops->phydm_load_txpower_limit(rtlpriv);

	if (!rtstatus) {
		pr_err("RF TxPwr Limit Fail!!\n");
		return false;
	}

	_rtl8822be_phy_convert_txpower_limit_to_power_index(hw);

	return true;
}