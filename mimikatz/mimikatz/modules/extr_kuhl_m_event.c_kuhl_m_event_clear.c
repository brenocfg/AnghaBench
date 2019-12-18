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
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ClearEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetNumberOfEventLogRecords (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenEventLog (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char*) ; 

NTSTATUS kuhl_m_event_clear(int argc, wchar_t * argv[])
{
	HANDLE hEventLog;
	PCWCHAR szLog;
	DWORD nbEvents;
	kull_m_string_args_byName(argc, argv, L"log", &szLog, L"Security");

	kprintf(L"Using \"%s\" event log :\n", szLog);
	if(hEventLog = OpenEventLog(NULL, szLog))
	{
		if(GetNumberOfEventLogRecords(hEventLog, &nbEvents))
			kprintf(L"- %u event(s)\n", nbEvents);
		if(ClearEventLog(hEventLog, NULL))
			kprintf(L"- Cleared !\n");
		else PRINT_ERROR_AUTO(L"ClearEventLog");
		if(GetNumberOfEventLogRecords(hEventLog, &nbEvents))
			kprintf(L"- %u event(s)\n", nbEvents);
	}
	else PRINT_ERROR_AUTO(L"OpenEventLog");

	return STATUS_SUCCESS;
}