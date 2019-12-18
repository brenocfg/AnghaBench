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

/* Variables and functions */
 scalar_t__ LoaderFree ; 
 scalar_t__ MmFindAvailablePages (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MmLowestPhysicalPage ; 
 int /*<<< orphan*/  TRUE ; 

PFN_NUMBER MmFindAvailablePagesBeforePage(PVOID PageLookupTable, PFN_NUMBER TotalPageCount, PFN_NUMBER PagesNeeded, PFN_NUMBER LastPage)
{
    PPAGE_LOOKUP_TABLE_ITEM        RealPageLookupTable = (PPAGE_LOOKUP_TABLE_ITEM)PageLookupTable;
    PFN_NUMBER                    AvailablePagesSoFar;
    PFN_NUMBER                    Index;

    if (LastPage > TotalPageCount)
    {
        return MmFindAvailablePages(PageLookupTable, TotalPageCount, PagesNeeded, TRUE);
    }

    AvailablePagesSoFar = 0;
    for (Index=LastPage-1; Index>0; Index--)
    {
        if (RealPageLookupTable[Index].PageAllocated != LoaderFree)
        {
            AvailablePagesSoFar = 0;
            continue;
        }
        else
        {
            AvailablePagesSoFar++;
        }

        if (AvailablePagesSoFar >= PagesNeeded)
        {
            return Index + MmLowestPhysicalPage;
        }
    }

    return 0;
}