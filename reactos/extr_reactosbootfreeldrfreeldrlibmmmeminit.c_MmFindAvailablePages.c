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
typedef  int PFN_NUMBER ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int LastFreePageHint ; 
 scalar_t__ LoaderFree ; 
 int MmLowestPhysicalPage ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 

PFN_NUMBER MmFindAvailablePages(PVOID PageLookupTable, PFN_NUMBER TotalPageCount, PFN_NUMBER PagesNeeded, BOOLEAN FromEnd)
{
    PPAGE_LOOKUP_TABLE_ITEM RealPageLookupTable = (PPAGE_LOOKUP_TABLE_ITEM)PageLookupTable;
    PFN_NUMBER AvailablePagesSoFar;
    PFN_NUMBER Index;

    if (LastFreePageHint > TotalPageCount)
    {
        LastFreePageHint = TotalPageCount;
    }

    AvailablePagesSoFar = 0;
    if (FromEnd)
    {
        /* Allocate "high" (from end) pages */
        for (Index=LastFreePageHint-1; Index>0; Index--)
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
    }
    else
    {
        TRACE("Alloc low memory, LastFreePageHint 0x%x, TPC 0x%x\n", LastFreePageHint, TotalPageCount);
        /* Allocate "low" pages */
        for (Index=1; Index < LastFreePageHint; Index++)
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
                return Index - AvailablePagesSoFar + 1 + MmLowestPhysicalPage;
            }
        }
    }

    return 0;
}