#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dwProcessId; } ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  PKULL_M_MEMORY_HANDLE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KULL_M_MEMORY_TYPE_PROCESS ; 
 int /*<<< orphan*/  OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kull_m_memory_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_service_getUniqueForName (char*,TYPE_1__*) ; 

BOOL kuhl_m_lsadump_lsa_getHandle(PKULL_M_MEMORY_HANDLE * hMemory, DWORD Flags)
{
	BOOL success = FALSE;
	SERVICE_STATUS_PROCESS ServiceStatusProcess;
	HANDLE hProcess;

	if(kull_m_service_getUniqueForName(L"SamSs", &ServiceStatusProcess))
	{
		if(hProcess = OpenProcess(Flags, FALSE, ServiceStatusProcess.dwProcessId))
		{
			if(!(success = kull_m_memory_open(KULL_M_MEMORY_TYPE_PROCESS, hProcess, hMemory)))
				CloseHandle(hProcess);
		}
		else PRINT_ERROR_AUTO(L"OpenProcess");
	}
	else PRINT_ERROR_AUTO(L"kull_m_service_getUniqueForName");
	return success;
}