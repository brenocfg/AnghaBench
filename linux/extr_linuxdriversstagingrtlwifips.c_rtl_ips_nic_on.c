#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rtl_ps_ctl {int rfpwr_state; scalar_t__ rfoff_reason; int inactive_pwrstate; int in_powersavemode; int /*<<< orphan*/  swrf_processing; scalar_t__ inactiveps; } ;
struct TYPE_16__ {int /*<<< orphan*/  ips_mutex; } ;
struct TYPE_15__ {TYPE_6__* btc_ops; } ;
struct TYPE_11__ {TYPE_2__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  ips_nic_off_wq; } ;
struct rtl_priv {TYPE_8__ locks; TYPE_7__ btcoexist; TYPE_5__* cfg; TYPE_3__ phydm; TYPE_1__ works; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rf_pwrstate { ____Placeholder_rf_pwrstate } rf_pwrstate ;
struct TYPE_14__ {int /*<<< orphan*/  (* btc_ips_notify ) (struct rtl_priv*,int) ;} ;
struct TYPE_13__ {TYPE_4__* ops; } ;
struct TYPE_12__ {scalar_t__ (* get_btc_status ) () ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* phydm_reset_dm ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int ERFON ; 
 scalar_t__ RF_CHANGE_BY_IPS ; 
 int /*<<< orphan*/  _rtl_ps_inactive_ps (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*) ; 
 scalar_t__ stub2 () ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*,int) ; 

void rtl_ips_nic_on(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	enum rf_pwrstate rtstate;

	cancel_delayed_work(&rtlpriv->works.ips_nic_off_wq);

	mutex_lock(&rtlpriv->locks.ips_mutex);
	if (ppsc->inactiveps) {
		rtstate = ppsc->rfpwr_state;

		if (rtstate != ERFON &&
		    !ppsc->swrf_processing &&
		    ppsc->rfoff_reason <= RF_CHANGE_BY_IPS) {
			ppsc->inactive_pwrstate = ERFON;
			ppsc->in_powersavemode = false;
			_rtl_ps_inactive_ps(hw);
			/* call after RF on */
			if (rtlpriv->phydm.ops)
				rtlpriv->phydm.ops->phydm_reset_dm(rtlpriv);
			if (rtlpriv->cfg->ops->get_btc_status())
				rtlpriv->btcoexist.btc_ops->btc_ips_notify(rtlpriv,
									ppsc->inactive_pwrstate);
		}
	}
	mutex_unlock(&rtlpriv->locks.ips_mutex);
}