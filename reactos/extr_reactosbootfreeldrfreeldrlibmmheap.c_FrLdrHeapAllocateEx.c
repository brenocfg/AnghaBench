#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  char ULONG ;
struct TYPE_14__ {int Size; char Tag; int PreviousSize; TYPE_1__* Data; } ;
struct TYPE_13__ {int TerminatingBlock; int Flink; int CurrentAllocBytes; void* LargestAllocation; void* MaxAllocBytes; int /*<<< orphan*/  NumAllocs; TYPE_2__ Blocks; } ;
typedef  int SIZE_T ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_2__* PHEAP_BLOCK ;
typedef  TYPE_1__* PHEAP ;
typedef  int /*<<< orphan*/  HEAP_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FrLdrHeapInsertFreeList (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FrLdrHeapRemoveFreeList (TYPE_1__*,TYPE_2__*) ; 
 int MAXUSHORT ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 void* max (void*,int) ; 

PVOID
FrLdrHeapAllocateEx(
    PVOID HeapHandle,
    SIZE_T ByteSize,
    ULONG Tag)
{
    PHEAP Heap = HeapHandle;
    PHEAP_BLOCK Block, NextBlock;
    USHORT BlockSize, Remaining;
#if DBG && !defined(_M_ARM)
    ULONGLONG Time = __rdtsc();
#endif

#ifdef FREELDR_HEAP_VERIFIER
    /* Verify the heap */
    FrLdrHeapVerify(HeapHandle);

    /* Add space for a size field and 2 redzones */
    ByteSize += REDZONE_ALLOCATION;
#endif

    /* Check if the allocation is too large */
    if ((ByteSize +  sizeof(HEAP_BLOCK)) > MAXUSHORT * sizeof(HEAP_BLOCK))
    {
        ERR("HEAP: Allocation of 0x%lx bytes too large\n", ByteSize);
        return NULL;
    }

    /* We need a proper tag */
    if (Tag == 0) Tag = 'enoN';

    /* Calculate alloc size */
    BlockSize = (USHORT)((ByteSize + sizeof(HEAP_BLOCK) - 1) / sizeof(HEAP_BLOCK));

    /* Walk the free block list */
    Block = &Heap->Blocks + Heap->TerminatingBlock;
    for (Block = &Heap->Blocks + Block->Data[0].Flink;
         Block->Size != 0;
         Block = &Heap->Blocks + Block->Data[0].Flink)
    {
        ASSERT(Block->Tag == 0);

        /* Continue, if its too small */
        if (Block->Size < BlockSize) continue;

        /* This block is just fine, use it */
        Block->Tag = Tag;

        /* Remove this entry from the free list */
        FrLdrHeapRemoveFreeList(Heap, Block);

        /* Calculate the remaining size */
        Remaining = Block->Size - BlockSize;

        /* Check if the remaining space is large enough for a new block */
        if (Remaining > 1)
        {
            /* Make the allocated block as large as necessary */
            Block->Size = BlockSize;

            /* Get pointer to the new block */
            NextBlock = Block + 1 + BlockSize;

            /* Make it a free block */
            NextBlock->Tag = 0;
            NextBlock->Size = Remaining - 1;
            NextBlock->PreviousSize = BlockSize;
            BlockSize = NextBlock->Size;
            FrLdrHeapInsertFreeList(Heap, NextBlock);

            /* Advance to the next block */
            NextBlock = NextBlock + 1 + BlockSize;
        }
        else
        {
            /* Not enough left, use the full block */
            BlockSize = Block->Size;

            /* Get the next block */
            NextBlock = Block + 1 + BlockSize;
        }

        /* Update the next blocks back link */
        NextBlock->PreviousSize = BlockSize;

        /* Update heap usage */
        Heap->NumAllocs++;
        Heap->CurrentAllocBytes += Block->Size * sizeof(HEAP_BLOCK);
        Heap->MaxAllocBytes = max(Heap->MaxAllocBytes, Heap->CurrentAllocBytes);
        Heap->LargestAllocation = max(Heap->LargestAllocation,
                                      Block->Size * sizeof(HEAP_BLOCK));
#if DBG && !defined(_M_ARM)
        Heap->AllocationTime += (__rdtsc() - Time);
#endif
        TRACE("HeapAllocate(%p, %ld, %.4s) -> return %p\n",
              HeapHandle, ByteSize, &Tag, Block->Data);

        /* HACK: zero out the allocation */
        RtlZeroMemory(Block->Data, Block->Size * sizeof(HEAP_BLOCK));

#ifdef FREELDR_HEAP_VERIFIER
        /* Write size and redzones */
        *REDZONE_SIZE(Block) = ByteSize - REDZONE_ALLOCATION;
        *REDZONE_LOW(Block) = REDZONE_MARK;
        *REDZONE_HI(Block) = REDZONE_MARK;

        /* Allocation starts after size field and redzone */
        return (PUCHAR)Block->Data + REDZONE_LOW_OFFSET;
#endif
        /* Return pointer to the data */
        return Block->Data;
    }

    /* We found nothing */
    WARN("HEAP: nothing suitable found for 0x%lx bytes\n", ByteSize);
    return NULL;
}