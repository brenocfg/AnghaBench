#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlme_ext_info {scalar_t__ FW_sta_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_4__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_CAM_INVALID_ALL ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void flush_all_cam_entry(_adapter *padapter)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

#ifdef CONFIG_CONCURRENT_MODE

	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	//if(check_buddy_mlmeinfo_state(padapter, _HW_STATE_NOLINK_))	
	if(check_buddy_fwstate(padapter, _FW_LINKED) == _FALSE)
	{
		rtw_hal_set_hwreg(padapter, HW_VAR_CAM_INVALID_ALL, 0);		
	}
	else
	{
		if(check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		{
			struct sta_priv	*pstapriv = &padapter->stapriv;
			struct sta_info	*psta;
			u8 cam_id=0;//cam_entry

			psta = rtw_get_stainfo(pstapriv, pmlmeinfo->network.MacAddress);
			if(psta) {
				if(psta->state & WIFI_AP_STATE)
				{}   //clear cam when ap free per sta_info        
				else {
					if(psta->mac_id==2)
						cam_id = 5;
					else
						cam_id = 4;
				}
				//clear_cam_entry(padapter, cam_id);
				rtw_clearstakey_cmd(padapter, (u8*)psta, cam_id, _FALSE);
			}
		}
		else if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
		{
			//clear cam when ap free per sta_info 
		}			
	}
#else //CONFIG_CONCURRENT_MODE

	rtw_hal_set_hwreg(padapter, HW_VAR_CAM_INVALID_ALL, 0);	

#endif //CONFIG_CONCURRENT_MODE

	_rtw_memset((u8 *)(pmlmeinfo->FW_sta_info), 0, sizeof(pmlmeinfo->FW_sta_info));

}