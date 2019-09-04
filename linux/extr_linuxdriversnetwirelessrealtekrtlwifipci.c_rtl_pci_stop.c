#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_ps_ctl {int rfchange_inprogress; } ;
struct TYPE_12__ {int /*<<< orphan*/  rf_ps_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  lps_change_work; } ;
struct TYPE_8__ {TYPE_1__* btc_ops; } ;
struct rtl_priv {TYPE_6__ locks; TYPE_5__* cfg; int /*<<< orphan*/  max_fw_size; TYPE_3__ works; TYPE_2__ btcoexist; } ;
struct rtl_pci {int driver_is_goingto_unload; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_11__ {TYPE_4__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hw_disable ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* disable_interrupt ) (struct ieee80211_hw*) ;scalar_t__ (* get_btc_status ) () ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* btc_deinit_variables ) (struct rtl_priv*) ;int /*<<< orphan*/  (* btc_halt_notify ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_pci_enable_aspm (struct ieee80211_hw*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  set_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_pci_stop(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	unsigned long flags;
	u8 rf_timeout = 0;

	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_halt_notify(rtlpriv);

	if (rtlpriv->btcoexist.btc_ops)
		rtlpriv->btcoexist.btc_ops->btc_deinit_variables(rtlpriv);

	/*should be before disable interrupt&adapter
	 *and will do it immediately.
	 */
	set_hal_stop(rtlhal);

	rtlpci->driver_is_goingto_unload = true;
	rtlpriv->cfg->ops->disable_interrupt(hw);
	cancel_work_sync(&rtlpriv->works.lps_change_work);

	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
	while (ppsc->rfchange_inprogress) {
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flags);
		if (rf_timeout > 100) {
			spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
			break;
		}
		mdelay(1);
		rf_timeout++;
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
	}
	ppsc->rfchange_inprogress = true;
	spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flags);

	rtlpriv->cfg->ops->hw_disable(hw);
	/* some things are not needed if firmware not available */
	if (!rtlpriv->max_fw_size)
		return;
	rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);

	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flags);
	ppsc->rfchange_inprogress = false;
	spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flags);

	rtl_pci_enable_aspm(hw);
}