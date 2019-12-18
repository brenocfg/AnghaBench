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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  SCARDHANDLE ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int* LPCBYTE ;
typedef  scalar_t__ LONG ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__,int) ; 
 scalar_t__ SCARD_S_SUCCESS ; 
 scalar_t__ SCardControl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int*,int,int) ; 

BOOL kuhl_m_crypto_l_sc_prop_tlv_features(SCARDHANDLE hCard, DWORD ctlCode)
{
	DWORD dwRet;
	BYTE data[256];
	LPCBYTE cur;
	LONG status;

	status = SCardControl(hCard, ctlCode, NULL, 0, data, sizeof(data), &dwRet);
	if(status == SCARD_S_SUCCESS)
	{
		for(cur = data; cur < (data + dwRet); cur += cur[1] + 2)
		{
			kprintf(L"    \\ %02x - ", cur[0], cur[1]);
			switch(cur[0])
			{
			case 1:
				if(cur[1] == sizeof(USHORT))
					kprintf(L"LCD Layout: %hhux%hhu\n", cur[2], cur[3]);
				break;
			case 2:
				if(cur[1] == sizeof(BYTE))
					kprintf(L"Entry Validation Condition: 0x%02x\n", cur[2]);
				break;
			case 3:
				if(cur[1] == sizeof(BYTE))
					kprintf(L"TimeOut2: %hhu\n", cur[2]);
				break;
			case 4:
				if(cur[1] == sizeof(USHORT))
					kprintf(L"LCD Max Characters: %hu\n", *(PUSHORT) (cur + 2));
				break;
			case 5:
				if(cur[1] == sizeof(USHORT))
					kprintf(L"LCD Max Lines: %hu\n", *(PUSHORT) (cur + 2));
				break;
			case 6:
				if(cur[1] == sizeof(BYTE))
					kprintf(L"Min Pin Size: %hhu\n", cur[2]);
				break;
			case 7:
				if(cur[1] == sizeof(BYTE))
					kprintf(L"Max Pin Size: %hhu\n", cur[2]);
				break;
			case 8:
				kprintf(L"FirmwareID: %.*S\n", cur[1], cur + 2);
				break;
			case 9:
				if(cur[1] == sizeof(BYTE))
				{
					kprintf(L"PPDU Support: %s", cur[2] ? L"YES" : L"NO");
					if(cur[2] & 1)
						kprintf(L" - SCardControl(FEATURE_CCID_ESC_COMMAND)");
					if(cur[2] & 2)
						kprintf(L" - SCardTransmit");
					kprintf(L"\n");
				}
				break;
			case 0x0a:
				if(cur[1] == sizeof(DWORD))
					kprintf(L"Max APDU Data Size: %u - 0x%x\n", *(PDWORD) (cur + 2), *(PDWORD) (cur + 2));
				break;
			case 0x0b:
				if(cur[1] == sizeof(USHORT))
					kprintf(L"USB VendorID : %04x\n", *(PUSHORT) (cur + 2));
				break;
			case 0x0c:
				if(cur[1] == sizeof(USHORT))
					kprintf(L"USB ProductID: %04x\n", *(PUSHORT) (cur + 2));
				break;

			default:
				kull_m_string_wprintf_hex(cur + 2, cur[1], 1);
				kprintf(L"\n");
			}
		}
	}
	else PRINT_ERROR(L"SCardControl(!FEATURE_GET_TLV_PROPERTIES!): 0x%08x (%u)\n", status, dwRet);
	return FALSE;
}