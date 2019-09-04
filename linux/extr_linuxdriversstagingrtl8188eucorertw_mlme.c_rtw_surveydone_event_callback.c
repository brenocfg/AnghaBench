#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wlan_bssid_ex {int /*<<< orphan*/  Ssid; int /*<<< orphan*/ * MacAddress; } ;
struct ndis_802_11_ssid {int dummy; } ;
struct mlme_priv {int to_join; scalar_t__ to_roaming; int /*<<< orphan*/  lock; int /*<<< orphan*/  assoc_ssid; int /*<<< orphan*/  assoc_timer; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  scan_to_timer; int /*<<< orphan*/ * wps_probe_req_ie; scalar_t__ wps_probe_req_ie_len; } ;
struct TYPE_2__ {struct wlan_bssid_ex dev_network; } ;
struct adapter {TYPE_1__ registrypriv; int /*<<< orphan*/  recvpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,scalar_t__) ; 
 int /*<<< orphan*/  MAX_JOIN_TIMEOUT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _FW_UNDER_SURVEY ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 int /*<<< orphan*/  indicate_wx_scan_complete_event (struct adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int rtw_createbss_cmd (struct adapter*) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*) ; 
 int /*<<< orphan*/  rtw_generate_random_ibss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_indicate_connect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_os_xmit_schedule (struct adapter*) ; 
 int rtw_select_and_join_from_scanned_queue (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_set_signal_stat_timer (int /*<<< orphan*/ *) ; 
 int rtw_sitesurvey_cmd (struct adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (struct adapter*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_surveydone_event_callback(struct adapter	*adapter, u8 *pbuf)
{
	struct	mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	spin_lock_bh(&pmlmepriv->lock);

	if (pmlmepriv->wps_probe_req_ie) {
		pmlmepriv->wps_probe_req_ie_len = 0;
		kfree(pmlmepriv->wps_probe_req_ie);
		pmlmepriv->wps_probe_req_ie = NULL;
	}

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_surveydone_event_callback: fw_state:%x\n\n", get_fwstate(pmlmepriv)));

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) {
		del_timer_sync(&pmlmepriv->scan_to_timer);
		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	} else {
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("nic status=%x, survey done event comes too late!\n", get_fwstate(pmlmepriv)));
	}

	rtw_set_signal_stat_timer(&adapter->recvpriv);

	if (pmlmepriv->to_join) {
		if ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) {
			if (check_fwstate(pmlmepriv, _FW_LINKED) == false) {
				set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

				if (rtw_select_and_join_from_scanned_queue(pmlmepriv) == _SUCCESS) {
					mod_timer(&pmlmepriv->assoc_timer,
						  jiffies + msecs_to_jiffies(MAX_JOIN_TIMEOUT));
				} else {
					struct wlan_bssid_ex    *pdev_network = &(adapter->registrypriv.dev_network);
					u8 *pibss = adapter->registrypriv.dev_network.MacAddress;

					_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);

					RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("switching to adhoc master\n"));

					memcpy(&pdev_network->Ssid, &pmlmepriv->assoc_ssid, sizeof(struct ndis_802_11_ssid));

					rtw_update_registrypriv_dev_network(adapter);
					rtw_generate_random_ibss(pibss);

					pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;

					if (rtw_createbss_cmd(adapter) != _SUCCESS)
						RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Error=>rtw_createbss_cmd status FAIL\n"));
					pmlmepriv->to_join = false;
				}
			}
		} else {
			int s_ret;

			set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
			pmlmepriv->to_join = false;
			s_ret = rtw_select_and_join_from_scanned_queue(pmlmepriv);
			if (s_ret == _SUCCESS) {
				mod_timer(&pmlmepriv->assoc_timer,
					jiffies + msecs_to_jiffies(MAX_JOIN_TIMEOUT));
			} else if (s_ret == 2) { /* there is no need to wait for join */
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
				rtw_indicate_connect(adapter);
			} else {
				DBG_88E("try_to_join, but select scanning queue fail, to_roaming:%d\n", pmlmepriv->to_roaming);
				if (pmlmepriv->to_roaming != 0) {
					if (--pmlmepriv->to_roaming == 0 ||
					    rtw_sitesurvey_cmd(adapter, &pmlmepriv->assoc_ssid, 1, NULL, 0) != _SUCCESS) {
						pmlmepriv->to_roaming = 0;
						rtw_free_assoc_resources(adapter);
						rtw_indicate_disconnect(adapter);
					} else {
						pmlmepriv->to_join = true;
					}
				}
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			}
		}
	}

	indicate_wx_scan_complete_event(adapter);

	spin_unlock_bh(&pmlmepriv->lock);

	rtw_os_xmit_schedule(adapter);
}