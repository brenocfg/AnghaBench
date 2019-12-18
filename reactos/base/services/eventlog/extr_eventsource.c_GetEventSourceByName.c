#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* szName; } ;
struct TYPE_11__ {struct TYPE_11__* Flink; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  TYPE_2__* PEVENTSOURCE ;
typedef  TYPE_2__* LPCWSTR ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  EVENTSOURCE ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EventSourceListCs ; 
 int /*<<< orphan*/  EventSourceListEntry ; 
 TYPE_1__ EventSourceListHead ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsicmp (TYPE_2__*,TYPE_2__*) ; 

PEVENTSOURCE
GetEventSourceByName(LPCWSTR Name)
{
    PLIST_ENTRY CurrentEntry;
    PEVENTSOURCE Item, Result = NULL;

    DPRINT("GetEventSourceByName(%S)\n", Name);
    EnterCriticalSection(&EventSourceListCs);

    CurrentEntry = EventSourceListHead.Flink;
    while (CurrentEntry != &EventSourceListHead)
    {
        Item = CONTAINING_RECORD(CurrentEntry,
                                 EVENTSOURCE,
                                 EventSourceListEntry);

        DPRINT("Item->szName: %S\n", Item->szName);
//        if ((*(Item->szName) != 0) && !_wcsicmp(Item->szName, Name))
        if (_wcsicmp(Item->szName, Name) == 0)
        {
            DPRINT("Found it\n");
            Result = Item;
            break;
        }

        CurrentEntry = CurrentEntry->Flink;
    }

    LeaveCriticalSection(&EventSourceListCs);

    DPRINT("Done (Result: %p)\n", Result);

    return Result;
}