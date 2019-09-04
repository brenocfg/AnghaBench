#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  irq_tasklet; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ works; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hw_disable ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* disable_interrupt ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_deinit_deferred_work (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

bool rtl_ps_disable_nic(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	/*<1> Stop all timer */
	rtl_deinit_deferred_work(hw, true);

	/*<2> Disable Interrupt */
	rtlpriv->cfg->ops->disable_interrupt(hw);
	tasklet_kill(&rtlpriv->works.irq_tasklet);

	/*<3> Disable Adapter */
	rtlpriv->cfg->ops->hw_disable(hw);

	return true;
}