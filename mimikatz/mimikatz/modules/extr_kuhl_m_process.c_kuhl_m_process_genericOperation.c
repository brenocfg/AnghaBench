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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  char* PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int KUHL_M_PROCESS_GENERICOPERATION ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
#define  KUHL_M_PROCESS_GENERICOPERATION_RESUME 130 
#define  KUHL_M_PROCESS_GENERICOPERATION_SUSPEND 129 
#define  KUHL_M_PROCESS_GENERICOPERATION_TERMINATE 128 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtResumeProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtSuspendProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtTerminateProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenProcess (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ PROCESS_SUSPEND_RESUME ; 
 scalar_t__ PROCESS_TERMINATE ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,char*,scalar_t__) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ wcstoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_process_genericOperation(int argc, wchar_t * argv[], KUHL_M_PROCESS_GENERICOPERATION operation)
{
	HANDLE hProcess;
	NTSTATUS status = STATUS_NOT_FOUND;
	DWORD pid = 0, access;
	PCWCHAR szPid, szText;

	switch(operation)
	{
	case KUHL_M_PROCESS_GENERICOPERATION_TERMINATE:
		access = PROCESS_TERMINATE;
		szText = L"NtTerminateProcess";
		break;
	case KUHL_M_PROCESS_GENERICOPERATION_SUSPEND:
		access = PROCESS_SUSPEND_RESUME;
		szText = L"NtSuspendProcess";
		break;
	case KUHL_M_PROCESS_GENERICOPERATION_RESUME:
		access = PROCESS_SUSPEND_RESUME;
		szText = L"NtResumeProcess";
		break;
	default:
		return status;
	}

	if(kull_m_string_args_byName(argc, argv, L"pid", &szPid, NULL))
		pid = wcstoul(szPid, NULL, 0);
	
	if(pid)
	{
		if(hProcess = OpenProcess(access, FALSE, pid))
		{
			switch(operation)
			{
			case KUHL_M_PROCESS_GENERICOPERATION_TERMINATE:
				status = NtTerminateProcess(hProcess, STATUS_SUCCESS);
				break;
			case KUHL_M_PROCESS_GENERICOPERATION_SUSPEND:
				status = NtSuspendProcess(hProcess);
				break;
			case KUHL_M_PROCESS_GENERICOPERATION_RESUME:
				status = NtResumeProcess(hProcess);
				break;
			}
			
			if(NT_SUCCESS(status))
				kprintf(L"%s of %u PID : OK !\n", szText, pid);
			else PRINT_ERROR(L"%s 0x%08x\n", szText, status);
			CloseHandle(hProcess);
		}
		else PRINT_ERROR_AUTO(L"OpenProcess");
	}
	else PRINT_ERROR(L"pid (/pid:123) is missing");
	return status;
}