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
struct rtl_ps_ctl {scalar_t__ dot11_psmode; int reg_rfps_level; scalar_t__ fwctrl_lps; } ;
struct TYPE_4__ {int /*<<< orphan*/  lps_mutex; } ;
struct rtl_priv {TYPE_2__ locks; TYPE_1__* intf_ops; } ;
struct rtl_hal {scalar_t__ interface; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_aspm ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ EACTIVE ; 
 scalar_t__ INTF_PCI ; 
 int /*<<< orphan*/  RT_CLEAR_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 scalar_t__ RT_IN_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_PS_LEVEL_ASPM ; 
 int RT_RF_LPS_LEVEL_ASPM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_lps_set_psmode (struct ieee80211_hw*,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl_lps_leave_core(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.lps_mutex);

	if (ppsc->fwctrl_lps) {
		if (ppsc->dot11_psmode != EACTIVE) {

			/*FIX ME */
			/*rtlpriv->cfg->ops->enable_interrupt(hw); */

			if (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM &&
			    RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM) &&
			    rtlhal->interface == INTF_PCI) {
				rtlpriv->intf_ops->disable_aspm(hw);
				RT_CLEAR_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
			}

			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
				 "Busy Traffic,Leave 802.11 power save..\n");

			rtl_lps_set_psmode(hw, EACTIVE);
		}
	}
	mutex_unlock(&rtlpriv->locks.lps_mutex);
}