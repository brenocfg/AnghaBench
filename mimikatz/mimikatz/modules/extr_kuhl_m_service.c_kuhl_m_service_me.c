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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ SERVICE_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * MIMIKATZ_SERVICE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  StartServiceCtrlDispatcher (TYPE_1__ const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hKiwiEventRunning ; 
 int /*<<< orphan*/ * kuhl_m_service_Main ; 

NTSTATUS kuhl_m_service_me(int argc, wchar_t * argv[])
{
	const SERVICE_TABLE_ENTRY DispatchTable[]= {{MIMIKATZ_SERVICE, kuhl_m_service_Main}, {NULL, NULL}};
	if(hKiwiEventRunning = CreateEvent(NULL, TRUE, FALSE, NULL))
	{
		StartServiceCtrlDispatcher(DispatchTable);
		CloseHandle(hKiwiEventRunning);
	}
	return STATUS_SUCCESS;
}