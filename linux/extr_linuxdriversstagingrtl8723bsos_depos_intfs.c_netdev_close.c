#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pwrctrl_priv {int bInternalAutoSuspend; scalar_t__ rf_pwrstate; int ps_flag; } ;
struct net_device {int dummy; } ;
struct adapter {int net_closed; int netif_up; int /*<<< orphan*/  bup; int /*<<< orphan*/  hw_init_completed; } ;
struct TYPE_2__ {int bandroid_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 TYPE_1__* adapter_wdev_data (struct adapter*) ; 
 scalar_t__ rf_off ; 
 scalar_t__ rf_on ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int,int) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_free_network_queue (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (struct adapter*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  rtw_netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtw_scan_abort (struct adapter*) ; 

__attribute__((used)) static int netdev_close(struct net_device *pnetdev)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);
	struct pwrctrl_priv *pwrctl = adapter_to_pwrctl(padapter);

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+871x_drv - drv_close\n"));

	if (pwrctl->bInternalAutoSuspend == true) {
		/* rtw_pwr_wakeup(padapter); */
		if (pwrctl->rf_pwrstate == rf_off)
			pwrctl->ps_flag = true;
	}
	padapter->net_closed = true;
	padapter->netif_up = false;

/*if (!padapter->hw_init_completed)
	{
		DBG_871X("(1)871x_drv - drv_close, bup =%d, hw_init_completed =%d\n", padapter->bup, padapter->hw_init_completed);

		padapter->bDriverStopped = true;

		rtw_dev_unload(padapter);
	}
	else*/
	if (pwrctl->rf_pwrstate == rf_on) {
		DBG_871X("(2)871x_drv - drv_close, bup =%d, hw_init_completed =%d\n", padapter->bup, padapter->hw_init_completed);

		/* s1. */
		if (pnetdev) {
			if (!rtw_netif_queue_stopped(pnetdev))
				rtw_netif_stop_queue(pnetdev);
		}

		/* s2. */
		LeaveAllPowerSaveMode(padapter);
		rtw_disassoc_cmd(padapter, 500, false);
		/* s2-2.  indicate disconnect to os */
		rtw_indicate_disconnect(padapter);
		/* s2-3. */
		rtw_free_assoc_resources(padapter, 1);
		/* s2-4. */
		rtw_free_network_queue(padapter, true);
	}

	rtw_scan_abort(padapter);
	adapter_wdev_data(padapter)->bandroid_scan = false;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("-871x_drv - drv_close\n"));
	DBG_871X("-871x_drv - drv_close, bup =%d\n", padapter->bup);

	return 0;
}