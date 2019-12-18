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
typedef  int /*<<< orphan*/ * PLOGFILE ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOGFILE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  LogFileListCs ; 
 TYPE_1__ LogFileListHead ; 

PLOGFILE LogfListItemByIndex(DWORD Index)
{
    PLIST_ENTRY CurrentEntry;
    PLOGFILE Result = NULL;
    DWORD i = 1;

    EnterCriticalSection(&LogFileListCs);

    CurrentEntry = LogFileListHead.Flink;
    while (CurrentEntry != &LogFileListHead)
    {
        if (i == Index)
        {
            Result = CONTAINING_RECORD(CurrentEntry, LOGFILE, ListEntry);
            break;
        }

        CurrentEntry = CurrentEntry->Flink;
        i++;
    }

    LeaveCriticalSection(&LogFileListCs);
    return Result;
}