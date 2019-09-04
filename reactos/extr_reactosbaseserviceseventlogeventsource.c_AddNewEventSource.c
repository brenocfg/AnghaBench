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
struct TYPE_3__ {int /*<<< orphan*/  EventSourceListEntry; int /*<<< orphan*/  szName; int /*<<< orphan*/  LogFile; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  PLOGFILE ;
typedef  TYPE_1__* PEVENTSOURCE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTSOURCE ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EventSourceListCs ; 
 int /*<<< orphan*/  EventSourceListHead ; 
 int /*<<< orphan*/  FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * szName ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
AddNewEventSource(PLOGFILE pLogFile,
                  PWSTR lpSourceName)
{
    PEVENTSOURCE lpEventSource;

    lpEventSource = HeapAlloc(GetProcessHeap(), 0,
                              FIELD_OFFSET(EVENTSOURCE, szName[wcslen(lpSourceName) + 1]));
    if (lpEventSource != NULL)
    {
        wcscpy(lpEventSource->szName, lpSourceName);
        lpEventSource->LogFile = pLogFile;

        DPRINT("Insert event source: %S\n", lpEventSource->szName);

        EnterCriticalSection(&EventSourceListCs);
        InsertTailList(&EventSourceListHead,
                       &lpEventSource->EventSourceListEntry);
        LeaveCriticalSection(&EventSourceListCs);
    }

    return (lpEventSource != NULL);
}