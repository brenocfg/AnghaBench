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
typedef  int /*<<< orphan*/  blockContent ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  SR98_IOCTL_T5577 ; 
 int SR98_SUB_IOCTL_T5577_WRITE_BLOCK ; 
 int SR98_SUB_IOCTL_T5577_WRITE_BLOCK_PASS ; 
 scalar_t__ sr98_send_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int**,int*) ; 

BOOL sr98_t5577_write_block(HANDLE hFile, BYTE page, BYTE block, DWORD data, BYTE isPassword, DWORD password/*, BYTE lockBit*/)
{
	BOOL status = FALSE;
	BYTE blockContent[11], *out, szOut;

	blockContent[0] = SR98_SUB_IOCTL_T5577_WRITE_BLOCK;
	blockContent[1] = page & 1;
	//if(lockBit) // ????
	//	blockContent[1] |= SR98_T5577_LOCKBIT_MASK

	*(PDWORD) (blockContent + 2) = data;
	blockContent[6] = block & 7;

	if(isPassword)
	{
		blockContent[0] = SR98_SUB_IOCTL_T5577_WRITE_BLOCK_PASS;
		*(PDWORD) (blockContent + 7) = password;
	}

	if(sr98_send_receive(hFile, SR98_IOCTL_T5577, blockContent, isPassword ? sizeof(blockContent) : sizeof(blockContent) - sizeof(DWORD), &out, &szOut))
	{
		if(szOut == 1)
		{
			if(!(status = (*out == sizeof(DWORD))))
				PRINT_ERROR(L"Received data size is not 4 (0x%02x)\n", *out);
		}
		else PRINT_ERROR(L"Received size is not 1 (0x%02x)\n", szOut);
		LocalFree(out);
	}
	return status;
}