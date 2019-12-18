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
typedef  int /*<<< orphan*/  temoin ;
typedef  int USHORT ;
typedef  int* PUSHORT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  SR98_IOCTL_TEST_DEVICE ; 
 int _byteswap_ushort (int) ; 
 scalar_t__ sr98_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int**,int*) ; 

BOOL sr98_test_device(HANDLE hFile)
{
	BOOL status = FALSE;
	USHORT temoin = 'BB';
	BYTE *out, szOut;
	if(sr98_send_receive(hFile, SR98_IOCTL_TEST_DEVICE, &temoin, sizeof(temoin), &out, &szOut))
	{
		if(szOut == sizeof(USHORT))
		{
			if(!(status = *((PUSHORT) out) == (temoin | 0x0100)))
				PRINT_ERROR(L"Received data is not origin+1 (0x%04x)\n", _byteswap_ushort(*((PUSHORT) out)));
		}
		else PRINT_ERROR(L"Received size is not 2 (0x%02x)\n", szOut);
		LocalFree(out);
	}
	return status;
}