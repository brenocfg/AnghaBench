#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct registry_priv {int wifi_spec; } ;
struct TYPE_5__ {scalar_t__ hw_init_completed; scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; scalar_t__ net_closed; struct registry_priv registrypriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  rtw_auto_scan_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_dynamic_chk_wk_cmd (TYPE_1__*) ; 

void rtw_dynamic_check_timer_handlder(_adapter *adapter)
{
#ifdef CONFIG_AP_MODE
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
#endif //CONFIG_AP_MODE
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
#ifdef CONFIG_CONCURRENT_MODE	
	PADAPTER pbuddy_adapter = adapter->pbuddy_adapter;	
#endif

	if(!adapter)
		return;	

	if(adapter->hw_init_completed == _FALSE)
		return;

	if ((adapter->bDriverStopped == _TRUE)||(adapter->bSurpriseRemoved== _TRUE))
		return;


#ifdef CONFIG_CONCURRENT_MODE
	if(pbuddy_adapter)
	{
		if(adapter->net_closed == _TRUE && pbuddy_adapter->net_closed == _TRUE)
		{
			return;
		}		
	}
	else
#endif //CONFIG_CONCURRENT_MODE
	if(adapter->net_closed == _TRUE)
	{
		return;
	}	

	rtw_dynamic_chk_wk_cmd(adapter);

	if(pregistrypriv->wifi_spec==1)
	{	
#ifdef CONFIG_P2P
		struct wifidirect_info *pwdinfo = &adapter->wdinfo;
		if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
#endif	
		{
			//auto site survey
			rtw_auto_scan_handler(adapter);
		}	
	}

#ifndef CONFIG_ACTIVE_KEEP_ALIVE_CHECK
#ifdef CONFIG_AP_MODE
	if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
	{
		expire_timeout_chk(adapter);
	}	
#endif
#endif //!CONFIG_ACTIVE_KEEP_ALIVE_CHECK

#ifdef CONFIG_BR_EXT

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 35))
	rcu_read_lock();
#endif	// (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 35))

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 35)) 
	if( adapter->pnetdev->br_port 
#else	// (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 35))
	if( rcu_dereference(adapter->pnetdev->rx_handler_data)
#endif	// (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 35))
		&& (check_fwstate(pmlmepriv, WIFI_STATION_STATE|WIFI_ADHOC_STATE) == _TRUE) )
	{
		// expire NAT2.5 entry
		void nat25_db_expire(_adapter *priv);
		nat25_db_expire(adapter);

		if (adapter->pppoe_connection_in_progress > 0) {
			adapter->pppoe_connection_in_progress--;
		}
		
		// due to rtw_dynamic_check_timer_handlder() is called every 2 seconds
		if (adapter->pppoe_connection_in_progress > 0) {
			adapter->pppoe_connection_in_progress--;
		}
	}

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 35))
	rcu_read_unlock();
#endif	// (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 35))

#endif	// CONFIG_BR_EXT
	
}