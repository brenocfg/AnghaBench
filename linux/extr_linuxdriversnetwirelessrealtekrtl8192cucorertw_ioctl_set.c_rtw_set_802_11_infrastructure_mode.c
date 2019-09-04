#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_7__ {scalar_t__ InfrastructureMode; } ;
struct wlan_network {int join_res; TYPE_1__ network; } ;
struct mlme_priv {struct wlan_network cur_network; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_8__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  scalar_t__ NDIS_802_11_NETWORK_INFRASTRUCTURE ;

/* Variables and functions */
#define  Ndis802_11APMode 132 
#define  Ndis802_11AutoUnknown 131 
#define  Ndis802_11IBSS 130 
#define  Ndis802_11Infrastructure 129 
#define  Ndis802_11InfrastructureMax 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_NULL_STATE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

u8 rtw_set_802_11_infrastructure_mode(_adapter* padapter, 
	NDIS_802_11_NETWORK_INFRASTRUCTURE networktype)
{
	_irqL irqL;
	struct	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct	wlan_network	*cur_network = &pmlmepriv->cur_network;
	NDIS_802_11_NETWORK_INFRASTRUCTURE* pold_state = &(cur_network->network.InfrastructureMode);
	
_func_enter_;

	RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_notice_,
		 ("+rtw_set_802_11_infrastructure_mode: old=%d new=%d fw_state=0x%08x\n",
		  *pold_state, networktype, get_fwstate(pmlmepriv)));
	
	if(*pold_state != networktype)
	{
		
		RT_TRACE(_module_rtl871x_ioctl_set_c_,_drv_info_,(" change mode!"));
		//DBG_871X("change mode, old_mode=%d, new_mode=%d, fw_state=0x%x\n", *pold_state, networktype, get_fwstate(pmlmepriv));

		if(*pold_state==Ndis802_11APMode)
		{		
			//change to other mode from Ndis802_11APMode			
			cur_network->join_res = -1;
			
#ifdef CONFIG_NATIVEAP_MLME
			stop_ap_mode(padapter);
#endif
		}	

		if((check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE) ||(*pold_state==Ndis802_11IBSS))
			rtw_disassoc_cmd(padapter, 0, _TRUE);

		if((check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE) ||
			(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)== _TRUE) )
			rtw_free_assoc_resources(padapter, 0);

		if((*pold_state == Ndis802_11Infrastructure) ||(*pold_state == Ndis802_11IBSS))
	       {
			if(check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE)
			{		
				rtw_indicate_disconnect(padapter); //will clr Linked_state; before this function, we must have chked whether  issue dis-assoc_cmd or not
			}
	       }

		*pold_state = networktype;

		_clr_fwstate_(pmlmepriv, ~WIFI_NULL_STATE);
				
		switch(networktype)
		{
			case Ndis802_11IBSS:
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
				break;
				
			case Ndis802_11Infrastructure:
				set_fwstate(pmlmepriv, WIFI_STATION_STATE);
				break;
				
			case Ndis802_11APMode:
				set_fwstate(pmlmepriv, WIFI_AP_STATE);
#ifdef CONFIG_NATIVEAP_MLME
				start_ap_mode(padapter);
				//rtw_indicate_connect(padapter);
#endif				
				
				break;

			case Ndis802_11AutoUnknown:
			case Ndis802_11InfrastructureMax:
				break;                        				
		}

		//SecClearAllKeys(adapter);
		
		//RT_TRACE(COMP_OID_SET, DBG_LOUD, ("set_infrastructure: fw_state:%x after changing mode\n",
		//									get_fwstate(pmlmepriv) ));

	}

_func_exit_;

	return _TRUE;
}