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
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  TYPE_OF_MEMORY ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ PFN_NUMBER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FreePagesInLookupTable ; 
 int LoaderPagesSpanned ; 
 int MM_PAGE_SIZE ; 
 int /*<<< orphan*/  MmAllocatePagesInLookupTable (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MmFindAvailablePages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageLookupTableAddress ; 
 int ROUND_UP (int,int) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TotalPagesInLookupTable ; 
 int /*<<< orphan*/  UiMessageBoxCritical (char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 

PVOID MmAllocateMemoryWithType(SIZE_T MemorySize, TYPE_OF_MEMORY MemoryType)
{
    PFN_NUMBER    PagesNeeded;
    PFN_NUMBER    FirstFreePageFromEnd;
    PVOID    MemPointer;

    if (MemorySize == 0)
    {
        WARN("MmAllocateMemory() called for 0 bytes. Returning NULL.\n");
        UiMessageBoxCritical("Memory allocation failed: MmAllocateMemory() called for 0 bytes.");
        return NULL;
    }

    MemorySize = ROUND_UP(MemorySize, 4);

    // Find out how many blocks it will take to
    // satisfy this allocation
    PagesNeeded = ROUND_UP(MemorySize, MM_PAGE_SIZE) / MM_PAGE_SIZE;

    // If we don't have enough available mem
    // then return NULL
    if (FreePagesInLookupTable < PagesNeeded)
    {
        ERR("Memory allocation failed in MmAllocateMemory(). Not enough free memory to allocate %d bytes.\n", MemorySize);
        UiMessageBoxCritical("Memory allocation failed: out of memory.");
        return NULL;
    }

    FirstFreePageFromEnd = MmFindAvailablePages(PageLookupTableAddress, TotalPagesInLookupTable, PagesNeeded, FALSE);

    if (FirstFreePageFromEnd == 0)
    {
        ERR("Memory allocation failed in MmAllocateMemory(). Not enough free memory to allocate %d bytes.\n", MemorySize);
        UiMessageBoxCritical("Memory allocation failed: out of memory.");
        return NULL;
    }

    MmAllocatePagesInLookupTable(PageLookupTableAddress, FirstFreePageFromEnd, PagesNeeded, MemoryType);

    FreePagesInLookupTable -= PagesNeeded;
    MemPointer = (PVOID)((ULONG_PTR)FirstFreePageFromEnd * MM_PAGE_SIZE);

    TRACE("Allocated %d bytes (%d pages) of memory (type %ld) starting at page 0x%lx.\n",
          MemorySize, PagesNeeded, MemoryType, FirstFreePageFromEnd);
    TRACE("Memory allocation pointer: 0x%x\n", MemPointer);

    // Update LoaderPagesSpanned count
    if ((((ULONG_PTR)MemPointer + MemorySize + PAGE_SIZE - 1) >> PAGE_SHIFT) > LoaderPagesSpanned)
        LoaderPagesSpanned = (((ULONG_PTR)MemPointer + MemorySize + PAGE_SIZE - 1) >> PAGE_SHIFT);

    // Now return the pointer
    return MemPointer;
}