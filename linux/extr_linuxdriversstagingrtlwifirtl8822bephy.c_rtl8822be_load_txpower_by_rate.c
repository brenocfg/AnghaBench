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
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int (* phydm_load_txpower_by_rate ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8822be_phy_init_tx_power_by_rate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_phy_txpower_by_rate_configuration (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct rtl_priv*) ; 

bool rtl8822be_load_txpower_by_rate(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	bool rtstatus = true;

	_rtl8822be_phy_init_tx_power_by_rate(hw);

	rtstatus = rtlpriv->phydm.ops->phydm_load_txpower_by_rate(rtlpriv);

	if (!rtstatus) {
		pr_err("BB_PG Reg Fail!!\n");
		return false;
	}

	_rtl8822be_phy_txpower_by_rate_configuration(hw);

	return true;
}