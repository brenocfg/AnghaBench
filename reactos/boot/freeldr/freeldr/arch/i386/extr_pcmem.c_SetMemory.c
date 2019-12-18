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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  TYPE_OF_MEMORY ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PFREELDR_MEMORY_DESCRIPTOR ;

/* Variables and functions */
 int ADDRESS_AND_SIZE_TO_SPAN_PAGES (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddMemoryDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_BIOS_DESCRIPTORS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PcMapCount ; 

VOID
SetMemory(
    PFREELDR_MEMORY_DESCRIPTOR MemoryMap,
    ULONG_PTR BaseAddress,
    SIZE_T Size,
    TYPE_OF_MEMORY MemoryType)
{
    ULONG_PTR BasePage, PageCount;

    BasePage = BaseAddress / PAGE_SIZE;
    PageCount = ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseAddress, Size);

    /* Add the memory descriptor */
    PcMapCount = AddMemoryDescriptor(MemoryMap,
                                     MAX_BIOS_DESCRIPTORS,
                                     BasePage,
                                     PageCount,
                                     MemoryType);
}