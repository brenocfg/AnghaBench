#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wlan_network {int /*<<< orphan*/  network; int /*<<< orphan*/  list; int /*<<< orphan*/  last_scanned; } ;
struct sta_info {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_4__ scanned_queue; int /*<<< orphan*/  assoc_timer; struct wlan_network cur_network; } ;
struct cmd_obj {scalar_t__ res; scalar_t__ parmbuf; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_8__ {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_9__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_2__ WLAN_BSSID_EX ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _cancel_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 struct wlan_network* _rtw_alloc_network (struct mlme_priv*) ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_WLAN_BSSID_EX_sz (TYPE_2__*) ; 
 struct sta_info* rtw_alloc_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_get_current_time () ; 
 struct wlan_network* rtw_get_oldest_wlan_network (TYPE_4__*) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rtw_createbss_cmd_callback(_adapter *padapter, struct cmd_obj *pcmd)
{	
	_irqL irqL;
	u8 timer_cancelled;
	struct sta_info *psta = NULL;
	struct wlan_network *pwlan = NULL;		
	struct 	mlme_priv *pmlmepriv = &padapter->mlmepriv;	
	WLAN_BSSID_EX *pnetwork = (WLAN_BSSID_EX *)pcmd->parmbuf;
	struct wlan_network *tgt_network = &(pmlmepriv->cur_network);

_func_enter_;	

	if((pcmd->res != H2C_SUCCESS))
	{	
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\n ********Error: rtw_createbss_cmd_callback  Fail ************\n\n."));
		_set_timer(&pmlmepriv->assoc_timer, 1 );		
	}
	
	_cancel_timer(&pmlmepriv->assoc_timer, &timer_cancelled);

#ifdef CONFIG_FW_MLMLE
       //endian_convert
	pnetwork->Length = le32_to_cpu(pnetwork->Length);
  	pnetwork->Ssid.SsidLength = le32_to_cpu(pnetwork->Ssid.SsidLength);
	pnetwork->Privacy =le32_to_cpu(pnetwork->Privacy);
	pnetwork->Rssi = le32_to_cpu(pnetwork->Rssi);
	pnetwork->NetworkTypeInUse =le32_to_cpu(pnetwork->NetworkTypeInUse);	
	pnetwork->Configuration.ATIMWindow = le32_to_cpu(pnetwork->Configuration.ATIMWindow);
	//pnetwork->Configuration.BeaconPeriod = le32_to_cpu(pnetwork->Configuration.BeaconPeriod);
	pnetwork->Configuration.DSConfig =le32_to_cpu(pnetwork->Configuration.DSConfig);
	pnetwork->Configuration.FHConfig.DwellTime=le32_to_cpu(pnetwork->Configuration.FHConfig.DwellTime);
	pnetwork->Configuration.FHConfig.HopPattern=le32_to_cpu(pnetwork->Configuration.FHConfig.HopPattern);
	pnetwork->Configuration.FHConfig.HopSet=le32_to_cpu(pnetwork->Configuration.FHConfig.HopSet);
	pnetwork->Configuration.FHConfig.Length=le32_to_cpu(pnetwork->Configuration.FHConfig.Length);	
	pnetwork->Configuration.Length = le32_to_cpu(pnetwork->Configuration.Length);
	pnetwork->InfrastructureMode = le32_to_cpu(pnetwork->InfrastructureMode);
	pnetwork->IELength = le32_to_cpu(pnetwork->IELength);
#endif
	
	_enter_critical_bh(&pmlmepriv->lock, &irqL);
	
	
	if(check_fwstate(pmlmepriv, WIFI_AP_STATE) )
	{
		psta = rtw_get_stainfo(&padapter->stapriv, pnetwork->MacAddress);
		if(!psta)
		{
		psta = rtw_alloc_stainfo(&padapter->stapriv, pnetwork->MacAddress);
		if (psta == NULL) 
		{ 
			RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\nCan't alloc sta_info when createbss_cmd_callback\n"));
			goto createbss_cmd_fail ;
		}
		}	
			
		rtw_indicate_connect( padapter);
	}
	else
	{	
		_irqL	irqL;

		pwlan = _rtw_alloc_network(pmlmepriv);
		_enter_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
		if ( pwlan == NULL)
		{
			pwlan = rtw_get_oldest_wlan_network(&pmlmepriv->scanned_queue);
			if( pwlan == NULL)
			{
				RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\n Error:  can't get pwlan in rtw_joinbss_event_callback \n"));
				_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
				goto createbss_cmd_fail;
			}
			pwlan->last_scanned = rtw_get_current_time();			
		}	
		else
		{
			rtw_list_insert_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue);
		}
				
		pnetwork->Length = get_WLAN_BSSID_EX_sz(pnetwork);
		_rtw_memcpy(&(pwlan->network), pnetwork, pnetwork->Length);
		//pwlan->fixed = _TRUE;

		//rtw_list_insert_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue);

		// copy pdev_network information to 	pmlmepriv->cur_network
		_rtw_memcpy(&tgt_network->network, pnetwork, (get_WLAN_BSSID_EX_sz(pnetwork)));

		// reset DSConfig
		//tgt_network->network.Configuration.DSConfig = (u32)rtw_ch2freq(pnetwork->Configuration.DSConfig);

		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

#if 0		
		if((pmlmepriv->fw_state) & WIFI_AP_STATE)
		{
			psta = rtw_alloc_stainfo(&padapter->stapriv, pnetwork->MacAddress);

			if (psta == NULL) { // for AP Mode & Adhoc Master Mode
				RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\nCan't alloc sta_info when createbss_cmd_callback\n"));
				goto createbss_cmd_fail ;
			}
			
			rtw_indicate_connect( padapter);
		}
		else {

			//rtw_indicate_disconnect(dev);
		}		
#endif
		_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
		// we will set _FW_LINKED when there is one more sat to join us (rtw_stassoc_event_callback)
			
	}

createbss_cmd_fail:
	
	_exit_critical_bh(&pmlmepriv->lock, &irqL);

	rtw_free_cmd_obj(pcmd);
	
_func_exit_;	

}