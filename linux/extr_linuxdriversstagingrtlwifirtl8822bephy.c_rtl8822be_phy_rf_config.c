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
struct rtl_phy {scalar_t__ rf_type; int num_total_rfpath; } ;
struct rtl_priv {TYPE_2__ phydm; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int (* phydm_phy_rf_config ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 scalar_t__ RF_1T1R ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct rtl_priv*) ; 

bool rtl8822be_phy_rf_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	if (rtlphy->rf_type == RF_1T1R)
		rtlphy->num_total_rfpath = 1;
	else
		rtlphy->num_total_rfpath = 2;

	return rtlpriv->phydm.ops->phydm_phy_rf_config(rtlpriv);
}