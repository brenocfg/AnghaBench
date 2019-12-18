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
typedef  scalar_t__ PCHAR ;
typedef  int* PBYTE ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int sprintf_s (scalar_t__,int,char*,int) ; 

BOOL dataToHexWithoutNull(LPCVOID data, DWORD dwData, LPBYTE dest, DWORD dwDest)
{
	BOOL status = FALSE;
	PCHAR buffer;
	DWORD dwBuffer = dwData * 2 + 1, i;
	if(dwDest >= (dwData * 2))
	{
		if(buffer = (PCHAR) LocalAlloc(LPTR, dwBuffer))
		{
			for(i = 0; i < dwData; i++)
				if(sprintf_s(buffer + i * 2, dwBuffer - i * 2, "%02x", ((PBYTE) data)[i]) < 2)
					break;
			if(status = (i == dwData))
				RtlCopyMemory(dest, buffer, dwBuffer - 1);
			LocalFree(buffer);
		}
	}
	return status;
}