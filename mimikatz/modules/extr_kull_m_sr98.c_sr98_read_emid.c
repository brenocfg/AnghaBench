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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,int*,int) ; 
 int /*<<< orphan*/  SR98_IOCTL_EMID_READ ; 
 scalar_t__ sr98_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int**,int*) ; 

BOOL sr98_read_emid(HANDLE hFile, BYTE emid[5])
{
	BOOL status = FALSE;
	BYTE *out, szOut;
	if(sr98_send_receive(hFile, SR98_IOCTL_EMID_READ, NULL, 0, &out, &szOut))
	{
		if(status = (szOut == 6))
			RtlCopyMemory(emid, out + 1, 5);
		else PRINT_ERROR(L"Received size is not 6 (0x%02x)\n", szOut);
		LocalFree(out);
	}
	return status;
}