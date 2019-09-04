#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ Privacy; scalar_t__ InfrastructureMode; scalar_t__ IELength; scalar_t__ IEs; } ;
struct wlan_network {TYPE_2__ network; } ;
struct security_priv {scalar_t__ ndisencryptstatus; scalar_t__ ndisauthtype; } ;
struct TYPE_7__ {scalar_t__ InfrastructureMode; } ;
struct TYPE_8__ {TYPE_3__ network; } ;
struct mlme_priv {TYPE_4__ cur_network; } ;
struct TYPE_5__ {int wifi_spec; } ;
struct adapter {TYPE_1__ registrypriv; struct mlme_priv mlmepriv; struct security_priv securitypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ Ndis802_11AuthModeWPA2PSK ; 
 scalar_t__ Ndis802_11EncryptionDisabled ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_UNDER_WPS ; 
 scalar_t__ _BEACON_IE_OFFSET_ ; 
 scalar_t__ _FIXED_IE_LENGTH_ ; 
 int /*<<< orphan*/  _RSN_IE_2_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtw_get_ie (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/ * rtw_get_wps_ie (scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

int rtw_is_desired_network(struct adapter *adapter, struct wlan_network *pnetwork)
{
	struct security_priv *psecuritypriv = &adapter->securitypriv;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u32 desired_encmode;
	u32 privacy;

	/* u8 wps_ie[512]; */
	uint wps_ielen;

	int bselected = true;

	desired_encmode = psecuritypriv->ndisencryptstatus;
	privacy = pnetwork->network.Privacy;

	if (check_fwstate(pmlmepriv, WIFI_UNDER_WPS)) {
		if (rtw_get_wps_ie(pnetwork->network.IEs+_FIXED_IE_LENGTH_, pnetwork->network.IELength-_FIXED_IE_LENGTH_, NULL, &wps_ielen) != NULL)
			return true;
		else
			return false;

	}
	if (adapter->registrypriv.wifi_spec == 1) { /* for  correct flow of 8021X  to do.... */
		u8 *p = NULL;
		uint ie_len = 0;

		if ((desired_encmode == Ndis802_11EncryptionDisabled) && (privacy != 0))
	    bselected = false;

		if (psecuritypriv->ndisauthtype == Ndis802_11AuthModeWPA2PSK) {
			p = rtw_get_ie(pnetwork->network.IEs + _BEACON_IE_OFFSET_, _RSN_IE_2_, &ie_len, (pnetwork->network.IELength - _BEACON_IE_OFFSET_));
			if (p && ie_len > 0) {
				bselected = true;
			} else {
				bselected = false;
			}
		}
	}


	if ((desired_encmode != Ndis802_11EncryptionDisabled) && (privacy == 0)) {
		DBG_871X("desired_encmode: %d, privacy: %d\n", desired_encmode, privacy);
		bselected = false;
	}

	if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) {
		if (pnetwork->network.InfrastructureMode != pmlmepriv->cur_network.network.InfrastructureMode)
			bselected = false;
	}


	return bselected;
}