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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_LOGON_FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ LOGONID_CURRENT ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  SERVERHANDLE_CURRENT ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ WinStationConnectW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,scalar_t__*,char*) ; 
 scalar_t__ wcstoul (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_ts_remote(int argc, wchar_t * argv[])
{
	LPCWSTR szId, szPassword;
	DWORD id, target;
	if(kull_m_string_args_byName(argc, argv, L"id", &szId, NULL))
	{
		id = wcstoul(szId, NULL, 0);
		if(kull_m_string_args_byName(argc, argv, L"target", &szId, NULL))
			target = wcstoul(szId, NULL, 0);
		else target = LOGONID_CURRENT;
		
		kull_m_string_args_byName(argc, argv, L"password", &szPassword, L"");

		kprintf(L"Asking to connect from %u to ", id);
		if(target == LOGONID_CURRENT)
			kprintf(L"current session");
		else kprintf(L"%u", target);
		
		kprintf(L"\n\n> ");
		if(WinStationConnectW(SERVERHANDLE_CURRENT, id, target, (LPWSTR) szPassword, FALSE))
			kprintf(L"Connected to %u\n", id);
		else if(GetLastError() == ERROR_LOGON_FAILURE)
			PRINT_ERROR(L"Bad password for this session (take care to not lock the account!)\n");
		else PRINT_ERROR_AUTO(L"WinStationConnect");
	}
	else PRINT_ERROR(L"Argument id is needed\n");
	return STATUS_SUCCESS;
}