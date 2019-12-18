#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Flink; } ;
typedef  int /*<<< orphan*/ * PSIDTOUSERNAME ;
typedef  TYPE_1__* PLIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/ * CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  List ; 
 int /*<<< orphan*/  PerfDataCriticalSection ; 
 int /*<<< orphan*/  SIDTOUSERNAME ; 
 TYPE_1__ SidToUserNameHead ; 
 int /*<<< orphan*/ * SystemProcessorTimeInfo ; 
 int /*<<< orphan*/ * SystemUserSid ; 
 int /*<<< orphan*/ * pPerfData ; 

void PerfDataUninitialize(void)
{
    PLIST_ENTRY pCur;
    PSIDTOUSERNAME pEntry;

    if (pPerfData != NULL)
        HeapFree(GetProcessHeap(), 0, pPerfData);

    DeleteCriticalSection(&PerfDataCriticalSection);

    if (SystemUserSid != NULL)
    {
        FreeSid(SystemUserSid);
        SystemUserSid = NULL;
    }

    /* Free user names cache list */
    pCur = SidToUserNameHead.Flink;
    while (pCur != &SidToUserNameHead)
    {
        pEntry = CONTAINING_RECORD(pCur, SIDTOUSERNAME, List);
        pCur = pCur->Flink;
        HeapFree(GetProcessHeap(), 0, pEntry);
    }

    if (SystemProcessorTimeInfo) {
        HeapFree(GetProcessHeap(), 0, SystemProcessorTimeInfo);
    }
}