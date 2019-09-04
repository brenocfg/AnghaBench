#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* Data; struct TYPE_5__* Name; struct TYPE_5__* Next; } ;
typedef  TYPE_1__* PINICACHEKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
PINICACHEKEY
IniCacheFreeKey(
    PINICACHEKEY Key)
{
    PINICACHEKEY Next;

    if (Key == NULL)
        return NULL;

    Next = Key->Next;
    if (Key->Name != NULL)
    {
        RtlFreeHeap(ProcessHeap, 0, Key->Name);
        Key->Name = NULL;
    }

    if (Key->Data != NULL)
    {
        RtlFreeHeap(ProcessHeap, 0, Key->Data);
        Key->Data = NULL;
    }

    RtlFreeHeap(ProcessHeap, 0, Key);

    return Next;
}