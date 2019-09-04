#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  int ULONG ;
struct TYPE_7__ {TYPE_1__* LastSection; TYPE_1__* FirstSection; } ;
struct TYPE_6__ {struct TYPE_6__* Prev; struct TYPE_6__* Next; scalar_t__* Name; } ;
typedef  TYPE_1__* PINICACHESECTION ;
typedef  TYPE_2__* PINICACHE ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  INICACHESECTION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
PINICACHESECTION
IniCacheAddSection(
    PINICACHE Cache,
    PCHAR Name,
    ULONG NameLength)
{
    PINICACHESECTION Section = NULL;
    ULONG i;

    if (Cache == NULL || Name == NULL || NameLength == 0)
    {
        DPRINT("Invalid parameter\n");
        return NULL;
    }

    Section = (PINICACHESECTION)RtlAllocateHeap(ProcessHeap,
                                                HEAP_ZERO_MEMORY,
                                                sizeof(INICACHESECTION));
    if (Section == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        return NULL;
    }

    /* Allocate and initialize section name */
    Section->Name = (WCHAR*)RtlAllocateHeap(ProcessHeap,
                                            0,
                                            (NameLength + 1) * sizeof(WCHAR));
    if (Section->Name == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        RtlFreeHeap(ProcessHeap, 0, Section);
        return NULL;
    }

    /* Copy section name */
    for (i = 0; i < NameLength; i++)
    {
        Section->Name[i] = (WCHAR)Name[i];
    }
    Section->Name[NameLength] = 0;

    /* Append section */
    if (Cache->FirstSection == NULL)
    {
        Cache->FirstSection = Section;
        Cache->LastSection = Section;
    }
    else
    {
        Cache->LastSection->Next = Section;
        Section->Prev = Cache->LastSection;
        Cache->LastSection = Section;
    }

    return Section;
}