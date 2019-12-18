#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_2__ {size_t PageFrameNumber; int Valid; int Write; } ;
typedef  scalar_t__ PHARDWARE_PTE ;

/* Variables and functions */
 int KSEG0_BASE ; 
 size_t KernelPageTables ; 
 int /*<<< orphan*/ * KernelPageTablesBuffer ; 
 size_t MM_PAGE_SHIFT ; 
 size_t MM_PAGE_SIZE ; 
 TYPE_1__* PDE ; 
 size_t PhysicalPageTables ; 
 int /*<<< orphan*/ * PhysicalPageTablesBuffer ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 

__attribute__((used)) static
VOID
MempAllocatePTE(ULONG Entry, PHARDWARE_PTE *PhysicalPT, PHARDWARE_PTE *KernelPT)
{
    //Print(L"Creating PDE Entry %X\n", Entry);

    // Identity mapping
    *PhysicalPT = (PHARDWARE_PTE)&PhysicalPageTablesBuffer[PhysicalPageTables*MM_PAGE_SIZE];
    PhysicalPageTables++;

    PDE[Entry].PageFrameNumber = (ULONG)*PhysicalPT >> MM_PAGE_SHIFT;
    PDE[Entry].Valid = 1;
    PDE[Entry].Write = 1;

    if (Entry+(KSEG0_BASE >> 22) > 1023)
    {
        TRACE("WARNING! Entry: %X > 1023\n", Entry+(KSEG0_BASE >> 22));
    }

    // Kernel-mode mapping
    *KernelPT = (PHARDWARE_PTE)&KernelPageTablesBuffer[KernelPageTables*MM_PAGE_SIZE];
    KernelPageTables++;

    PDE[Entry+(KSEG0_BASE >> 22)].PageFrameNumber = ((ULONG)*KernelPT >> MM_PAGE_SHIFT);
    PDE[Entry+(KSEG0_BASE >> 22)].Valid = 1;
    PDE[Entry+(KSEG0_BASE >> 22)].Write = 1;
}