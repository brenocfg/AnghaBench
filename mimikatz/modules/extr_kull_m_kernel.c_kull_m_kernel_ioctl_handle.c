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
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeviceIoControl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__,scalar_t__) ; 

BOOL kull_m_kernel_ioctl_handle(HANDLE hDriver, DWORD ioctlCode, PVOID bufferIn, DWORD szBufferIn, PVOID * pBufferOut, PDWORD pSzBufferOut, BOOL autobuffer)
{
	BOOL status = FALSE;
	DWORD lStatus = ERROR_MORE_DATA, returned;

	if(!autobuffer)
	{
		status = DeviceIoControl(hDriver, ioctlCode, bufferIn, szBufferIn, pBufferOut ? *pBufferOut : NULL, pSzBufferOut ? *pSzBufferOut : 0, &returned, NULL);
	}
	else
	{
		for(*pSzBufferOut = 0x10000; (lStatus == ERROR_MORE_DATA) && (*pBufferOut = LocalAlloc(LPTR, *pSzBufferOut)) ; *pSzBufferOut <<= 1)
		{
			if(status = DeviceIoControl(hDriver, ioctlCode, bufferIn, szBufferIn, *pBufferOut, *pSzBufferOut, &returned, NULL))
			{
				lStatus = ERROR_SUCCESS;
			}
			else
			{
				lStatus = GetLastError();
				if(lStatus == ERROR_MORE_DATA)
					LocalFree(*pBufferOut);
			}
		}
	}
	if(!status)
	{
		PRINT_ERROR(L"DeviceIoControl (0x%08x) : 0x%08x\n", ioctlCode, GetLastError());
		if(autobuffer)
			LocalFree(*pBufferOut);
	}
	else if(pSzBufferOut)
		*pSzBufferOut = returned;
	return status;
}