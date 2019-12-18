#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32 ;
struct TYPE_6__ {size_t nr_txns; int /*<<< orphan*/  heap; int /*<<< orphan*/  old_change; TYPE_1__* entries; } ;
struct TYPE_5__ {int fd; } ;
typedef  TYPE_2__ ReorderBufferIterTXNState ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseTransientFile (int) ; 
 int ReorderBufferChange ; 
 int /*<<< orphan*/  ReorderBufferReturnChange (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  binaryheap_free (int /*<<< orphan*/ ) ; 
 int change ; 
 int /*<<< orphan*/  dlist_container (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_pop_head_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
ReorderBufferIterTXNFinish(ReorderBuffer *rb,
						   ReorderBufferIterTXNState *state)
{
	int32		off;

	for (off = 0; off < state->nr_txns; off++)
	{
		if (state->entries[off].fd != -1)
			CloseTransientFile(state->entries[off].fd);
	}

	/* free memory we might have "leaked" in the last *Next call */
	if (!dlist_is_empty(&state->old_change))
	{
		ReorderBufferChange *change;

		change = dlist_container(ReorderBufferChange, node,
								 dlist_pop_head_node(&state->old_change));
		ReorderBufferReturnChange(rb, change);
		Assert(dlist_is_empty(&state->old_change));
	}

	binaryheap_free(state->heap);
	pfree(state);
}