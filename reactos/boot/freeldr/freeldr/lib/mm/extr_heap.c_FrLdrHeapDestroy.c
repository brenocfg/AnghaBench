#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG_PTR ;
struct TYPE_5__ {int MaximumSize; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PHEAP ;
typedef  int /*<<< orphan*/  PFN_COUNT ;

/* Variables and functions */
 int /*<<< orphan*/  LoaderFirmwareTemporary ; 
 int MM_PAGE_SIZE ; 
 int /*<<< orphan*/  MmMarkPagesInLookupTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageLookupTableAddress ; 
 int /*<<< orphan*/  RtlFillMemory (TYPE_1__*,int,int) ; 

VOID
FrLdrHeapDestroy(
    PVOID HeapHandle)
{
    PHEAP Heap = HeapHandle;

    /* Mark all pages as firmware temporary, so they are free for the kernel */
    MmMarkPagesInLookupTable(PageLookupTableAddress,
                             (ULONG_PTR)Heap / MM_PAGE_SIZE,
                             (PFN_COUNT)(Heap->MaximumSize / MM_PAGE_SIZE),
                             LoaderFirmwareTemporary);

#if DBG
    /* Make sure everything is dead */
    RtlFillMemory(Heap, Heap->MaximumSize, 0xCCCCCCCC);
#endif
}