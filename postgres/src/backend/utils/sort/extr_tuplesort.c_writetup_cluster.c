#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuplen ;
struct TYPE_9__ {int /*<<< orphan*/  slabAllocatorUsed; int /*<<< orphan*/  tapeset; scalar_t__ randomAccess; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_11__ {int t_len; unsigned int t_self; unsigned int* t_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_3__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_3__*) ; 
 int /*<<< orphan*/  LogicalTapeWrite (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 

__attribute__((used)) static void
writetup_cluster(Tuplesortstate *state, int tapenum, SortTuple *stup)
{
	HeapTuple	tuple = (HeapTuple) stup->tuple;
	unsigned int tuplen = tuple->t_len + sizeof(ItemPointerData) + sizeof(int);

	/* We need to store t_self, but not other fields of HeapTupleData */
	LogicalTapeWrite(state->tapeset, tapenum,
					 &tuplen, sizeof(tuplen));
	LogicalTapeWrite(state->tapeset, tapenum,
					 &tuple->t_self, sizeof(ItemPointerData));
	LogicalTapeWrite(state->tapeset, tapenum,
					 tuple->t_data, tuple->t_len);
	if (state->randomAccess)	/* need trailing length word? */
		LogicalTapeWrite(state->tapeset, tapenum,
						 &tuplen, sizeof(tuplen));

	if (!state->slabAllocatorUsed)
	{
		FREEMEM(state, GetMemoryChunkSpace(tuple));
		heap_freetuple(tuple);
	}
}