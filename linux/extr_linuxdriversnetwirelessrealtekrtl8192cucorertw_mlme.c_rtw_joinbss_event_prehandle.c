#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_13__ {int Length; int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {int join_res; unsigned int fixed; TYPE_11__ network; } ;
struct sta_priv {int /*<<< orphan*/  sta_hash_lock; } ;
struct sta_info {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct mlme_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  assoc_timer; TYPE_10__ scanned_queue; TYPE_1__ assoc_ssid; struct wlan_network cur_network; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_15__ {struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 unsigned int _TRUE ; 
 int /*<<< orphan*/  _cancel_timer (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 unsigned int _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int) ; 
 unsigned int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int get_WLAN_BSSID_EX_sz (TYPE_11__*) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 struct wlan_network* rtw_find_network (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_stainfo (TYPE_2__*,struct sta_info*) ; 
 int /*<<< orphan*/  rtw_get_encrypt_decrypt_from_registrypriv (TYPE_2__*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_joinbss_update_network (TYPE_2__*,struct wlan_network*,struct wlan_network*) ; 
 struct sta_info* rtw_joinbss_update_stainfo (TYPE_2__*,struct wlan_network*) ; 
 int /*<<< orphan*/  rtw_reset_securitypriv (TYPE_2__*) ; 

void rtw_joinbss_event_prehandle(_adapter *adapter, u8 *pbuf)
{
	_irqL irqL,irqL2;
	static u8 retry=0;
	u8 timer_cancelled;
	struct sta_info *ptarget_sta= NULL, *pcur_sta = NULL;
   	struct	sta_priv *pstapriv = &adapter->stapriv;
	struct	mlme_priv	*pmlmepriv = &(adapter->mlmepriv);
	struct wlan_network 	*pnetwork	= (struct wlan_network *)pbuf;
	struct wlan_network 	*cur_network = &(pmlmepriv->cur_network);
	struct wlan_network	*pcur_wlan = NULL, *ptarget_wlan = NULL;
	unsigned int 		the_same_macaddr = _FALSE;	

_func_enter_;	

#ifdef CONFIG_RTL8712
       //endian_convert
	pnetwork->join_res = le32_to_cpu(pnetwork->join_res);
	pnetwork->network_type = le32_to_cpu(pnetwork->network_type);
	pnetwork->network.Length = le32_to_cpu(pnetwork->network.Length);
	pnetwork->network.Ssid.SsidLength = le32_to_cpu(pnetwork->network.Ssid.SsidLength);
	pnetwork->network.Privacy =le32_to_cpu( pnetwork->network.Privacy);
	pnetwork->network.Rssi = le32_to_cpu(pnetwork->network.Rssi);
	pnetwork->network.NetworkTypeInUse =le32_to_cpu(pnetwork->network.NetworkTypeInUse) ;	
	pnetwork->network.Configuration.ATIMWindow = le32_to_cpu(pnetwork->network.Configuration.ATIMWindow);
	pnetwork->network.Configuration.BeaconPeriod = le32_to_cpu(pnetwork->network.Configuration.BeaconPeriod);
	pnetwork->network.Configuration.DSConfig = le32_to_cpu(pnetwork->network.Configuration.DSConfig);
	pnetwork->network.Configuration.FHConfig.DwellTime=le32_to_cpu(pnetwork->network.Configuration.FHConfig.DwellTime);
	pnetwork->network.Configuration.FHConfig.HopPattern=le32_to_cpu(pnetwork->network.Configuration.FHConfig.HopPattern);
	pnetwork->network.Configuration.FHConfig.HopSet=le32_to_cpu(pnetwork->network.Configuration.FHConfig.HopSet);
	pnetwork->network.Configuration.FHConfig.Length=le32_to_cpu(pnetwork->network.Configuration.FHConfig.Length);	
	pnetwork->network.Configuration.Length = le32_to_cpu(pnetwork->network.Configuration.Length);
	pnetwork->network.InfrastructureMode = le32_to_cpu(pnetwork->network.InfrastructureMode);
	pnetwork->network.IELength = le32_to_cpu(pnetwork->network.IELength );
#endif

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("joinbss event call back received with res=%d\n", pnetwork->join_res));

	rtw_get_encrypt_decrypt_from_registrypriv(adapter);
	

	if (pmlmepriv->assoc_ssid.SsidLength == 0)
	{
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("@@@@@   joinbss event call back  for Any SSid\n"));		
	}
	else
	{
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("@@@@@   rtw_joinbss_event_callback for SSid:%s\n", pmlmepriv->assoc_ssid.Ssid));
	}
	
