#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* Flink; } ;
struct TYPE_7__ {scalar_t__ LogName; } ;
typedef  TYPE_1__* PLOGFILE ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOGFILE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  LogFileListCs ; 
 TYPE_2__ LogFileListHead ; 
 int /*<<< orphan*/  _wcsicmp (scalar_t__,int /*<<< orphan*/ ) ; 

PLOGFILE LogfListItemByName(LPCWSTR Name)
{
    PLIST_ENTRY CurrentEntry;
    PLOGFILE Item, Result = NULL;

    ASSERT(Name);

    EnterCriticalSection(&LogFileListCs);

    CurrentEntry = LogFileListHead.Flink;
    while (CurrentEntry != &LogFileListHead)
    {
        Item = CONTAINING_RECORD(CurrentEntry, LOGFILE, ListEntry);

        if (Item->LogName && !_wcsicmp(Item->LogName, Name))
        {
            Result = Item;
            break;
        }

        CurrentEntry = CurrentEntry->Flink;
    }

    LeaveCriticalSection(&LogFileListCs);
    return Result;
}