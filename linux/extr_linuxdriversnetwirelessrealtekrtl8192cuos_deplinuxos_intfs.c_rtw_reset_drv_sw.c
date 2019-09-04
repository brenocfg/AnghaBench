#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pwrctrl_priv {scalar_t__ pwr_state_check_cnts; int /*<<< orphan*/  rf_pwrstate; void* bips_processing; } ;
struct TYPE_11__ {void* bBusyTraffic; } ;
struct mlme_priv {TYPE_3__ LinkDetectInfo; int /*<<< orphan*/  scan_interval; } ;
struct TYPE_12__ {int /*<<< orphan*/  state; } ;
struct TYPE_13__ {TYPE_4__ sitesurvey_res; } ;
struct TYPE_10__ {scalar_t__ rx_pkts; } ;
struct TYPE_9__ {scalar_t__ tx_pkts; } ;
struct TYPE_14__ {TYPE_5__ mlmeextpriv; TYPE_2__ recvpriv; TYPE_1__ xmitpriv; scalar_t__ bRxRSSIDisplay; void* bWritePortCancel; void* bReadPortCancel; struct pwrctrl_priv pwrctrlpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_6__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_DISABLE ; 
 int /*<<< orphan*/  SCAN_INTERVAL ; 
 void* _FALSE ; 
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  rf_on ; 
 int /*<<< orphan*/  rtw_hal_def_value_init (TYPE_6__*) ; 

u8 rtw_reset_drv_sw(_adapter *padapter)
{
	u8	ret8=_SUCCESS;
	struct mlme_priv *pmlmepriv= &padapter->mlmepriv;
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	//hal_priv
	rtw_hal_def_value_init(padapter);
	padapter->bReadPortCancel = _FALSE;
	padapter->bWritePortCancel = _FALSE;
	padapter->bRxRSSIDisplay = 0;
	pmlmepriv->scan_interval = SCAN_INTERVAL;// 30*2 sec = 60sec

	pwrctrlpriv->bips_processing = _FALSE;
	pwrctrlpriv->rf_pwrstate = rf_on;

	padapter->xmitpriv.tx_pkts = 0;
	padapter->recvpriv.rx_pkts = 0;

	pmlmepriv->LinkDetectInfo.bBusyTraffic = _FALSE;

	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY |_FW_UNDER_LINKING);

#ifdef CONFIG_AUTOSUSPEND
	#if (LINUX_VERSION_CODE>=KERNEL_VERSION(2,6,22) && LINUX_VERSION_CODE<=KERNEL_VERSION(2,6,34))
		adapter_to_dvobj(padapter)->pusbdev->autosuspend_disabled = 1;//autosuspend disabled by the user
	#endif
#endif

#ifdef DBG_CONFIG_ERROR_DETECT
	rtw_hal_sreset_reset_value(padapter);
#endif
	pwrctrlpriv->pwr_state_check_cnts = 0;

	//mlmeextpriv
	padapter->mlmeextpriv.sitesurvey_res.state= SCAN_DISABLE;

#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	rtw_set_signal_stat_timer(&padapter->recvpriv);
#endif

	return ret8;
}