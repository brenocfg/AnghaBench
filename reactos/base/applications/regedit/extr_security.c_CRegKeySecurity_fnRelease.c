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
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__* PCRegKeySecurity ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline ULONG
CRegKeySecurity_fnRelease(PCRegKeySecurity obj)
{
    ULONG Ret;

    Ret = (ULONG)InterlockedDecrement((LONG*)&obj->ref);
    if (Ret == 0)
    {
        HeapFree(GetProcessHeap(),
                 0,
                 obj);
    }

    return Ret;
}