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
typedef  unsigned int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int ElementID; scalar_t__ Length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PNDIS_802_11_VARIABLE_IEs ;
typedef  int /*<<< orphan*/  NDIS_802_11_FIXED_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  AIRGOCAP_OUI ; 
 int /*<<< orphan*/  ARTHEROS_OUI1 ; 
 int /*<<< orphan*/  ARTHEROS_OUI2 ; 
 int /*<<< orphan*/  BROADCOM_OUI1 ; 
 int /*<<< orphan*/  BROADCOM_OUI2 ; 
 int /*<<< orphan*/  CISCO_OUI ; 
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  MARVELL_OUI ; 
 int /*<<< orphan*/  RALINK_OUI ; 
 int /*<<< orphan*/  REALTEK_OUI ; 
#define  _VENDOR_SPECIFIC_IE_ 128 
 int /*<<< orphan*/  _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned char airgocapAP ; 
 unsigned char atherosAP ; 
 unsigned char broadcomAP ; 
 unsigned char ciscoAP ; 
 unsigned char marvellAP ; 
 unsigned char ralinkAP ; 
 unsigned char realtekAP ; 
 unsigned char unknownAP ; 

unsigned char check_assoc_AP(u8 *pframe, uint len)
{
	unsigned int	i;
	PNDIS_802_11_VARIABLE_IEs	pIE;

	for (i = sizeof(NDIS_802_11_FIXED_IEs); i < len;)
	{
		pIE = (PNDIS_802_11_VARIABLE_IEs)(pframe + i);
		
		switch (pIE->ElementID)
		{
			case _VENDOR_SPECIFIC_IE_:
				if ((_rtw_memcmp(pIE->data, ARTHEROS_OUI1, 3)) || (_rtw_memcmp(pIE->data, ARTHEROS_OUI2, 3)))
				{
					DBG_871X("link to Artheros AP\n");
					return atherosAP;
				}
				else if ((_rtw_memcmp(pIE->data, BROADCOM_OUI1, 3))
							|| (_rtw_memcmp(pIE->data, BROADCOM_OUI2, 3))
							|| (_rtw_memcmp(pIE->data, BROADCOM_OUI2, 3)))
				{
					DBG_871X("link to Broadcom AP\n");
					return broadcomAP;
				}
				else if (_rtw_memcmp(pIE->data, MARVELL_OUI, 3))
				{
					DBG_871X("link to Marvell AP\n");
					return marvellAP;
				}
				else if (_rtw_memcmp(pIE->data, RALINK_OUI, 3))
				{
					DBG_871X("link to Ralink AP\n");
					return ralinkAP;
				}
				else if (_rtw_memcmp(pIE->data, CISCO_OUI, 3))
				{
					DBG_871X("link to Cisco AP\n");
					return ciscoAP;
				}
				else if (_rtw_memcmp(pIE->data, REALTEK_OUI, 3))
				{
					DBG_871X("link to Realtek 96B\n");
					return realtekAP;
				}
				else if (_rtw_memcmp(pIE->data, AIRGOCAP_OUI,3))
				{
					DBG_871X("link to Airgo Cap\n");
					return airgocapAP;
				}
				else
				{
					break;
				}
						
			default:
				break;
		}
				
		i += (pIE->Length + 2);
	}
	
	DBG_871X("link to new AP\n");
	return unknownAP;
}