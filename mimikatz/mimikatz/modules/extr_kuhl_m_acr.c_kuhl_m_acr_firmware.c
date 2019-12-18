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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  acrFirmware ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int BYTE ;

/* Variables and functions */
 int ARRAYSIZE (char**) ; 
 int /*<<< orphan*/  FALSE ; 
 char** KUHL_M_ACR_FIRMWARE_PN532_SUPPORT ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_acr_Comm ; 
 int /*<<< orphan*/  kuhl_m_acr_pn532Comm ; 
 scalar_t__ kull_m_acr_sendrecv_ins (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_pn532_GetFirmware (int /*<<< orphan*/ *,int*) ; 

NTSTATUS kuhl_m_acr_firmware(int argc, wchar_t * argv[])
{
	BYTE acrFirmware[10];
	BYTE firmwareInfo[4], i;
	UINT16 wOut = sizeof(acrFirmware);

	if(kull_m_acr_sendrecv_ins(&kuhl_m_acr_Comm, 0xff, 0x00, 0x48, 0x00, NULL, 0, acrFirmware, &wOut, FALSE))
		kprintf(L"ACR firmware: %.*S\n", wOut, acrFirmware);
	
	if(kull_m_pn532_GetFirmware(&kuhl_m_acr_pn532Comm, firmwareInfo))
	{
		kprintf(L"PN532 chip\n version    : 0x%02x\n firmware   : %hhu.%hhu\n support    : ", firmwareInfo[0], firmwareInfo[1], firmwareInfo[2]);
		for(i = 0; i < 8; i++)
			if((firmwareInfo[3] >> i) & 1)
				kprintf(L"%s ; ", (i < ARRAYSIZE(KUHL_M_ACR_FIRMWARE_PN532_SUPPORT)) ? KUHL_M_ACR_FIRMWARE_PN532_SUPPORT[i] : L"RFU");
		kprintf(L"\n");
	}
	return STATUS_SUCCESS;
}