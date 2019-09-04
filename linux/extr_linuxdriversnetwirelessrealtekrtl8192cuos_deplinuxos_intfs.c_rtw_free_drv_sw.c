#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/ * old_pnetdev; } ;
struct TYPE_9__ {TYPE_2__* pbuddy_adapter; TYPE_1__ rereg_nd_name_priv; int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  stapriv; int /*<<< orphan*/  xmitpriv; int /*<<< orphan*/  mlmepriv; int /*<<< orphan*/  evtpriv; int /*<<< orphan*/  cmdpriv; int /*<<< orphan*/  mlmeextpriv; int /*<<< orphan*/  security_key_mutex; } ;
typedef  TYPE_3__ _adapter ;
struct TYPE_8__ {int /*<<< orphan*/ * pbuddy_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  _rtw_free_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_sta_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mlme_ext_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_cmd_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_evt_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_mlme_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_pwrctrl_priv (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_hal_free_data (TYPE_3__*) ; 

u8 rtw_free_drv_sw(_adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_,_drv_info_,("==>rtw_free_drv_sw"));


	//we can call rtw_p2p_enable here, but:
	// 1. rtw_p2p_enable may have IO operation
	// 2. rtw_p2p_enable is bundled with wext interface
	#ifdef CONFIG_P2P
	{
		struct wifidirect_info *pwdinfo = &padapter->wdinfo;
		if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
		{
			_cancel_timer_ex( &pwdinfo->find_phase_timer );
			_cancel_timer_ex( &pwdinfo->restore_p2p_state_timer );
			_cancel_timer_ex( &pwdinfo->pre_tx_scan_timer);
#ifdef CONFIG_CONCURRENT_MODE
			_cancel_timer_ex( &pwdinfo->ap_p2p_switch_timer );
#endif // CONFIG_CONCURRENT_MODE
			rtw_p2p_set_state(pwdinfo, P2P_STATE_NONE);
		}
	}
	#endif
	// add for CONFIG_IEEE80211W, none 11w also can use
	_rtw_spinlock_free(&padapter->security_key_mutex);

#ifdef CONFIG_BR_EXT
	_rtw_spinlock_free(&padapter->br_ext_lock);
#endif	// CONFIG_BR_EXT

#ifdef CONFIG_INTEL_WIDI
	rtw_free_intel_widi(padapter);
#endif //CONFIG_INTEL_WIDI

	free_mlme_ext_priv(&padapter->mlmeextpriv);

#ifdef CONFIG_TDLS
	//rtw_free_tdls_info(&padapter->tdlsinfo);
#endif //CONFIG_TDLS

	rtw_free_cmd_priv(&padapter->cmdpriv);

	rtw_free_evt_priv(&padapter->evtpriv);

	rtw_free_mlme_priv(&padapter->mlmepriv);

	//free_io_queue(padapter);

	_rtw_free_xmit_priv(&padapter->xmitpriv);

	_rtw_free_sta_priv(&padapter->stapriv); //will free bcmc_stainfo here

	_rtw_free_recv_priv(&padapter->recvpriv);

	rtw_free_pwrctrl_priv(padapter);

	//rtw_mfree((void *)padapter, sizeof (padapter));

#ifdef CONFIG_DRVEXT_MODULE
	free_drvext(&padapter->drvextpriv);
#endif

	rtw_hal_free_data(padapter);

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("<==rtw_free_drv_sw\n"));

	//free the old_pnetdev
	if(padapter->rereg_nd_name_priv.old_pnetdev) {
		free_netdev(padapter->rereg_nd_name_priv.old_pnetdev);
		padapter->rereg_nd_name_priv.old_pnetdev = NULL;
	}

	// clear pbuddy_adapter to avoid access wrong pointer.
	if(padapter->pbuddy_adapter != NULL)
	{
		padapter->pbuddy_adapter->pbuddy_adapter = NULL;
	}

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("-rtw_free_drv_sw\n"));

	return _SUCCESS;

}