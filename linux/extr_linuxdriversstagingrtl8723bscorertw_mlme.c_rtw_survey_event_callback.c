#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  IEs; } ;
struct wlan_network {TYPE_3__ network; } ;
struct TYPE_9__ {scalar_t__* Ssid; scalar_t__ SsidLength; } ;
struct wlan_bssid_ex {TYPE_4__ Ssid; int /*<<< orphan*/  IEs; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  IEs; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_7__ {TYPE_1__ network; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_5__ scanned_queue; TYPE_2__ cur_network; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_add_network (struct adapter*,struct wlan_bssid_ex*) ; 
 struct wlan_network* rtw_find_network (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_survey_event_callback(struct adapter	*adapter, u8 *pbuf)
{
	u32 len;
	struct wlan_bssid_ex *pnetwork;
	struct	mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	pnetwork = (struct wlan_bssid_ex *)pbuf;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_survey_event_callback, ssid =%s\n",  pnetwork->Ssid.Ssid));

	len = get_wlan_bssid_ex_sz(pnetwork);
	if (len > (sizeof(struct wlan_bssid_ex))) {
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("\n ****rtw_survey_event_callback: return a wrong bss ***\n"));
		return;
	}


	spin_lock_bh(&pmlmepriv->lock);

	/*  update IBSS_network 's timestamp */
	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) == true) {
		/* RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,"rtw_survey_event_callback : WIFI_ADHOC_MASTER_STATE\n\n"); */
		if (!memcmp(&(pmlmepriv->cur_network.network.MacAddress), pnetwork->MacAddress, ETH_ALEN)) {
			struct wlan_network *ibss_wlan = NULL;

			memcpy(pmlmepriv->cur_network.network.IEs, pnetwork->IEs, 8);
			spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
			ibss_wlan = rtw_find_network(&pmlmepriv->scanned_queue,  pnetwork->MacAddress);
			if (ibss_wlan) {
				memcpy(ibss_wlan->network.IEs, pnetwork->IEs, 8);
				spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
				goto exit;
			}
			spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
		}
	}

	/*  lock pmlmepriv->lock when you accessing network_q */
	if ((check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) == false) {
		if (pnetwork->Ssid.Ssid[0] == 0) {
			pnetwork->Ssid.SsidLength = 0;
		}
		rtw_add_network(adapter, pnetwork);
	}

exit:

	spin_unlock_bh(&pmlmepriv->lock);

	return;
}