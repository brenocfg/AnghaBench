#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleQueueReader ;
struct TYPE_3__ {int /*<<< orphan*/ ** reader; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ GatherMergeState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  TupleQueueReaderNext (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static HeapTuple
gm_readnext_tuple(GatherMergeState *gm_state, int nreader, bool nowait,
				  bool *done)
{
	TupleQueueReader *reader;
	HeapTuple	tup;

	/* Check for async events, particularly messages from workers. */
	CHECK_FOR_INTERRUPTS();

	/*
	 * Attempt to read a tuple.
	 *
	 * Note that TupleQueueReaderNext will just return NULL for a worker which
	 * fails to initialize.  We'll treat that worker as having produced no
	 * tuples; WaitForParallelWorkersToFinish will error out when we get
	 * there.
	 */
	reader = gm_state->reader[nreader - 1];
	tup = TupleQueueReaderNext(reader, nowait, done);

	return tup;
}