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
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

BOOL kull_m_pipe_read(HANDLE hPipe, LPBYTE *buffer, DWORD *size)
{
	BOOL status = FALSE;
	DWORD szReaded, szBuffer = 0;
	BYTE * tmpBuffer = NULL; DWORD szTmpBuffer = 0;

	*size = 0;
	*buffer = NULL;
	do
	{
		if(*buffer)
		{
			tmpBuffer = *buffer;
			szTmpBuffer = szBuffer;
		}
	
		szBuffer += 2048;
		if(*buffer = (BYTE *) LocalAlloc(LPTR, szBuffer))
		{
			if(tmpBuffer)
			{
				RtlCopyMemory(*buffer, tmpBuffer, szTmpBuffer);
				tmpBuffer = (BYTE *) LocalFree(tmpBuffer);
			}

			if(status = ReadFile(hPipe, *buffer + szTmpBuffer, 2048, &szReaded, NULL))
			{
				*size = szTmpBuffer + szReaded;
				break;
			}
		}
	} while(GetLastError() == ERROR_MORE_DATA);

	if(!status)
	{
		PRINT_ERROR_AUTO(L"ReadFile");
		*buffer = (BYTE *) LocalFree(*buffer);
		*size = 0;
	}
	return status;
}