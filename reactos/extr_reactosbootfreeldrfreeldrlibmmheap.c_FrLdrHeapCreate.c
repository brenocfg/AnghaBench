#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int TYPE_OF_MEMORY ;
struct TYPE_9__ {int Size; int PreviousSize; char Tag; TYPE_1__* Data; } ;
struct TYPE_8__ {int MaximumSize; int TerminatingBlock; TYPE_3__ Blocks; scalar_t__ LargestAllocation; scalar_t__ NumFrees; scalar_t__ NumAllocs; scalar_t__ MaxAllocBytes; scalar_t__ CurrentAllocBytes; } ;
struct TYPE_7__ {int Flink; int Blink; } ;
typedef  int SIZE_T ;
typedef  TYPE_2__* PVOID ;
typedef  TYPE_3__* PHEAP_BLOCK ;
typedef  TYPE_2__* PHEAP ;
typedef  int /*<<< orphan*/  HEAP_BLOCK ;
typedef  int /*<<< orphan*/  HEAP ;

/* Variables and functions */
 int ALIGN_UP_BY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int,int) ; 
 int /*<<< orphan*/  MAXUSHORT ; 
 int /*<<< orphan*/  MM_PAGE_SIZE ; 
 TYPE_2__* MmAllocateMemoryWithType (int,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int) ; 

PVOID
FrLdrHeapCreate(
    SIZE_T MaximumSize,
    TYPE_OF_MEMORY MemoryType)
{
    PHEAP Heap;
    PHEAP_BLOCK Block;
    SIZE_T Remaining;
    USHORT PreviousSize;
    TRACE("HeapCreate(MemoryType=%ld)\n", MemoryType);

    /* Allocate some memory for the heap */
    MaximumSize = ALIGN_UP_BY(MaximumSize, MM_PAGE_SIZE);
    Heap = MmAllocateMemoryWithType(MaximumSize, MemoryType);
    if (!Heap)
    {
        ERR("HEAP: Failed to allocate heap of size 0x%lx, Type\n",
            MaximumSize, MemoryType);
        return NULL;
    }

    /* Initialize the heap header */
    Heap->MaximumSize = MaximumSize;
    Heap->CurrentAllocBytes = 0;
    Heap->MaxAllocBytes = 0;
    Heap->NumAllocs = 0;
    Heap->NumFrees = 0;
    Heap->LargestAllocation = 0;

    /* Calculate what's left to process */
    Remaining = (MaximumSize - sizeof(HEAP)) / sizeof(HEAP_BLOCK);
    TRACE("Remaining = %ld\n", Remaining);

    /* Substract 2 for the terminating entry (header + free entry) */
    Remaining -= 2;

    Block = &Heap->Blocks;
    PreviousSize = 0;

    /* Create free blocks */
    while (Remaining > 1)
    {
        /* Initialize this free block */
        Block->Size = (USHORT)min(MAXUSHORT, Remaining - 1);
        Block->PreviousSize = PreviousSize;
        Block->Tag = 0;
        Block->Data[0].Flink = (Block - &Heap->Blocks) + Block->Size + 1;
        Block->Data[0].Blink = (Block - &Heap->Blocks) - 1 - PreviousSize;

        /* Substract current block size from remainder */
        Remaining -= (Block->Size + 1);

        /* Go to next block */
        PreviousSize = Block->Size;
        Block = Block + Block->Size + 1;

        TRACE("Remaining = %ld\n", Remaining);
    }

    /* Now finish with a terminating block */
    Heap->TerminatingBlock = Block - &Heap->Blocks;
    Block->Size = 0;
    Block->PreviousSize = PreviousSize;
    Block->Tag = 'dnE#';
    Block->Data[0].Flink = 0;
    Block->Data[0].Blink = (Block - &Heap->Blocks) - 1 - PreviousSize;
    Heap->Blocks.Data[0].Blink = Heap->TerminatingBlock;

    return Heap;
}