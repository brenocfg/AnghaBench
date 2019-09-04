#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  conf_mutex; } ;
struct rtl_priv {TYPE_4__ locks; TYPE_3__* intf_ops; TYPE_2__* cfg; } ;
struct rtl_mac {int /*<<< orphan*/  vendor; int /*<<< orphan*/  bssid; int /*<<< orphan*/  link_state; } ;
struct rtl_hal {scalar_t__ enter_pnp_sleep; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* adapter_stop ) (struct ieee80211_hw*) ;} ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ ERFOFF ; 
 int /*<<< orphan*/  HAL_DEF_WOWLAN ; 
 int /*<<< orphan*/  MAC80211_NOLINK ; 
 int /*<<< orphan*/  PEER_UNKNOWN ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_cam_reset_sec_info (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_deinit_deferred_work (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_ips_nic_on (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rtl_op_stop(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool support_remote_wakeup = false;

	if (is_hal_stop(rtlhal))
		return;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));
	/* here is must, because adhoc do stop and start,
	 * but stop with RFOFF may cause something wrong,
	 * like adhoc TP
	 */
	if (unlikely(ppsc->rfpwr_state == ERFOFF))
		rtl_ips_nic_on(hw);

	mutex_lock(&rtlpriv->locks.conf_mutex);
	/* if wowlan supported, DON'T clear connected info */
	if (!(support_remote_wakeup &&
	      rtlhal->enter_pnp_sleep)) {
		mac->link_state = MAC80211_NOLINK;
		eth_zero_addr(mac->bssid);
		mac->vendor = PEER_UNKNOWN;

		/* reset sec info */
		rtl_cam_reset_sec_info(hw);

		rtl_deinit_deferred_work(hw, false);
	}
	rtlpriv->intf_ops->adapter_stop(hw);

	mutex_unlock(&rtlpriv->locks.conf_mutex);
}