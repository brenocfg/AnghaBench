#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct wlan_bssid_ex {int IELength; scalar_t__ IEs; } ;
struct ndis_802_11_fix_ie {int dummy; } ;
struct ndis_80211_var_ie {int ElementID; scalar_t__ Length; int /*<<< orphan*/  data; } ;
struct mlme_ext_info {struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSN_TKIP_CIPHER ; 
 int /*<<< orphan*/  RTW_WPA_OUI ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  WPA_TKIP_CIPHER ; 
#define  _RSN_IE_2_ 129 
#define  _VENDOR_SPECIFIC_IE_ 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtw_get_capability (struct wlan_bssid_ex*) ; 

unsigned int is_ap_in_tkip(struct adapter *padapter)
{
	u32 i;
	struct ndis_80211_var_ie *pIE;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex		*cur_network = &(pmlmeinfo->network);

	if (rtw_get_capability((struct wlan_bssid_ex *)cur_network) & WLAN_CAPABILITY_PRIVACY) {
		for (i = sizeof(struct ndis_802_11_fix_ie); i < pmlmeinfo->network.IELength;) {
			pIE = (struct ndis_80211_var_ie *)(pmlmeinfo->network.IEs + i);

			switch (pIE->ElementID) {
			case _VENDOR_SPECIFIC_IE_:
				if ((!memcmp(pIE->data, RTW_WPA_OUI, 4)) && (!memcmp((pIE->data + 12), WPA_TKIP_CIPHER, 4)))
					return true;

				break;

			case _RSN_IE_2_:
				if (!memcmp((pIE->data + 8), RSN_TKIP_CIPHER, 4))
					return true;

			default:
				break;
			}

			i += (pIE->Length + 2);
		}

		return false;
	} else
		return false;
}