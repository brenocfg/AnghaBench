#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_6__ {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; struct mlme_priv mlmepriv; int /*<<< orphan*/ * pbuddy_adapter; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  linked_status_chk (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_hal_dm_watchdog (TYPE_1__*) ; 
 int /*<<< orphan*/  traffic_status_watchdog (TYPE_1__*) ; 

void dynamic_chk_wk_hdl(_adapter *padapter, u8 *pbuf, int sz)
{
	struct mlme_priv *pmlmepriv;
	
	if ((padapter->bDriverStopped == _TRUE)||(padapter->bSurpriseRemoved== _TRUE))
		return;

	if((void*)padapter != (void*)pbuf && padapter->pbuddy_adapter == NULL)
		return;		

	padapter = (_adapter *)pbuf;

	if ((padapter->bDriverStopped == _TRUE)||(padapter->bSurpriseRemoved== _TRUE))
		return;

	pmlmepriv = &(padapter->mlmepriv);

#ifdef CONFIG_ACTIVE_KEEP_ALIVE_CHECK
#ifdef CONFIG_AP_MODE
	if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
	{			
		expire_timeout_chk(padapter);
	}
#endif
#endif //CONFIG_ACTIVE_KEEP_ALIVE_CHECK

	#ifdef DBG_CONFIG_ERROR_DETECT	
	rtw_hal_sreset_xmit_status_check(padapter);
	#endif	

	//if(check_fwstate(pmlmepriv, _FW_UNDER_LINKING|_FW_UNDER_SURVEY)==_FALSE)
	{
		linked_status_chk(padapter);	
		traffic_status_watchdog(padapter);
	}

	rtw_hal_dm_watchdog(padapter);

	//check_hw_pbc(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type_size);	

}