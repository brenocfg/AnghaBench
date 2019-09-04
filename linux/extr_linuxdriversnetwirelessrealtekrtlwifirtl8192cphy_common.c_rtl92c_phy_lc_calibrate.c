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
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_lc_calibrate ) (struct ieee80211_hw*,int) ;} ;

/* Variables and functions */
 scalar_t__ IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int) ; 

void rtl92c_phy_lc_calibrate(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (IS_92C_SERIAL(rtlhal->version))
		rtlpriv->cfg->ops->phy_lc_calibrate(hw, true);
	else
		rtlpriv->cfg->ops->phy_lc_calibrate(hw, false);
}