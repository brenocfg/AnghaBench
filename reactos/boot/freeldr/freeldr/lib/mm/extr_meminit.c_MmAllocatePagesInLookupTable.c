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
typedef  int /*<<< orphan*/  TYPE_OF_MEMORY ;
struct TYPE_2__ {size_t PageAllocationLength; int /*<<< orphan*/  PageAllocated; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PPAGE_LOOKUP_TABLE_ITEM ;
typedef  size_t PFN_NUMBER ;

/* Variables and functions */
 scalar_t__ MmLowestPhysicalPage ; 

VOID MmAllocatePagesInLookupTable(PVOID PageLookupTable, PFN_NUMBER StartPage, PFN_NUMBER PageCount, TYPE_OF_MEMORY MemoryType)
{
    PPAGE_LOOKUP_TABLE_ITEM        RealPageLookupTable = (PPAGE_LOOKUP_TABLE_ITEM)PageLookupTable;
    PFN_NUMBER                    Index;

    StartPage -= MmLowestPhysicalPage;
    for (Index=StartPage; Index<(StartPage+PageCount); Index++)
    {
        RealPageLookupTable[Index].PageAllocated = MemoryType;
        RealPageLookupTable[Index].PageAllocationLength = (Index == StartPage) ? PageCount : 0;
    }
}