#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* Key; TYPE_1__* Section; } ;
struct TYPE_7__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  Name; } ;
struct TYPE_6__ {TYPE_2__* FirstKey; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  TYPE_1__* PINICACHESECTION ;
typedef  TYPE_2__* PINICACHEKEY ;
typedef  TYPE_3__* PINICACHEITERATOR ;
typedef  int /*<<< orphan*/  INICACHEITERATOR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

PINICACHEITERATOR
IniCacheFindFirstValue(
    PINICACHESECTION Section,
    PWCHAR *KeyName,
    PWCHAR *KeyData)
{
    PINICACHEITERATOR Iterator;
    PINICACHEKEY Key;

    if (Section == NULL || KeyName == NULL || KeyData == NULL)
    {
        DPRINT("Invalid parameter\n");
        return NULL;
    }

    Key = Section->FirstKey;
    if (Key == NULL)
    {
        DPRINT("Invalid parameter\n");
        return NULL;
    }

    *KeyName = Key->Name;
    *KeyData = Key->Data;

    Iterator = (PINICACHEITERATOR)RtlAllocateHeap(ProcessHeap,
                                                  0,
                                                  sizeof(INICACHEITERATOR));
    if (Iterator == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        return NULL;
    }

    Iterator->Section = Section;
    Iterator->Key = Key;

    return Iterator;
}