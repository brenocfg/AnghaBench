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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_4__ {int ElementID; scalar_t__ Length; } ;
typedef  TYPE_1__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  ERP_IE_handler (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  VCS_update (int /*<<< orphan*/ *,struct sta_info*) ; 
 int WLAN_HDR_A3_LEN ; 
 int _BEACON_IE_OFFSET_ ; 
#define  _ERPINFO_IE_ 129 
#define  _HT_EXTRA_INFO_IE_ 128 
 int /*<<< orphan*/  bwmode_update_check (int /*<<< orphan*/ *,TYPE_1__*) ; 

void update_beacon_info(_adapter *padapter, u8 *pframe, uint pkt_len, struct sta_info *psta)
{
	unsigned int i;
	unsigned int len;
	PNDIS_802_11_VARIABLE_IEs	pIE;
		
#ifdef CONFIG_TDLS
	struct tdls_info *ptdlsinfo = &padapter->tdlsinfo;
	u8 tdls_prohibited[] = { 0x00, 0x00, 0x00, 0x00, 0x10 }; //bit(38): TDLS_prohibited
#endif //CONFIG_TDLS

	len = pkt_len - (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN);

	for (i = 0; i < len;)
	{
		pIE = (PNDIS_802_11_VARIABLE_IEs)(pframe + (_BEACON_IE_OFFSET_ + WLAN_HDR_A3_LEN) + i);
		
		switch (pIE->ElementID)
		{
#if 0			
			case _VENDOR_SPECIFIC_IE_:		
				//todo: to update WMM paramter set while receiving beacon			
				if (_rtw_memcmp(pIE->data, WMM_PARA_OUI, 6))	//WMM
				{
					(WMM_param_handler(padapter, pIE))? WMMOnAssocRsp(padapter): 0;
				}				
				break;
#endif

			case _HT_EXTRA_INFO_IE_:	//HT info				
				//HT_info_handler(padapter, pIE);
				bwmode_update_check(padapter, pIE);
				break;

			case _ERPINFO_IE_:
				ERP_IE_handler(padapter, pIE);
				VCS_update(padapter, psta);
				break;
				
#ifdef CONFIG_TDLS
			case _EXT_CAP_IE_:
				if( check_ap_tdls_prohibited(pIE->data, pIE->Length) == _TRUE )
					ptdlsinfo->ap_prohibited = _TRUE;
				break;
#endif //CONFIG_TDLS
			default:
				break;
		}
		
		i += (pIE->Length + 2);
	}
}