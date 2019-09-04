#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct mlme_priv {scalar_t__ to_join; int /*<<< orphan*/  lock; int /*<<< orphan*/  assoc_timer; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  assoc_ssid; int /*<<< orphan*/  scan_to_timer; int /*<<< orphan*/ * wps_probe_req_ie; scalar_t__ wps_probe_req_ie_len; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_13__ {int /*<<< orphan*/  Ssid; scalar_t__* MacAddress; } ;
struct TYPE_11__ {TYPE_3__ dev_network; } ;
struct TYPE_12__ {TYPE_1__ registrypriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  TYPE_3__ WLAN_BSSID_EX ;
typedef  int /*<<< orphan*/  NDIS_802_11_SSID ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_JOIN_TIMEOUT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _FW_UNDER_SURVEY ; 
 int _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _cancel_timer (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 int /*<<< orphan*/  indicate_wx_scan_complete_event (TYPE_2__*) ; 
 int rtw_createbss_cmd (TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_generate_random_ibss (scalar_t__*) ; 
 int /*<<< orphan*/  rtw_indicate_connect (TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rtw_os_xmit_schedule (TYPE_2__*) ; 
 int rtw_select_and_join_from_scanned_queue (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_to_roaming (TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (TYPE_2__*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

void rtw_surveydone_event_callback(_adapter	*adapter, u8 *pbuf)
{
	_irqL  irqL;
	u8 timer_cancelled = _FALSE;
	struct	mlme_priv	*pmlmepriv = &(adapter->mlmepriv);
	
#ifdef CONFIG_MLME_EXT	

	mlmeext_surveydone_event_callback(adapter);

#endif

_func_enter_;			

	_enter_critical_bh(&pmlmepriv->lock, &irqL);
	if(pmlmepriv->wps_probe_req_ie)
	{
		u32 free_len = pmlmepriv->wps_probe_req_ie_len;
		pmlmepriv->wps_probe_req_ie_len = 0;
		rtw_mfree(pmlmepriv->wps_probe_req_ie, free_len);
		pmlmepriv->wps_probe_req_ie = NULL;			
	}
	
	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("rtw_surveydone_event_callback: fw_state:%x\n\n", get_fwstate(pmlmepriv)));
	
	if (check_fwstate(pmlmepriv,_FW_UNDER_SURVEY))
	{
		//u8 timer_cancelled;

		timer_cancelled = _TRUE;
		//_cancel_timer(&pmlmepriv->scan_to_timer, &timer_cancelled);
		
		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	}
	else {
	
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("nic status =%x, survey done event comes too late!\n", get_fwstate(pmlmepriv)));	
	}
	_exit_critical_bh(&pmlmepriv->lock, &irqL);

	if(timer_cancelled)
		_cancel_timer(&pmlmepriv->scan_to_timer, &timer_cancelled);


	_enter_critical_bh(&pmlmepriv->lock, &irqL);

	#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	rtw_set_signal_stat_timer(&adapter->recvpriv);
	#endif

	if(pmlmepriv->to_join == _TRUE)
	{
		if((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)==_TRUE) )
		{
			if(check_fwstate(pmlmepriv, _FW_LINKED)==_FALSE)
			{
				set_fwstate(pmlmepriv, _FW_UNDER_LINKING);	
				
		   		if(rtw_select_and_join_from_scanned_queue(pmlmepriv)==_SUCCESS)
		   		{
		       			_set_timer(&pmlmepriv->assoc_timer, MAX_JOIN_TIMEOUT );	 
                  		}
		   		else	
		  		{
					WLAN_BSSID_EX    *pdev_network = &(adapter->registrypriv.dev_network); 			
					u8 *pibss = adapter->registrypriv.dev_network.MacAddress;

					//pmlmepriv->fw_state ^= _FW_UNDER_SURVEY;//because don't set assoc_timer
					_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);

					RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("switching to adhoc master\n"));
				
					_rtw_memset(&pdev_network->Ssid, 0, sizeof(NDIS_802_11_SSID));
					_rtw_memcpy(&pdev_network->Ssid, &pmlmepriv->assoc_ssid, sizeof(NDIS_802_11_SSID));
	
					rtw_update_registrypriv_dev_network(adapter);
					rtw_generate_random_ibss(pibss);

                       			pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;
			
					if(rtw_createbss_cmd(adapter)!=_SUCCESS)
					{
	                     		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("Error=>rtw_createbss_cmd status FAIL\n"));						
					}	

			     		pmlmepriv->to_join = _FALSE;
		   		}
		 	}
		}
		else
		{
			int s_ret;
			set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
			pmlmepriv->to_join = _FALSE;
			if(_SUCCESS == (s_ret=rtw_select_and_join_from_scanned_queue(pmlmepriv)))
			{
	     		     _set_timer(&pmlmepriv->assoc_timer, MAX_JOIN_TIMEOUT);	 
			}
			else if(s_ret == 2)//there is no need to wait for join
			{
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
				rtw_indicate_connect(adapter);
			}
			else
			{
				DBG_871X("try_to_join, but select scanning queue fail, to_roaming:%d\n", rtw_to_roaming(adapter));
				#ifdef CONFIG_LAYER2_ROAMING
				if (rtw_to_roaming(adapter) != 0) {
					if( --pmlmepriv->to_roaming == 0
						|| _SUCCESS != rtw_sitesurvey_cmd(adapter, &pmlmepriv->assoc_ssid, 1, NULL, 0)
					) {
						rtw_set_roaming(adapter, 0);
#ifdef CONFIG_INTEL_WIDI
						if(adapter->mlmepriv.widi_state == INTEL_WIDI_STATE_ROAMING)
						{
							_rtw_memset(pmlmepriv->sa_ext, 0x00, L2SDTA_SERVICE_VE_LEN);
							intel_widi_wk_cmd(adapter, INTEL_WIDI_LISTEN_WK, NULL);
							DBG_871X("change to widi listen\n");
						}
#endif // CONFIG_INTEL_WIDI
						rtw_free_assoc_resources(adapter, 1);
						rtw_indicate_disconnect(adapter);
					} else {
						pmlmepriv->to_join = _TRUE;
					}
				}
				#endif
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			}
		}
	}

	indicate_wx_scan_complete_event(adapter);
	//DBG_871X("scan complete in %dms\n",rtw_get_passing_time_ms(pmlmepriv->scan_start_time));

	_exit_critical_bh(&pmlmepriv->lock, &irqL);

#ifdef CONFIG_P2P_PS
	if (check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE) {
		p2p_ps_wk_cmd(adapter, P2P_PS_SCAN_DONE, 0);
	}
#endif // CONFIG_P2P_PS

	rtw_os_xmit_schedule(adapter);
#ifdef CONFIG_CONCURRENT_MODE
	rtw_os_xmit_schedule(adapter->pbuddy_adapter);
#endif
#ifdef CONFIG_DUALMAC_CONCURRENT
	dc_resume_xmit(adapter);
#endif

#ifdef CONFIG_DRVEXT_MODULE_WSC
	drvext_surveydone_callback(&adapter->drvextpriv);
#endif

#ifdef DBG_CONFIG_ERROR_DETECT
#ifdef CONFIG_INTEL_WIDI
	if (adapter->mlmepriv.widi_state == INTEL_WIDI_STATE_NONE)
#endif
	{
		struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;		
		if(pmlmeext->sitesurvey_res.bss_cnt == 0){
			rtw_hal_sreset_reset(adapter);
		}
	}
#endif

#ifdef CONFIG_IOCTL_CFG80211
	rtw_cfg80211_surveydone_event_callback(adapter);
#endif //CONFIG_IOCTL_CFG80211

_func_exit_;	

}