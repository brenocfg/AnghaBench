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
struct TYPE_4__ {scalar_t__ MemoryType; int PageCount; int BasePage; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int PFN_NUMBER ;
typedef  int /*<<< orphan*/  PAGE_LOOKUP_TABLE_ITEM ;
typedef  TYPE_1__ FREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 TYPE_1__* ArcGetMemoryDescriptor (TYPE_1__ const*) ; 
 scalar_t__ LoaderFree ; 
 scalar_t__ MM_MAX_PAGE ; 
 int MM_PAGE_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int min (int,scalar_t__) ; 

PVOID MmFindLocationForPageLookupTable(PFN_NUMBER TotalPageCount)
{
    const FREELDR_MEMORY_DESCRIPTOR* MemoryDescriptor = NULL;
    SIZE_T PageLookupTableSize;
    PFN_NUMBER RequiredPages;
    PFN_NUMBER CandidateBasePage = 0;
    PFN_NUMBER CandidatePageCount;
    PFN_NUMBER PageLookupTableEndPage;
    PVOID PageLookupTableMemAddress = NULL;

    // Calculate how much pages we need to keep the page lookup table
    PageLookupTableSize = TotalPageCount * sizeof(PAGE_LOOKUP_TABLE_ITEM);
    RequiredPages = PageLookupTableSize / MM_PAGE_SIZE;

    // Search the highest memory block big enough to contain lookup table
    while ((MemoryDescriptor = ArcGetMemoryDescriptor(MemoryDescriptor)) != NULL)
    {
        // Continue, if memory is not free
        if (MemoryDescriptor->MemoryType != LoaderFree) continue;

        // Continue, if the block is not big enough
        if (MemoryDescriptor->PageCount < RequiredPages) continue;

        // Continue, if it is not at a higher address than previous address
        if (MemoryDescriptor->BasePage < CandidateBasePage) continue;

        // Continue, if the address is too high
        if (MemoryDescriptor->BasePage + RequiredPages >= MM_MAX_PAGE) continue;

        // Memory block is more suitable than the previous one
        CandidateBasePage = MemoryDescriptor->BasePage;
        CandidatePageCount = MemoryDescriptor->PageCount;
    }

    // Calculate the end address for the lookup table
    PageLookupTableEndPage = min(CandidateBasePage + CandidatePageCount,
                                 MM_MAX_PAGE);

    // Calculate the virtual address
    PageLookupTableMemAddress = (PVOID)((PageLookupTableEndPage * PAGE_SIZE)
                                        - PageLookupTableSize);

    TRACE("MmFindLocationForPageLookupTable() returning 0x%x\n", PageLookupTableMemAddress);

    return PageLookupTableMemAddress;
}