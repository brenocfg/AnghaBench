#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {scalar_t__ Tag; TYPE_1__* Data; } ;
struct TYPE_8__ {int TerminatingBlock; TYPE_2__ Blocks; } ;
struct TYPE_6__ {int Flink; int Blink; } ;
typedef  TYPE_2__* PHEAP_BLOCK ;
typedef  TYPE_3__* PHEAP ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static VOID
FrLdrHeapInsertFreeList(
    PHEAP Heap,
    PHEAP_BLOCK FreeBlock)
{
    PHEAP_BLOCK ListHead, NextBlock;
    ASSERT(FreeBlock->Tag == 0);

    /* Terminating block serves as free list head */
    ListHead = &Heap->Blocks + Heap->TerminatingBlock;

    for (NextBlock = &Heap->Blocks + ListHead->Data[0].Flink;
         NextBlock < FreeBlock;
         NextBlock = &Heap->Blocks + NextBlock->Data[0].Flink);

    FreeBlock->Data[0].Flink = NextBlock - &Heap->Blocks;
    FreeBlock->Data[0].Blink = NextBlock->Data[0].Blink;
    NextBlock->Data[0].Blink = FreeBlock - &Heap->Blocks;
    NextBlock = &Heap->Blocks + FreeBlock->Data[0].Blink;
    NextBlock->Data[0].Flink = FreeBlock - &Heap->Blocks;
}