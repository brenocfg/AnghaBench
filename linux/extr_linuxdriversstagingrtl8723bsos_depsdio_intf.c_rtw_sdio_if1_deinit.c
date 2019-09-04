#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct adapter {scalar_t__ rtw_wdev; int /*<<< orphan*/  hw_init_completed; struct mlme_priv mlmepriv; struct net_device* pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mlme_ap_info (struct adapter*) ; 
 int /*<<< orphan*/  rtw_cancel_all_timer (struct adapter*) ; 
 int /*<<< orphan*/  rtw_dev_unload (struct adapter*) ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_free_drv_sw (struct adapter*) ; 
 int /*<<< orphan*/  rtw_free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rtw_wdev_free (scalar_t__) ; 

__attribute__((used)) static void rtw_sdio_if1_deinit(struct adapter *if1)
{
	struct net_device *pnetdev = if1->pnetdev;
	struct mlme_priv *pmlmepriv = &if1->mlmepriv;

	if (check_fwstate(pmlmepriv, _FW_LINKED))
		rtw_disassoc_cmd(if1, 0, false);

	free_mlme_ap_info(if1);

#ifdef CONFIG_GPIO_WAKEUP
	gpio_hostwakeup_free_irq(if1);
#endif

	rtw_cancel_all_timer(if1);

#ifdef CONFIG_WOWLAN
	adapter_to_pwrctl(if1)->wowlan_mode =false;
	DBG_871X_LEVEL(_drv_always_, "%s wowlan_mode:%d\n", __func__, adapter_to_pwrctl(if1)->wowlan_mode);
#endif /* CONFIG_WOWLAN */

	rtw_dev_unload(if1);
	DBG_871X("+r871xu_dev_remove, hw_init_completed =%d\n", if1->hw_init_completed);

	if (if1->rtw_wdev) {
		rtw_wdev_free(if1->rtw_wdev);
	}

	rtw_free_drv_sw(if1);

	if (pnetdev)
		rtw_free_netdev(pnetdev);
}