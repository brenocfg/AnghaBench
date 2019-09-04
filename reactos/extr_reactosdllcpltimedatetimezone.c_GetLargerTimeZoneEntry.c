#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Bias; } ;
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/  Description; TYPE_1__ TimezoneInfo; } ;
typedef  TYPE_2__* PTIMEZONE_ENTRY ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 TYPE_2__* TimeZoneListHead ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
PTIMEZONE_ENTRY
GetLargerTimeZoneEntry(
    LONG Bias,
    LPWSTR lpDescription)
{
    PTIMEZONE_ENTRY Entry;

    Entry = TimeZoneListHead;
    while (Entry != NULL)
    {
        if (Entry->TimezoneInfo.Bias < Bias)
            return Entry;

        if (Entry->TimezoneInfo.Bias == Bias)
        {
            if (_wcsicmp(Entry->Description, lpDescription) > 0)
                return Entry;
        }

        Entry = Entry->Next;
    }

    return NULL;
}