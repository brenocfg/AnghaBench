#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_14__ {int /*<<< orphan*/  IEs; } ;
struct wlan_network {TYPE_3__ network; } ;
struct TYPE_18__ {int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  IEs; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_13__ {TYPE_1__ network; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_8__ scanned_queue; TYPE_2__ cur_network; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_16__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_5__ _adapter ;
struct TYPE_15__ {scalar_t__* Ssid; scalar_t__ SsidLength; } ;
struct TYPE_17__ {TYPE_4__ Ssid; int /*<<< orphan*/  IEs; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_6__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ _rtw_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int get_WLAN_BSSID_EX_sz (TYPE_6__*) ; 
 int /*<<< orphan*/  rtw_add_network (TYPE_5__*,TYPE_6__*) ; 
 struct wlan_network* rtw_find_network (TYPE_8__*,int /*<<< orphan*/ ) ; 

void rtw_survey_event_callback(_adapter	*adapter, u8 *pbuf)
{
	_irqL  irqL;
	u32 len;
	WLAN_BSSID_EX *pnetwork;
	struct	mlme_priv	*pmlmepriv = &(adapter->mlmepriv);

_func_enter_;		

	pnetwork = (WLAN_BSSID_EX *)pbuf;

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("rtw_survey_event_callback, ssid=%s\n",  pnetwork->Ssid.Ssid));

#ifdef CONFIG_RTL8712
        //endian_convert
 	pnetwork->Length = le32_to_cpu(pnetwork->Length);
  	pnetwork->Ssid.SsidLength = le32_to_cpu(pnetwork->Ssid.SsidLength);	
	pnetwork->Privacy =le32_to_cpu( pnetwork->Privacy);
	pnetwork->Rssi = le32_to_cpu(pnetwork->Rssi);
	pnetwork->NetworkTypeInUse =le32_to_cpu(pnetwork->NetworkTypeInUse);	
	pnetwork->Configuration.ATIMWindow = le32_to_cpu(pnetwork->Configuration.ATIMWindow);
	pnetwork->Configuration.BeaconPeriod = le32_to_cpu(pnetwork->Configuration.BeaconPeriod);
	pnetwork->Configuration.DSConfig =le32_to_cpu(pnetwork->Configuration.DSConfig);
	pnetwork->Configuration.FHConfig.DwellTime=le32_to_cpu(pnetwork->Configuration.FHConfig.DwellTime);
	pnetwork->Configuration.FHConfig.HopPattern=le32_to_cpu(pnetwork->Configuration.FHConfig.HopPattern);
	pnetwork->Configuration.FHConfig.HopSet=le32_to_cpu(pnetwork->Configuration.FHConfig.HopSet);
	pnetwork->Configuration.FHConfig.Length=le32_to_cpu(pnetwork->Configuration.FHConfig.Length);	
	pnetwork->Configuration.Length = le32_to_cpu(pnetwork->Configuration.Length);
	pnetwork->InfrastructureMode = le32_to_cpu(pnetwork->InfrastructureMode);
	pnetwork->IELength = le32_to_cpu(pnetwork->IELength);
#endif	

	len = get_WLAN_BSSID_EX_sz(pnetwork);
	if(len > (sizeof(WLAN_BSSID_EX)))
	{
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("\n ****rtw_survey_event_callback: return a wrong bss ***\n"));
		return;
	}


	_enter_critical_bh(&pmlmepriv->lock, &irqL);

	// update IBSS_network 's timestamp
	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) == _TRUE)
	{
		//RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,"rtw_survey_event_callback : WIFI_ADHOC_MASTER_STATE \n\n");
		if(_rtw_memcmp(&(pmlmepriv->cur_network.network.MacAddress), pnetwork->MacAddress, ETH_ALEN))
		{
			struct wlan_network* ibss_wlan = NULL;
			_irqL	irqL;
			
			_rtw_memcpy(pmlmepriv->cur_network.network.IEs, pnetwork->IEs, 8);
			_enter_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
			ibss_wlan = rtw_find_network(&pmlmepriv->scanned_queue,  pnetwork->MacAddress);
			if(ibss_wlan)
			{
				_rtw_memcpy(ibss_wlan->network.IEs , pnetwork->IEs, 8);			
				_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);		
				goto exit;
			}
			_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
		}
	}

	// lock pmlmepriv->lock when you accessing network_q
	if ((check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) == _FALSE)
	{		
   	        if( pnetwork->Ssid.Ssid[0] == 0 )
		{
			pnetwork->Ssid.SsidLength = 0;
		}	
		rtw_add_network(adapter, pnetwork);
	}	

exit:	
		
	_exit_critical_bh(&pmlmepriv->lock, &irqL);

_func_exit_;		

	return;	
}