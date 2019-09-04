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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_4__ {int BasePage; int PageCount; int /*<<< orphan*/  MemoryType; } ;
typedef  scalar_t__ PVOID ;
typedef  int PFN_NUMBER ;
typedef  int /*<<< orphan*/  PAGE_LOOKUP_TABLE_ITEM ;
typedef  TYPE_1__ FREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 TYPE_1__* ArcGetMemoryDescriptor (TYPE_1__ const*) ; 
 int /*<<< orphan*/  LoaderFirmwarePermanent ; 
 int /*<<< orphan*/  LoaderFirmwareTemporary ; 
 int /*<<< orphan*/  MM_PAGE_SIZE ; 
 int MmGetPageNumberFromAddress (scalar_t__) ; 
 int /*<<< orphan*/  MmGetSystemMemoryMapTypeString (int /*<<< orphan*/ ) ; 
 int MmLowestPhysicalPage ; 
 int /*<<< orphan*/  MmMarkPagesInLookupTable (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

VOID MmInitPageLookupTable(PVOID PageLookupTable, PFN_NUMBER TotalPageCount)
{
    const FREELDR_MEMORY_DESCRIPTOR* MemoryDescriptor = NULL;
    PFN_NUMBER PageLookupTableStartPage;
    PFN_NUMBER PageLookupTablePageCount;

    TRACE("MmInitPageLookupTable()\n");

    // Mark every page as allocated initially
    // We will go through and mark pages again according to the memory map
    // But this will mark any holes not described in the map as allocated
    MmMarkPagesInLookupTable(PageLookupTable, MmLowestPhysicalPage, TotalPageCount, LoaderFirmwarePermanent);

    // Parse the whole memory map
    while ((MemoryDescriptor = ArcGetMemoryDescriptor(MemoryDescriptor)) != NULL)
    {
        // Mark used pages in the lookup table

        if (MemoryDescriptor->BasePage + MemoryDescriptor->PageCount <= TotalPageCount)
        {
            TRACE("Marking pages 0x%lx-0x%lx as type %s\n",
                  MemoryDescriptor->BasePage,
                  MemoryDescriptor->BasePage + MemoryDescriptor->PageCount,
                  MmGetSystemMemoryMapTypeString(MemoryDescriptor->MemoryType));
            MmMarkPagesInLookupTable(PageLookupTable,
                                     MemoryDescriptor->BasePage,
                                     MemoryDescriptor->PageCount,
                                     MemoryDescriptor->MemoryType);
        }
        else
            TRACE("Ignoring pages 0x%lx-0x%lx (%s)\n",
                  MemoryDescriptor->BasePage,
                  MemoryDescriptor->BasePage + MemoryDescriptor->PageCount,
                  MmGetSystemMemoryMapTypeString(MemoryDescriptor->MemoryType));
    }

    // Mark the pages that the lookup table occupies as reserved
    PageLookupTableStartPage = MmGetPageNumberFromAddress(PageLookupTable);
    PageLookupTablePageCount = MmGetPageNumberFromAddress((PVOID)((ULONG_PTR)PageLookupTable + ROUND_UP(TotalPageCount * sizeof(PAGE_LOOKUP_TABLE_ITEM), MM_PAGE_SIZE))) - PageLookupTableStartPage;
    TRACE("Marking the page lookup table pages as reserved StartPage: 0x%x PageCount: 0x%x\n", PageLookupTableStartPage, PageLookupTablePageCount);
    MmMarkPagesInLookupTable(PageLookupTable, PageLookupTableStartPage, PageLookupTablePageCount, LoaderFirmwareTemporary);
}