#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG64 ;
typedef  size_t ULONG ;
struct TYPE_10__ {scalar_t__ PageFrameNumber; int /*<<< orphan*/  Valid; } ;
struct TYPE_9__ {int /*<<< orphan*/  Valid; scalar_t__ PageFrameNumber; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PHARDWARE_PTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PAGE_SIZE ; 
 TYPE_7__* PxeBase ; 
 int /*<<< orphan*/  TRUE ; 
 size_t VAtoPDI (TYPE_1__*) ; 
 size_t VAtoPPI (TYPE_1__*) ; 
 size_t VAtoPTI (TYPE_1__*) ; 
 size_t VAtoPXI (TYPE_1__*) ; 

BOOLEAN
MempIsPageMapped(PVOID VirtualAddress)
{
    PHARDWARE_PTE PpeBase, PdeBase, PteBase;
    ULONG Index;

    Index = VAtoPXI(VirtualAddress);
    if (!PxeBase[Index].Valid)
        return FALSE;

    PpeBase = (PVOID)((ULONG64)(PxeBase[Index].PageFrameNumber) * PAGE_SIZE);
    Index = VAtoPPI(VirtualAddress);
    if (!PpeBase[Index].Valid)
        return FALSE;

    PdeBase = (PVOID)((ULONG64)(PpeBase[Index].PageFrameNumber) * PAGE_SIZE);
    Index = VAtoPDI(VirtualAddress);
    if (!PdeBase[Index].Valid)
        return FALSE;

    PteBase = (PVOID)((ULONG64)(PdeBase[Index].PageFrameNumber) * PAGE_SIZE);
    Index = VAtoPTI(VirtualAddress);
    if (!PteBase[Index].Valid)
        return FALSE;

    return TRUE;
}