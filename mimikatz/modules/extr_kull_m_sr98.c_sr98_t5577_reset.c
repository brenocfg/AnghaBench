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
typedef  int /*<<< orphan*/  inBuffer ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  SR98_IOCTL_T5577 ; 
 int SR98_SUB_IOCTL_T5577_RESET ; 
 scalar_t__ sr98_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int**,int*) ; 

BOOL sr98_t5577_reset(HANDLE hFile, BYTE DataRate)
{
	BYTE inBuffer[5] = {SR98_SUB_IOCTL_T5577_RESET, DataRate & 0x0b}, *out, szOut;
	if(sr98_send_receive(hFile, SR98_IOCTL_T5577, inBuffer, sizeof(inBuffer), &out, &szOut))
	{
		if(szOut == 1)
		{
			if(*out)
				PRINT_ERROR(L"Data size is not 0 (0x%02x)\n", *out);
		}
		else PRINT_ERROR(L"Received size is not 1 (0x%02x)\n", szOut);
	}
	return FALSE;
}