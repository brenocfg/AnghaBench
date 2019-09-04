#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG_PTR ;
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  TYPE_OF_MEMORY ;
struct TYPE_3__ {int BasePage; int PageCount; scalar_t__ MemoryType; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int ADDRESS_AND_SIZE_TO_SPAN_PAGES (int,int /*<<< orphan*/ ) ; 
 size_t AddMemoryDescriptor (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrBugCheckWithMessage (int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LoaderFree ; 
 int /*<<< orphan*/  MAX_BIOS_DESCRIPTORS ; 
 int /*<<< orphan*/  MEMORY_INIT_FAILURE ; 
 int PAGE_SIZE ; 
 size_t PcMapCount ; 
 TYPE_1__* PcMemoryMap ; 

VOID
ReserveMemory(
    ULONG_PTR BaseAddress,
    SIZE_T Size,
    TYPE_OF_MEMORY MemoryType,
    PCHAR Usage)
{
    ULONG_PTR BasePage, PageCount;
    ULONG i;

    BasePage = BaseAddress / PAGE_SIZE;
    PageCount = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, Size);

    for (i = 0; i < PcMapCount; i++)
    {
        /* Check for conflicting descriptor */
        if ((PcMemoryMap[i].BasePage < BasePage + PageCount) &&
            (PcMemoryMap[i].BasePage + PcMemoryMap[i].PageCount > BasePage))
        {
            /* Check if the memory is free */
            if (PcMemoryMap[i].MemoryType != LoaderFree)
            {
                FrLdrBugCheckWithMessage(
                    MEMORY_INIT_FAILURE,
                    __FILE__,
                    __LINE__,
                    "Failed to reserve memory in the range 0x%Ix - 0x%Ix for %s",
                    BaseAddress,
                    Size,
                    Usage);
            }
        }
    }

    /* Add the memory descriptor */
    PcMapCount = AddMemoryDescriptor(PcMemoryMap,
                                     MAX_BIOS_DESCRIPTORS,
                                     BasePage,
                                     PageCount,
                                     MemoryType);
}