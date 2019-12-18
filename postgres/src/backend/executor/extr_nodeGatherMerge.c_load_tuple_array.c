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
struct TYPE_6__ {int nTuples; int readCounter; int /*<<< orphan*/ * tuple; int /*<<< orphan*/  done; } ;
struct TYPE_5__ {TYPE_2__* gm_tuple_buffers; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ GatherMergeState ;
typedef  TYPE_2__ GMReaderTupleBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int MAX_TUPLE_STORE ; 
 int /*<<< orphan*/  gm_readnext_tuple (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
load_tuple_array(GatherMergeState *gm_state, int reader)
{
	GMReaderTupleBuffer *tuple_buffer;
	int			i;

	/* Don't do anything if this is the leader. */
	if (reader == 0)
		return;

	tuple_buffer = &gm_state->gm_tuple_buffers[reader - 1];

	/* If there's nothing in the array, reset the counters to zero. */
	if (tuple_buffer->nTuples == tuple_buffer->readCounter)
		tuple_buffer->nTuples = tuple_buffer->readCounter = 0;

	/* Try to fill additional slots in the array. */
	for (i = tuple_buffer->nTuples; i < MAX_TUPLE_STORE; i++)
	{
		HeapTuple	tuple;

		tuple = gm_readnext_tuple(gm_state,
								  reader,
								  true,
								  &tuple_buffer->done);
		if (!HeapTupleIsValid(tuple))
			break;
		tuple_buffer->tuple[i] = tuple;
		tuple_buffer->nTuples++;
	}
}