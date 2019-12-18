#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  TYPE_OF_MEMORY ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ PFN_NUMBER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FreePagesInLookupTable ; 
 scalar_t__ LoaderPagesSpanned ; 
 scalar_t__ MM_PAGE_SIZE ; 
 int /*<<< orphan*/  MmAllocatePagesInLookupTable (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MmFindAvailablePagesBeforePage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  PageLookupTableAddress ; 
 scalar_t__ ROUND_UP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  TotalPagesInLookupTable ; 
 int /*<<< orphan*/  UiMessageBoxCritical (char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 

PVOID MmAllocateHighestMemoryBelowAddress(SIZE_T MemorySize, PVOID DesiredAddress, TYPE_OF_MEMORY MemoryType)
{
    PFN_NUMBER        PagesNeeded;
    PFN_NUMBER        FirstFreePageFromEnd;
    PFN_NUMBER        DesiredAddressPageNumber;
    PVOID    MemPointer;

    if (MemorySize == 0)
    {
        WARN("MmAllocateHighestMemoryBelowAddress() called for 0 bytes. Returning NULL.\n");
        UiMessageBoxCritical("Memory allocation failed: MmAllocateHighestMemoryBelowAddress() called for 0 bytes.");
        return NULL;
    }

    // Find out how many blocks it will take to
    // satisfy this allocation
    PagesNeeded = ROUND_UP(MemorySize, MM_PAGE_SIZE) / MM_PAGE_SIZE;

    // Get the page number for their desired address
    DesiredAddressPageNumber = (ULONG_PTR)DesiredAddress / MM_PAGE_SIZE;

    // If we don't have enough available mem
    // then return NULL
    if (FreePagesInLookupTable < PagesNeeded)
    {
        ERR("Memory allocation failed in MmAllocateHighestMemoryBelowAddress(). Not enough free memory to allocate %d bytes.\n", MemorySize);
        UiMessageBoxCritical("Memory allocation failed: out of memory.");
        return NULL;
    }

    FirstFreePageFromEnd = MmFindAvailablePagesBeforePage(PageLookupTableAddress, TotalPagesInLookupTable, PagesNeeded, DesiredAddressPageNumber);

    if (FirstFreePageFromEnd == 0)
    {
        ERR("Memory allocation failed in MmAllocateHighestMemoryBelowAddress(). Not enough free memory to allocate %d bytes.\n", MemorySize);
        UiMessageBoxCritical("Memory allocation failed: out of memory.");
        return NULL;
    }

    MmAllocatePagesInLookupTable(PageLookupTableAddress, FirstFreePageFromEnd, PagesNeeded, MemoryType);

    FreePagesInLookupTable -= PagesNeeded;
    MemPointer = (PVOID)((ULONG_PTR)FirstFreePageFromEnd * MM_PAGE_SIZE);

    TRACE("Allocated %d bytes (%d pages) of memory starting at page %d.\n", MemorySize, PagesNeeded, FirstFreePageFromEnd);
    TRACE("Memory allocation pointer: 0x%x\n", MemPointer);

    // Update LoaderPagesSpanned count
    if ((((ULONG_PTR)MemPointer + MemorySize) >> PAGE_SHIFT) > LoaderPagesSpanned)
        LoaderPagesSpanned = (((ULONG_PTR)MemPointer + MemorySize) >> PAGE_SHIFT);

    // Now return the pointer
    return MemPointer;
}