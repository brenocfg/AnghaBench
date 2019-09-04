#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_14__ {TYPE_1__* padapter; } ;
struct TYPE_16__ {TYPE_1__* padapter; } ;
struct TYPE_15__ {int /*<<< orphan*/  setband; TYPE_12__ stapriv; int /*<<< orphan*/  security_key_mutex; int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  xmitpriv; int /*<<< orphan*/  evtpriv; TYPE_6__ cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  GHZ24_50 ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 scalar_t__ _rtw_init_recv_priv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ _rtw_init_sta_priv (TYPE_12__*) ; 
 scalar_t__ _rtw_init_xmit_priv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ init_mlme_ext_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_hal_dm_init (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_hal_sw_led_init (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_init_bcmc_stainfo (TYPE_1__*) ; 
 scalar_t__ rtw_init_cmd_priv (TYPE_6__*) ; 
 scalar_t__ rtw_init_default_value (TYPE_1__*) ; 
 scalar_t__ rtw_init_evt_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_init_mlme_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_init_pwrctrl_priv (TYPE_1__*) ; 

u8 rtw_init_drv_sw(_adapter *padapter)
{

	u8	ret8=_SUCCESS;

_func_enter_;

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("+rtw_init_drv_sw\n"));

	if ((rtw_init_cmd_priv(&padapter->cmdpriv)) == _FAIL)
	{
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("\n Can't init cmd_priv\n"));
		ret8=_FAIL;
		goto exit;
	}

	padapter->cmdpriv.padapter=padapter;

	if ((rtw_init_evt_priv(&padapter->evtpriv)) == _FAIL)
	{
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("\n Can't init evt_priv\n"));
		ret8=_FAIL;
		goto exit;
	}


	if (rtw_init_mlme_priv(padapter) == _FAIL)
	{
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("\n Can't init mlme_priv\n"));
		ret8=_FAIL;
		goto exit;
	}

#ifdef CONFIG_P2P
	rtw_init_wifidirect_timers(padapter);
	init_wifidirect_info(padapter, P2P_ROLE_DISABLE);
	reset_global_wifidirect_info(padapter);
	#ifdef CONFIG_IOCTL_CFG80211
	rtw_init_cfg80211_wifidirect_info(padapter);
	#endif
#ifdef CONFIG_WFD
	if(rtw_init_wifi_display_info(padapter) == _FAIL)
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("\n Can't init init_wifi_display_info\n"));
#endif
#endif /* CONFIG_P2P */

	if(init_mlme_ext_priv(padapter) == _FAIL)
	{
		RT_TRACE(_module_os_intfs_c_,_drv_err_,("\n Can't init mlme_ext_priv\n"));
		ret8=_FAIL;
		goto exit;
	}

#ifdef CONFIG_TDLS
	if(rtw_init_tdls_info(padapter) == _FAIL)
	{
		DBG_871X("Can't rtw_init_tdls_info\n");
		ret8=_FAIL;
		goto exit;
	}
#endif //CONFIG_TDLS

	if(_rtw_init_xmit_priv(&padapter->xmitpriv, padapter) == _FAIL)
	{
		DBG_871X("Can't _rtw_init_xmit_priv\n");
		ret8=_FAIL;
		goto exit;
	}

	if(_rtw_init_recv_priv(&padapter->recvpriv, padapter) == _FAIL)
	{
		DBG_871X("Can't _rtw_init_recv_priv\n");
		ret8=_FAIL;
		goto exit;
	}
	// add for CONFIG_IEEE80211W, none 11w also can use
	_rtw_spinlock_init(&padapter->security_key_mutex);

	// We don't need to memset padapter->XXX to zero, because adapter is allocated by rtw_zvmalloc().
	//_rtw_memset((unsigned char *)&padapter->securitypriv, 0, sizeof (struct security_priv));

	//_init_timer(&(padapter->securitypriv.tkip_timer), padapter->pifp, rtw_use_tkipkey_handler, padapter);

	if(_rtw_init_sta_priv(&padapter->stapriv) == _FAIL)
	{
		DBG_871X("Can't _rtw_init_sta_priv\n");
		ret8=_FAIL;
		goto exit;
	}

	padapter->stapriv.padapter = padapter;
	padapter->setband = GHZ24_50;
	rtw_init_bcmc_stainfo(padapter);

	rtw_init_pwrctrl_priv(padapter);

	//_rtw_memset((u8 *)&padapter->qospriv, 0, sizeof (struct qos_priv));//move to mlme_priv

#ifdef CONFIG_MP_INCLUDED
	if (init_mp_priv(padapter) == _FAIL) {
		DBG_871X("%s: initialize MP private data Fail!\n", __func__);
	}
#endif

	ret8 = rtw_init_default_value(padapter);

	rtw_hal_dm_init(padapter);
	rtw_hal_sw_led_init(padapter);

#ifdef DBG_CONFIG_ERROR_DETECT
	rtw_hal_sreset_init(padapter);
#endif

#ifdef CONFIG_INTEL_WIDI
	if(rtw_init_intel_widi(padapter) == _FAIL)
	{
		DBG_871X("Can't rtw_init_intel_widi\n");
		ret8=_FAIL;
		goto exit;
	}
#endif //CONFIG_INTEL_WIDI

#ifdef CONFIG_BR_EXT
	_rtw_spinlock_init(&padapter->br_ext_lock);
#endif	// CONFIG_BR_EXT

exit:

	RT_TRACE(_module_os_intfs_c_,_drv_info_,("-rtw_init_drv_sw\n"));

	_func_exit_;

	return ret8;

}