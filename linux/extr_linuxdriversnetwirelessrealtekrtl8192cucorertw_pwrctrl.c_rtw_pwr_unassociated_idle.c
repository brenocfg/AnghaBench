#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_priv {int dummy; } ;
struct TYPE_4__ {scalar_t__ ips_deny_time; } ;
struct TYPE_5__ {struct mlme_priv mlmepriv; TYPE_1__ pwrctrlpriv; struct TYPE_5__* pbuddy_adapter; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_ASOC_STATE ; 
 int WIFI_SITE_MONITOR ; 
 int WIFI_UNDER_LINKING ; 
 int WIFI_UNDER_WPS ; 
 int _FALSE ; 
 int _TRUE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 scalar_t__ rtw_get_current_time () ; 

bool rtw_pwr_unassociated_idle(_adapter *adapter)
{
	_adapter *buddy = adapter->pbuddy_adapter;
	struct mlme_priv *pmlmepriv = &(adapter->mlmepriv);
#ifdef CONFIG_P2P
	struct wifidirect_info	*pwdinfo = &(adapter->wdinfo);
#ifdef CONFIG_IOCTL_CFG80211
	struct cfg80211_wifidirect_info *pcfg80211_wdinfo = &adapter->cfg80211_wdinfo;
#endif
#endif

	bool ret = _FALSE;

	if (adapter->pwrctrlpriv.ips_deny_time >= rtw_get_current_time()) {
		//DBG_871X("%s ips_deny_time\n", __func__);
		goto exit;
	}

	if (check_fwstate(pmlmepriv, WIFI_ASOC_STATE|WIFI_SITE_MONITOR)
		|| check_fwstate(pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
		|| check_fwstate(pmlmepriv, WIFI_AP_STATE)
		|| check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
		#if defined(CONFIG_P2P) && defined(CONFIG_IOCTL_CFG80211) && defined(CONFIG_P2P_IPS)
		|| pcfg80211_wdinfo->is_ro_ch
		#elif defined(CONFIG_P2P)
		|| !rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE)
		#endif
	) {
		goto exit;
	}

	/* consider buddy, if exist */
	if (buddy) {
		struct mlme_priv *b_pmlmepriv = &(buddy->mlmepriv);
		#ifdef CONFIG_P2P
		struct wifidirect_info *b_pwdinfo = &(buddy->wdinfo);
		#ifdef CONFIG_IOCTL_CFG80211		
		struct cfg80211_wifidirect_info *b_pcfg80211_wdinfo = &buddy->cfg80211_wdinfo;
		#endif
		#endif

		if (check_fwstate(b_pmlmepriv, WIFI_ASOC_STATE|WIFI_SITE_MONITOR)
			|| check_fwstate(b_pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
			|| check_fwstate(b_pmlmepriv, WIFI_AP_STATE)
			|| check_fwstate(b_pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
			#if defined(CONFIG_P2P) && defined(CONFIG_IOCTL_CFG80211) && defined(CONFIG_P2P_IPS)
			|| b_pcfg80211_wdinfo->is_ro_ch
			#elif defined(CONFIG_P2P)
			|| !rtw_p2p_chk_state(b_pwdinfo, P2P_STATE_NONE)
			#endif
		) {
			goto exit;
		}
	}

#ifdef CONFIG_INTEL_PROXIM
	if(adapter->proximity.proxim_on==_TRUE){
		return;
	}
#endif

	ret = _TRUE;

exit:
	return ret;
}