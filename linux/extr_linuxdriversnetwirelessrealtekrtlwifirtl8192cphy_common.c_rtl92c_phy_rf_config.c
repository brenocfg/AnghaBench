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
struct rtl_priv {TYPE_2__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* phy_rf6052_config ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct ieee80211_hw*) ; 

bool rtl92c_phy_rf_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	return rtlpriv->cfg->ops->phy_rf6052_config(hw);
}