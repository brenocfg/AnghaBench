#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int Size; scalar_t__ Tag; } ;
struct TYPE_8__ {TYPE_2__ Blocks; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_2__* PHEAP_BLOCK ;
typedef  TYPE_1__* PHEAP ;
typedef  int /*<<< orphan*/  HEAP_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__* REDZONE_HI (TYPE_2__*) ; 
 scalar_t__* REDZONE_LOW (TYPE_2__*) ; 
 scalar_t__ REDZONE_MARK ; 
 int* REDZONE_SIZE (TYPE_2__*) ; 

VOID
FrLdrHeapVerify(
    PVOID HeapHandle)
{
    PHEAP Heap = HeapHandle;
    PHEAP_BLOCK Block;

    /* Loop all heap chunks */
    for (Block = &Heap->Blocks;
         Block->Size != 0;
         Block = Block + 1 + Block->Size)
    {
        /* Continue, if its not free */
        if (Block->Tag != 0)
        {
            /* Verify size and redzones */
            ASSERT(*REDZONE_SIZE(Block) <= Block->Size * sizeof(HEAP_BLOCK));
            ASSERT(*REDZONE_LOW(Block) == REDZONE_MARK);
            ASSERT(*REDZONE_HI(Block) == REDZONE_MARK);
            continue;
        }
    }
}