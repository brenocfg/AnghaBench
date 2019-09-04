#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pwrctrl_priv {scalar_t__ pwr_state_check_cnts; } ;
struct TYPE_7__ {int bBusyTraffic; } ;
struct mlme_priv {TYPE_2__ LinkDetectInfo; int /*<<< orphan*/  scan_interval; } ;
struct TYPE_10__ {scalar_t__ rx_pkts; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_3__ sitesurvey_res; } ;
struct TYPE_6__ {scalar_t__ tx_pkts; } ;
struct adapter {int bReadPortCancel; int bWritePortCancel; TYPE_5__ recvpriv; TYPE_4__ mlmeextpriv; TYPE_1__ xmitpriv; struct pwrctrl_priv pwrctrlpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_DISABLE ; 
 int /*<<< orphan*/  SCAN_INTERVAL ; 
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  rtw_hal_def_value_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_sreset_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_signal_stat_timer (TYPE_5__*) ; 

u8 rtw_reset_drv_sw(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	/* hal_priv */
	rtw_hal_def_value_init(padapter);
	padapter->bReadPortCancel = false;
	padapter->bWritePortCancel = false;
	pmlmepriv->scan_interval = SCAN_INTERVAL;/*  30*2 sec = 60sec */

	padapter->xmitpriv.tx_pkts = 0;
	padapter->recvpriv.rx_pkts = 0;

	pmlmepriv->LinkDetectInfo.bBusyTraffic = false;

	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING);
	rtw_hal_sreset_init(padapter);
	pwrctrlpriv->pwr_state_check_cnts = 0;

	/* mlmeextpriv */
	padapter->mlmeextpriv.sitesurvey_res.state = SCAN_DISABLE;

	rtw_set_signal_stat_timer(&padapter->recvpriv);

	return _SUCCESS;
}