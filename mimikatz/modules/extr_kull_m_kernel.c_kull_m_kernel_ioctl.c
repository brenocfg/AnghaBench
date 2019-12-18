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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PDWORD ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kull_m_kernel_ioctl_handle (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL kull_m_kernel_ioctl(PCWSTR driver, DWORD ioctlCode, PVOID bufferIn, DWORD szBufferIn, PVOID * pBufferOut, PDWORD pSzBufferOut, BOOL autobuffer)
{
	BOOL status = FALSE;
	HANDLE hDriver;
	hDriver = CreateFile(driver, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(hDriver && hDriver != INVALID_HANDLE_VALUE)
	{
		status = kull_m_kernel_ioctl_handle(hDriver, ioctlCode, bufferIn, szBufferIn, pBufferOut, pSzBufferOut, autobuffer);
		CloseHandle(hDriver);
	}
	else
		PRINT_ERROR_AUTO(L"CreateFile");
	return status;
}