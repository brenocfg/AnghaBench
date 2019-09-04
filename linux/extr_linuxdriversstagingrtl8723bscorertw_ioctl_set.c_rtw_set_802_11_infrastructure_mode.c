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
typedef  int u8 ;
struct TYPE_2__ {int InfrastructureMode; } ;
struct wlan_network {int join_res; TYPE_1__ network; } ;
struct mlme_priv {int /*<<< orphan*/  lock; struct wlan_network cur_network; } ;
struct adapter {struct mlme_priv mlmepriv; } ;
typedef  enum NDIS_802_11_NETWORK_INFRASTRUCTURE { ____Placeholder_NDIS_802_11_NETWORK_INFRASTRUCTURE } NDIS_802_11_NETWORK_INFRASTRUCTURE ;

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
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (struct adapter*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_ap_mode (struct adapter*) ; 
 int /*<<< orphan*/  stop_ap_mode (struct adapter*) ; 

u8 rtw_set_802_11_infrastructure_mode(struct adapter *padapter,
	enum NDIS_802_11_NETWORK_INFRASTRUCTURE networktype)
{
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct	wlan_network	*cur_network = &pmlmepriv->cur_network;
	enum NDIS_802_11_NETWORK_INFRASTRUCTURE *pold_state = &(cur_network->network.InfrastructureMode);

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_notice_,
		 ("+rtw_set_802_11_infrastructure_mode: old =%d new =%d fw_state = 0x%08x\n",
		  *pold_state, networktype, get_fwstate(pmlmepriv)));

	if (*pold_state != networktype) {
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, (" change mode!"));
		/* DBG_871X("change mode, old_mode =%d, new_mode =%d, fw_state = 0x%x\n", *pold_state, networktype, get_fwstate(pmlmepriv)); */

		if (*pold_state == Ndis802_11APMode) {
			/* change to other mode from Ndis802_11APMode */
			cur_network->join_res = -1;

			stop_ap_mode(padapter);
		}

		spin_lock_bh(&pmlmepriv->lock);

		if ((check_fwstate(pmlmepriv, _FW_LINKED) == true) || (*pold_state == Ndis802_11IBSS))
			rtw_disassoc_cmd(padapter, 0, true);

		if ((check_fwstate(pmlmepriv, _FW_LINKED) == true) ||
			(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true))
			rtw_free_assoc_resources(padapter, 1);

		if ((*pold_state == Ndis802_11Infrastructure) || (*pold_state == Ndis802_11IBSS)) {
			if (check_fwstate(pmlmepriv, _FW_LINKED) == true) {
				rtw_indicate_disconnect(padapter); /* will clr Linked_state; before this function, we must have chked whether  issue dis-assoc_cmd or not */
			}
	       }

		*pold_state = networktype;

		_clr_fwstate_(pmlmepriv, ~WIFI_NULL_STATE);

		switch (networktype) {
		case Ndis802_11IBSS:
			set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			break;

		case Ndis802_11Infrastructure:
			set_fwstate(pmlmepriv, WIFI_STATION_STATE);
			break;

		case Ndis802_11APMode:
			set_fwstate(pmlmepriv, WIFI_AP_STATE);
			start_ap_mode(padapter);
			/* rtw_indicate_connect(padapter); */

			break;

		case Ndis802_11AutoUnknown:
		case Ndis802_11InfrastructureMax:
			break;
		}

		/* SecClearAllKeys(adapter); */

		/* RT_TRACE(COMP_OID_SET, DBG_LOUD, ("set_infrastructure: fw_state:%x after changing mode\n", */
		/* 									get_fwstate(pmlmepriv))); */

		spin_unlock_bh(&pmlmepriv->lock);
	}
	return true;
}