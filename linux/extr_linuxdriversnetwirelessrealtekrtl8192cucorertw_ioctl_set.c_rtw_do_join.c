#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_17__ {void* bBusyTraffic; } ;
struct TYPE_18__ {int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {int join_res; } ;
struct mlme_priv {int /*<<< orphan*/  assoc_ssid; TYPE_3__ LinkDetectInfo; void* to_join; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  assoc_timer; TYPE_4__ scanned_queue; int /*<<< orphan*/ * pscanned; TYPE_1__ cur_network; } ;
typedef  TYPE_4__ _queue ;
typedef  int /*<<< orphan*/  _list ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_20__ {int* MacAddress; int /*<<< orphan*/  Ssid; } ;
struct TYPE_16__ {TYPE_6__ dev_network; } ;
struct TYPE_19__ {TYPE_2__ registrypriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_5__ _adapter ;
typedef  TYPE_6__ WLAN_BSSID_EX ;
typedef  int /*<<< orphan*/  NDIS_802_11_SSID ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_JOIN_TIMEOUT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _rtw_queue_empty (TYPE_4__*) ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_list_head (TYPE_4__*) ; 
 int /*<<< orphan*/ * get_next (int /*<<< orphan*/ *) ; 
 int rtw_createbss_cmd (TYPE_5__*) ; 
 int /*<<< orphan*/  rtw_generate_random_ibss (int*) ; 
 int /*<<< orphan*/  rtw_indicate_connect (TYPE_5__*) ; 
 int rtw_select_and_join_from_scanned_queue (struct mlme_priv*) ; 
 int rtw_sitesurvey_cmd (TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_to_roaming (TYPE_5__*) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (TYPE_5__*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

u8 rtw_do_join(_adapter * padapter)
{
	_irqL	irqL;
	_list	*plist, *phead;
	u8* pibss = NULL;
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	_queue	*queue	= &(pmlmepriv->scanned_queue);
	u8 ret=_SUCCESS;

_func_enter_;

	_enter_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
	phead = get_list_head(queue);
	plist = get_next(phead);

	RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_info_,("\n rtw_do_join: phead = %p; plist = %p \n\n\n", phead, plist));

	pmlmepriv->cur_network.join_res = -2;
		
	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

	pmlmepriv->pscanned = plist;

	pmlmepriv->to_join = _TRUE;

	if(_rtw_queue_empty(queue)== _TRUE)
	{	
		_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
            		
		//when set_ssid/set_bssid for rtw_do_join(), but scanning queue is empty
		//we try to issue sitesurvey firstly	
            		
		if (pmlmepriv->LinkDetectInfo.bBusyTraffic ==_FALSE
			|| rtw_to_roaming(padapter) > 0
		)
		{
			RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_info_,("rtw_do_join(): site survey if scanned_queue is empty\n."));
			// submit site_survey_cmd
			if(_SUCCESS!=(ret=rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, NULL, 0)) ) {
				RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_err_,("rtw_do_join(): site survey return error\n."));
			}
		}
		
		goto exit;
	}	
	else 	
	{
		int select_ret;
		_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
		if((select_ret=rtw_select_and_join_from_scanned_queue(pmlmepriv))==_SUCCESS)
		{
			pmlmepriv->to_join = _FALSE;
			_set_timer(&pmlmepriv->assoc_timer, MAX_JOIN_TIMEOUT);
		}
		else if(ret == 2)//there is no need to wait for join
		{
			ret = _SUCCESS;
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			rtw_indicate_connect(padapter);
		}
		else	
		{
			if(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)==_TRUE)
			{
				// submit createbss_cmd to change to a ADHOC_MASTER

 				//pmlmepriv->lock has been acquired by caller...
				WLAN_BSSID_EX    *pdev_network = &(padapter->registrypriv.dev_network);

				pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;
				
				pibss = padapter->registrypriv.dev_network.MacAddress;

				_rtw_memset(&pdev_network->Ssid, 0, sizeof(NDIS_802_11_SSID));
				_rtw_memcpy(&pdev_network->Ssid, &pmlmepriv->assoc_ssid, sizeof(NDIS_802_11_SSID));
	
				rtw_update_registrypriv_dev_network(padapter);

				rtw_generate_random_ibss(pibss);
					
				if(rtw_createbss_cmd(padapter)!=_SUCCESS)
				{
					RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_err_,("***Error=>do_goin: rtw_createbss_cmd status FAIL*** \n "));						
					ret =  _FALSE;
					goto exit;
				}

			     	pmlmepriv->to_join = _FALSE;

				RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_info_,("***Error=> rtw_select_and_join_from_scanned_queue FAIL under STA_Mode*** \n "));						

			}			
			else
			{ 
				// can't associate ; reset under-linking			
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

#if 0	
				if((check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE))
				{
					if(_rtw_memcmp(pmlmepriv->cur_network.network.Ssid.Ssid, pmlmepriv->assoc_ssid.Ssid, pmlmepriv->assoc_ssid.SsidLength))
					{ 
						// for funk to do roaming
						// funk will reconnect, but funk will not sitesurvey before reconnect
						RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_info_,("for funk to do roaming"));
						if(pmlmepriv->sitesurveyctrl.traffic_busy==_FALSE)
							rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, NULL, 0);
					}
				
				}				
#endif

				//when set_ssid/set_bssid for rtw_do_join(), but there are no desired bss in scanning queue
				//we try to issue sitesurvey firstly			
				if(pmlmepriv->LinkDetectInfo.bBusyTraffic==_FALSE
					|| rtw_to_roaming(padapter) > 0
				)
				{
					//DBG_871X("rtw_do_join() when   no desired bss in scanning queue \n");
					if( _SUCCESS!=(ret=rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, NULL, 0)) ){
						RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_err_,("do_join(): site survey return error\n."));
					}
				}				


			}

		}

	}
	
exit:
	
_func_exit_;	

	return ret;	
}