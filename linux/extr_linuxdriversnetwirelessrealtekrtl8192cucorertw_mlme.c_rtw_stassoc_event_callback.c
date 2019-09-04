#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {scalar_t__ fixed; TYPE_2__ network; } ;
struct stassoc_event {scalar_t__ cam_id; int /*<<< orphan*/  macaddr; } ;
struct sta_info {scalar_t__ ieee8021x_blocked; int /*<<< orphan*/  dot118021XPrivacy; scalar_t__ mac_id; scalar_t__ qos_option; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_7__ scanned_queue; struct wlan_network cur_network; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_14__ {int asoc_sta_count; } ;
struct TYPE_11__ {scalar_t__ dot11AuthAlgrthm; int /*<<< orphan*/  dot11PrivacyAlgrthm; } ;
struct TYPE_13__ {TYPE_6__ stapriv; TYPE_1__ securitypriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 int /*<<< orphan*/  mlmeext_sta_add_event_callback (TYPE_3__*,struct sta_info*) ; 
 scalar_t__ rtw_access_ctrl (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct sta_info* rtw_alloc_stainfo (TYPE_6__*,int /*<<< orphan*/ ) ; 
 struct wlan_network* rtw_find_network (TYPE_7__*,int /*<<< orphan*/ ) ; 
 struct sta_info* rtw_get_stainfo (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_connect (TYPE_3__*) ; 

void rtw_stassoc_event_callback(_adapter *adapter, u8 *pbuf)
{
	_irqL irqL;	
	struct sta_info *psta;
	struct mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	struct stassoc_event	*pstassoc	= (struct stassoc_event*)pbuf;
	struct wlan_network 	*cur_network = &(pmlmepriv->cur_network);
	struct wlan_network	*ptarget_wlan = NULL;

_func_enter_;	
	
	if(rtw_access_ctrl(adapter, pstassoc->macaddr) == _FALSE)
		return;

#if defined (CONFIG_AP_MODE) && defined (CONFIG_NATIVEAP_MLME)
	if(check_fwstate(pmlmepriv, WIFI_AP_STATE))
	{
		psta = rtw_get_stainfo(&adapter->stapriv, pstassoc->macaddr);	
		if(psta)
		{
#ifdef CONFIG_IOCTL_CFG80211
#ifdef COMPAT_KERNEL_RELEASE

#elif (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37)) || defined(CONFIG_CFG80211_FORCE_COMPATIBLE_2_6_37_UNDER)
			u8 *passoc_req = NULL;
			u32 assoc_req_len;

			_enter_critical_bh(&psta->lock, &irqL);
			if(psta->passoc_req && psta->assoc_req_len>0)
			{				
				passoc_req = rtw_zmalloc(psta->assoc_req_len);
				if(passoc_req)
				{
					assoc_req_len = psta->assoc_req_len;
					_rtw_memcpy(passoc_req, psta->passoc_req, assoc_req_len);
					
					rtw_mfree(psta->passoc_req , psta->assoc_req_len);
					psta->passoc_req = NULL;
					psta->assoc_req_len = 0;
				}
			}			
			_exit_critical_bh(&psta->lock, &irqL);

			if(passoc_req && assoc_req_len>0)
			{
				rtw_cfg80211_indicate_sta_assoc(adapter, passoc_req, assoc_req_len);

				rtw_mfree(passoc_req, assoc_req_len);
			}
#endif //(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37)) || defined(CONFIG_CFG80211_FORCE_COMPATIBLE_2_6_37_UNDER)
#endif //CONFIG_IOCTL_CFG80211	

			//bss_cap_update_on_sta_join(adapter, psta);
			//sta_info_update(adapter, psta);
			ap_sta_info_defer_update(adapter, psta);
		}	
		
		goto exit;
	}	
#endif	

	psta = rtw_get_stainfo(&adapter->stapriv, pstassoc->macaddr);	
	if( psta != NULL)
	{
		//the sta have been in sta_info_queue => do nothing 
		
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("Error: rtw_stassoc_event_callback: sta has been in sta_hash_queue \n"));
		
		goto exit; //(between drv has received this event before and  fw have not yet to set key to CAM_ENTRY)
	}

	psta = rtw_alloc_stainfo(&adapter->stapriv, pstassoc->macaddr);	
	if (psta == NULL) {
		RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("Can't alloc sta_info when rtw_stassoc_event_callback\n"));
		goto exit;
	}	
	
	//to do : init sta_info variable
	psta->qos_option = 0;
	psta->mac_id = (uint)pstassoc->cam_id;
	//psta->aid = (uint)pstassoc->cam_id;
	
	if(adapter->securitypriv.dot11AuthAlgrthm==dot11AuthAlgrthm_8021X)
		psta->dot118021XPrivacy = adapter->securitypriv.dot11PrivacyAlgrthm;

	psta->ieee8021x_blocked = _FALSE;		
	
	_enter_critical_bh(&pmlmepriv->lock, &irqL);

	if ( (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)==_TRUE ) || 
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)==_TRUE ) )
	{
		if(adapter->stapriv.asoc_sta_count== 2)
		{
			_enter_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
			ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
			if(ptarget_wlan)	ptarget_wlan->fixed = _TRUE;
			_exit_critical_bh(&(pmlmepriv->scanned_queue.lock), &irqL);
			// a sta + bc/mc_stainfo (not Ibss_stainfo)
			rtw_indicate_connect(adapter);
		}
	}

	_exit_critical_bh(&pmlmepriv->lock, &irqL);


	mlmeext_sta_add_event_callback(adapter, psta);
	
#ifdef CONFIG_RTL8711
	//submit SetStaKey_cmd to tell fw, fw will allocate an CAM entry for this sta	
	rtw_setstakey_cmd(adapter, (unsigned char*)psta, _FALSE);
#endif
		
exit:
	
_func_exit_;	

}