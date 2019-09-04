#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_9__ {scalar_t__ bInternalAutoSuspend; scalar_t__ rf_pwrstate; scalar_t__ ps_flag; } ;
struct TYPE_10__ {int /*<<< orphan*/  bup; int /*<<< orphan*/  hw_init_completed; TYPE_1__ pwrctrlpriv; scalar_t__ net_closed; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (TYPE_2__*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 scalar_t__ rf_off ; 
 scalar_t__ rf_on ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rtw_free_network_queue (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_led_control (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  rtw_netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int netdev_close(struct net_device *pnetdev)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(pnetdev);

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("+871x_drv - drv_close\n"));

	if(padapter->pwrctrlpriv.bInternalAutoSuspend == _TRUE)
	{
		//rtw_pwr_wakeup(padapter);
		if(padapter->pwrctrlpriv.rf_pwrstate == rf_off)
			padapter->pwrctrlpriv.ps_flag = _TRUE;
	}
	padapter->net_closed = _TRUE;

/*	if(!padapter->hw_init_completed)
	{
		DBG_871X("(1)871x_drv - drv_close, bup=%d, hw_init_completed=%d\n", padapter->bup, padapter->hw_init_completed);

		padapter->bDriverStopped = _TRUE;

		rtw_dev_unload(padapter);
	}
	else*/
	if(padapter->pwrctrlpriv.rf_pwrstate == rf_on){
		DBG_871X("(2)871x_drv - drv_close, bup=%d, hw_init_completed=%d\n", padapter->bup, padapter->hw_init_completed);

		//s1.
		if(pnetdev)
		{
			if (!rtw_netif_queue_stopped(pnetdev))
				rtw_netif_stop_queue(pnetdev);
		}

#ifndef CONFIG_ANDROID
		//s2.
		LeaveAllPowerSaveMode(padapter);
		rtw_disassoc_cmd(padapter, 500, _FALSE);
		//s2-2.  indicate disconnect to os
		rtw_indicate_disconnect(padapter);
		//s2-3.
		rtw_free_assoc_resources(padapter, 1);
		//s2-4.
		rtw_free_network_queue(padapter,_TRUE);
#endif
		// Close LED
		rtw_led_control(padapter, LED_CTL_POWER_OFF);
	}

#ifdef CONFIG_BR_EXT
	//if (OPMODE & (WIFI_STATION_STATE | WIFI_ADHOC_STATE))
	{
		//void nat25_db_cleanup(_adapter *priv);
		nat25_db_cleanup(padapter);
	}
#endif	// CONFIG_BR_EXT

#ifdef CONFIG_P2P
#ifdef CONFIG_IOCTL_CFG80211
	if( padapter->wdinfo.driver_interface == DRIVER_CFG80211 )
	{
		if(wdev_to_priv(padapter->rtw_wdev)->p2p_enabled == _TRUE)
			wdev_to_priv(padapter->rtw_wdev)->p2p_enabled = _FALSE;
	}
#endif //CONFIG_IOCTL_CFG80211
	rtw_p2p_enable(padapter, P2P_ROLE_DISABLE);
#endif //CONFIG_P2P

#ifdef CONFIG_IOCTL_CFG80211
	rtw_scan_abort(padapter);
	wdev_to_priv(padapter->rtw_wdev)->bandroid_scan = _FALSE;
	padapter->rtw_wdev->iftype = NL80211_IFTYPE_MONITOR; //set this at the end
#endif //CONFIG_IOCTL_CFG80211

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("-871x_drv - drv_close\n"));
	DBG_871X("-871x_drv - drv_close, bup=%d\n", padapter->bup);

	return 0;
}