	the_same_macaddr = _rtw_memcmp(pnetwork->network.MacAddress, cur_network->network.MacAddress, ETH_ALEN);

	pnetwork->network.Length = get_WLAN_BSSID_EX_sz(&pnetwork->network);
	if(pnetwork->network.Length > sizeof(WLAN_BSSID_EX))
	{
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("\n\n ***joinbss_evt_callback return a wrong bss ***\n\n"));
		goto ignore_joinbss_callback;
	}

	_enter_critical_bh(&pmlmepriv->lock, &irqL);
	
	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("\n rtw_joinbss_event_callback !! _enter_critical \n"));

	if(pnetwork->join_res > 0)
	{
		_enter_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
		retry = 0;
		if (check_fwstate(pmlmepriv,_FW_UNDER_LINKING) )
		{
			//s1. find ptarget_wlan
			if(check_fwstate(pmlmepriv, _FW_LINKED) )
			{
				if(the_same_macaddr == _TRUE)
				{
					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);					
				}
				else
				{
					pcur_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
					if(pcur_wlan)	pcur_wlan->fixed = _FALSE;

					pcur_sta = rtw_get_stainfo(pstapriv, cur_network->network.MacAddress);
					if(pcur_sta){
						_enter_critical_bh(&(pstapriv->sta_hash_lock), &irqL2);
						rtw_free_stainfo(adapter,  pcur_sta);
						_exit_critical_bh(&(pstapriv->sta_hash_lock), &irqL2);
					}

					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
					if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE){
						if(ptarget_wlan)	ptarget_wlan->fixed = _TRUE;			
					}
				}

			}
			else
			{
				ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
				if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE){
					if(ptarget_wlan)	ptarget_wlan->fixed = _TRUE;			
				}
			}
		
			//s2. update cur_network 
			if(ptarget_wlan)
			{			
				rtw_joinbss_update_network(adapter, ptarget_wlan, pnetwork);
			}
			else
			{
				RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("Can't find ptarget_wlan when joinbss_event callback\n"));
				_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
				goto ignore_joinbss_callback;
			}
			
			
			//s3. find ptarget_sta & update ptarget_sta after update cur_network only for station mode 
			if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE)
			{
				ptarget_sta = rtw_joinbss_update_stainfo(adapter, pnetwork);
				if(ptarget_sta==NULL)
				{
					RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("Can't update stainfo when joinbss_event callback\n"));
					_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
					goto ignore_joinbss_callback;
				}
			}	
					
			//s4. indicate connect			
			if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE)
			{
				rtw_indicate_connect(adapter);
			}
			else
			{
				//adhoc mode will rtw_indicate_connect when rtw_stassoc_event_callback
				RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("adhoc mode, fw_state:%x", get_fwstate(pmlmepriv)));
			}


			//s5. Cancle assoc_timer					
			_cancel_timer(&pmlmepriv->assoc_timer, &timer_cancelled);
			
			RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("Cancle assoc_timer\n"));
				
		}
		else
		{
			RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("rtw_joinbss_event_callback err: fw_state:%x", get_fwstate(pmlmepriv)));	
			_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
			goto ignore_joinbss_callback;
		}
		
		_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
				
	}
	else if(pnetwork->join_res == -4) 
	{
		rtw_reset_securitypriv(adapter);
		_set_timer(&pmlmepriv->assoc_timer, 1);					

		//rtw_free_assoc_resources(adapter, 1);

		if((check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) == _TRUE)
		{		
			RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("fail! clear _FW_UNDER_LINKING ^^^fw_state=%x\n", get_fwstate(pmlmepriv)));
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
		}	
		
	}
	else //if join_res < 0 (join fails), then try again
	{
	
		#ifdef REJOIN
		res = _FAIL;
		if(retry < 2) {
			res = rtw_select_and_join_from_scanned_queue(pmlmepriv);
			RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("rtw_select_and_join_from_scanned_queue again! res:%d\n",res));
		}

		 if(res == _SUCCESS)
		{
			//extend time of assoc_timer
			_set_timer(&pmlmepriv->assoc_timer, MAX_JOIN_TIMEOUT);
			retry++;
		}
		else if(res == 2)//there is no need to wait for join
		{
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			rtw_indicate_connect(adapter);
		}	
		else
		{
			RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("Set Assoc_Timer = 1; can't find match ssid in scanned_q \n"));
		#endif
			
			_set_timer(&pmlmepriv->assoc_timer, 1);
			//rtw_free_assoc_resources(adapter, 1);
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			
		#ifdef REJOIN
			retry = 0;	
		}
		#endif
	}

ignore_joinbss_callback:

	_exit_critical_bh(&pmlmepriv->lock, &irqL);
	_func_exit_;	
}