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
struct TYPE_11__ {int t_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  TYPE_3__* MinimalTuple ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (TYPE_3__*) ; 
 int /*<<< orphan*/  LogicalTapeWrite (int /*<<< orphan*/ ,int,void*,int) ; 
 int MINIMAL_TUPLE_DATA_OFFSET ; 
 int /*<<< orphan*/  heap_free_minimal_tuple (TYPE_3__*) ; 

__attribute__((used)) static void
writetup_heap(Tuplesortstate *state, int tapenum, SortTuple *stup)
{
	MinimalTuple tuple = (MinimalTuple) stup->tuple;

	/* the part of the MinimalTuple we'll write: */
	char	   *tupbody = (char *) tuple + MINIMAL_TUPLE_DATA_OFFSET;
	unsigned int tupbodylen = tuple->t_len - MINIMAL_TUPLE_DATA_OFFSET;

	/* total on-disk footprint: */
	unsigned int tuplen = tupbodylen + sizeof(int);

	LogicalTapeWrite(state->tapeset, tapenum,
					 (void *) &tuplen, sizeof(tuplen));
	LogicalTapeWrite(state->tapeset, tapenum,
					 (void *) tupbody, tupbodylen);
	if (state->randomAccess)	/* need trailing length word? */
		LogicalTapeWrite(state->tapeset, tapenum,
						 (void *) &tuplen, sizeof(tuplen));

	if (!state->slabAllocatorUsed)
	{
		FREEMEM(state, GetMemoryChunkSpace(tuple));
		heap_free_minimal_tuple(tuple);
	}
}