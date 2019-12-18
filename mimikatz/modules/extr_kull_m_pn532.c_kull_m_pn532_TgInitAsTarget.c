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
typedef  int /*<<< orphan*/  dataOut ;
typedef  int /*<<< orphan*/  dataIn ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  PKULL_M_PN532_COMM ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  PN532_CMD_TgInitAsTarget ; 
 int /*<<< orphan*/  PN532_MAX_LEN ; 
 int /*<<< orphan*/ * TgInitBaudrate ; 
 char** TgInitMode ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_pn532_TgResponseToInitiator (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_pn532_sendrecv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int*,int,int) ; 

void kull_m_pn532_TgInitAsTarget(PKULL_M_PN532_COMM comm)
{
	BYTE dataIn[] = {	0x00,
						0x04, 0x00,		0x11, 0x22, 0x33,	0x08,
						
						0x01, 0xfe, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
						0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
						0xff, 0xff,

						0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
						0x00,
						0x00,
	};
	BYTE dataOut[PN532_MAX_LEN - 2];
	UINT16 wOut = sizeof(dataOut);

	if(kull_m_pn532_sendrecv(comm, PN532_CMD_TgInitAsTarget, dataIn, sizeof(dataIn), dataOut, &wOut))
	{
		kull_m_pn532_TgResponseToInitiator(comm);
		if(wOut)
		{
			kprintf(L"Framing Type        : %s\n", ((dataOut[0] & 3) < 3) ? TgInitMode[(dataOut[0] & 3)] : L"?");
			kprintf(L"DEP                 : %s\n", (dataOut[0] & 0x04) ? L"yes": L"no");
			kprintf(L"ISO/IEC 14443-4 PICC: %s\n", (dataOut[0] & 0x08) ? L"yes": L"no");
			kprintf(L"Baudrate            : %hu\n", (((dataOut[0] & 0x70) >> 4) < 3) ? TgInitBaudrate[((dataOut[0] & 0x70) >> 4)] : 0);
			if(wOut > 1)
			{
				kprintf(L"InitiatorCommand    : ");
				kull_m_string_wprintf_hex(dataOut + 1, wOut - 1, 1);
				kprintf(L"\n");
			}
		}
	}
}