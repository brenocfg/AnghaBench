#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int IELength; scalar_t__ IEs; } ;
struct mlme_ext_info {TYPE_2__ network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  TYPE_2__ WLAN_BSSID_EX ;
struct TYPE_8__ {int ElementID; scalar_t__ Length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__* PNDIS_802_11_VARIABLE_IEs ;
typedef  int /*<<< orphan*/  NDIS_802_11_FIXED_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  RSN_TKIP_CIPHER ; 
 int /*<<< orphan*/  RTW_WPA_OUI ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int /*<<< orphan*/  WPA_TKIP_CIPHER ; 
 unsigned int _FALSE ; 
#define  _RSN_IE_2_ 129 
 unsigned int _TRUE ; 
#define  _VENDOR_SPECIFIC_IE_ 128 
 int /*<<< orphan*/  _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtw_get_capability (TYPE_2__*) ; 

unsigned int is_ap_in_tkip(_adapter *padapter)
{
	u32 i;
	PNDIS_802_11_VARIABLE_IEs	pIE;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX 		*cur_network = &(pmlmeinfo->network);

	if (rtw_get_capability((WLAN_BSSID_EX *)cur_network) & WLAN_CAPABILITY_PRIVACY)
	{
		for (i = sizeof(NDIS_802_11_FIXED_IEs); i < pmlmeinfo->network.IELength;)
		{
			pIE = (PNDIS_802_11_VARIABLE_IEs)(pmlmeinfo->network.IEs + i);
		
			switch (pIE->ElementID)
			{
				case _VENDOR_SPECIFIC_IE_:
					if ((_rtw_memcmp(pIE->data, RTW_WPA_OUI, 4)) && (_rtw_memcmp((pIE->data + 12), WPA_TKIP_CIPHER, 4))) 
					{
						return _TRUE;
					}
					break;
				
				case _RSN_IE_2_:
					if (_rtw_memcmp((pIE->data + 8), RSN_TKIP_CIPHER, 4)) 
					{
						return _TRUE;
					}
					
				default:
					break;
			}
		
			i += (pIE->Length + 2);
		}
		
		return _FALSE;
	}
	else
	{
		return _FALSE;
	}
	
}