#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/ ** gm_slots; int /*<<< orphan*/  gm_heap; int /*<<< orphan*/  gm_initialized; } ;
typedef  TYPE_1__ GatherMergeState ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 scalar_t__ binaryheap_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binaryheap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binaryheap_remove_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binaryheap_replace_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gather_merge_clear_tuples (TYPE_1__*) ; 
 int /*<<< orphan*/  gather_merge_init (TYPE_1__*) ; 
 scalar_t__ gather_merge_readnext (TYPE_1__*,int,int) ; 

__attribute__((used)) static TupleTableSlot *
gather_merge_getnext(GatherMergeState *gm_state)
{
	int			i;

	if (!gm_state->gm_initialized)
	{
		/*
		 * First time through: pull the first tuple from each participant, and
		 * set up the heap.
		 */
		gather_merge_init(gm_state);
	}
	else
	{
		/*
		 * Otherwise, pull the next tuple from whichever participant we
		 * returned from last time, and reinsert that participant's index into
		 * the heap, because it might now compare differently against the
		 * other elements of the heap.
		 */
		i = DatumGetInt32(binaryheap_first(gm_state->gm_heap));

		if (gather_merge_readnext(gm_state, i, false))
			binaryheap_replace_first(gm_state->gm_heap, Int32GetDatum(i));
		else
		{
			/* reader exhausted, remove it from heap */
			(void) binaryheap_remove_first(gm_state->gm_heap);
		}
	}

	if (binaryheap_empty(gm_state->gm_heap))
	{
		/* All the queues are exhausted, and so is the heap */
		gather_merge_clear_tuples(gm_state);
		return NULL;
	}
	else
	{
		/* Return next tuple from whichever participant has the leading one */
		i = DatumGetInt32(binaryheap_first(gm_state->gm_heap));
		return gm_state->gm_slots[i];
	}
}