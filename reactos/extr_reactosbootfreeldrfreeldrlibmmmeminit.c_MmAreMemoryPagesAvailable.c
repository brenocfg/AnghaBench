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
struct TYPE_2__ {scalar_t__ PageAllocated; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PPAGE_LOOKUP_TABLE_ITEM ;
typedef  scalar_t__ PFN_NUMBER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LoaderFree ; 
 scalar_t__ MmGetPageNumberFromAddress (int /*<<< orphan*/ ) ; 
 scalar_t__ MmLowestPhysicalPage ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN MmAreMemoryPagesAvailable(PVOID PageLookupTable, PFN_NUMBER TotalPageCount, PVOID PageAddress, PFN_NUMBER PageCount)
{
    PPAGE_LOOKUP_TABLE_ITEM        RealPageLookupTable = (PPAGE_LOOKUP_TABLE_ITEM)PageLookupTable;
    PFN_NUMBER                            StartPage;
    PFN_NUMBER                            Index;

    StartPage = MmGetPageNumberFromAddress(PageAddress);

    if (StartPage < MmLowestPhysicalPage) return FALSE;

    StartPage -= MmLowestPhysicalPage;

    // Make sure they aren't trying to go past the
    // end of available memory
    if ((StartPage + PageCount) > TotalPageCount)
    {
        return FALSE;
    }

    for (Index = StartPage; Index < (StartPage + PageCount); Index++)
    {
        // If this page is allocated then there obviously isn't
        // memory available so return FALSE
        if (RealPageLookupTable[Index].PageAllocated != LoaderFree)
        {
            return FALSE;
        }
    }

    return TRUE;
}