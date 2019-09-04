#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union iwreq_data {int mode; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_1__ scanned_queue; } ;
struct iw_request_info {int dummy; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_7__ {scalar_t__ hw_init_completed; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  NDIS_802_11_NETWORK_INFRASTRUCTURE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int EINVAL ; 
 int EPERM ; 
#define  IW_MODE_ADHOC 131 
#define  IW_MODE_AUTO 130 
#define  IW_MODE_INFRA 129 
#define  IW_MODE_MASTER 128 
 int /*<<< orphan*/  Ndis802_11APMode ; 
 int /*<<< orphan*/  Ndis802_11AutoUnknown ; 
 int /*<<< orphan*/  Ndis802_11IBSS ; 
 int /*<<< orphan*/  Ndis802_11Infrastructure ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_os_c ; 
 int /*<<< orphan*/ * iw_operation_mode ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 scalar_t__ rtw_pwr_wakeup (TYPE_2__*) ; 
 scalar_t__ rtw_set_802_11_infrastructure_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_setopmode_cmd (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_wx_set_mode(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *b)
{
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	NDIS_802_11_NETWORK_INFRASTRUCTURE networkType ;
	int ret = 0;
	_irqL irqL;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	_queue *queue = &pmlmepriv->scanned_queue;
	_func_enter_;
	
	if(_FAIL == rtw_pwr_wakeup(padapter)) {
		ret= -EPERM;
		goto exit;
	}

	if (padapter->hw_init_completed==_FALSE){
		ret = -EPERM;
		goto exit;
	}
	
	switch(wrqu->mode)
	{
		case IW_MODE_AUTO:
			networkType = Ndis802_11AutoUnknown;
			DBG_871X("set_mode = IW_MODE_AUTO\n");	
			break;				
		case IW_MODE_ADHOC:		
			networkType = Ndis802_11IBSS;
			DBG_871X("set_mode = IW_MODE_ADHOC\n");			
			break;
		case IW_MODE_MASTER:		
			networkType = Ndis802_11APMode;
			DBG_871X("set_mode = IW_MODE_MASTER\n");
                        //rtw_setopmode_cmd(padapter, networkType);	
			break;				
		case IW_MODE_INFRA:
			networkType = Ndis802_11Infrastructure;
			DBG_871X("set_mode = IW_MODE_INFRA\n");			
			break;
	
		default :
			ret = -EINVAL;;
			RT_TRACE(_module_rtl871x_ioctl_os_c,_drv_err_,("\n Mode: %s is not supported  \n", iw_operation_mode[wrqu->mode]));
			goto exit;
	}
	
/*	
	if(Ndis802_11APMode == networkType)
	{
		rtw_setopmode_cmd(padapter, networkType);
	}	
	else
	{
		rtw_setopmode_cmd(padapter, Ndis802_11AutoUnknown);	
	}
*/
	_enter_critical_bh(&pmlmepriv->lock, &irqL);
	_enter_critical_bh(&queue->lock, &irqL);
	if (rtw_set_802_11_infrastructure_mode(padapter, networkType) ==_FALSE){

		ret = -EPERM;
		_exit_critical_bh(&queue->lock, &irqL);
		_exit_critical_bh(&pmlmepriv->lock, &irqL);
		goto exit;

	}
	_exit_critical_bh(&queue->lock, &irqL);
	_exit_critical_bh(&pmlmepriv->lock, &irqL);
	rtw_setopmode_cmd(padapter, networkType);

exit:
	
	_func_exit_;
	
	return ret;
	
}