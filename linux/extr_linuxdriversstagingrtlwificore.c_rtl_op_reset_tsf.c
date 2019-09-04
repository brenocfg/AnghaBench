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
typedef  scalar_t__ u8 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_DUAL_TSF_RST ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void rtl_op_reset_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tmp = 0;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_DUAL_TSF_RST, (u8 *)(&tmp));
}