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
typedef  scalar_t__ shm_mq_result ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ TupleQueueReader ;
struct TYPE_6__ {void* t_data; int /*<<< orphan*/  t_len; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__ HeapTupleData ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 scalar_t__ SHM_MQ_DETACHED ; 
 scalar_t__ SHM_MQ_SUCCESS ; 
 scalar_t__ SHM_MQ_WOULD_BLOCK ; 
 int /*<<< orphan*/ * heap_copytuple (TYPE_2__*) ; 
 scalar_t__ shm_mq_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int) ; 

HeapTuple
TupleQueueReaderNext(TupleQueueReader *reader, bool nowait, bool *done)
{
	HeapTupleData htup;
	shm_mq_result result;
	Size		nbytes;
	void	   *data;

	if (done != NULL)
		*done = false;

	/* Attempt to read a message. */
	result = shm_mq_receive(reader->queue, &nbytes, &data, nowait);

	/* If queue is detached, set *done and return NULL. */
	if (result == SHM_MQ_DETACHED)
	{
		if (done != NULL)
			*done = true;
		return NULL;
	}

	/* In non-blocking mode, bail out if no message ready yet. */
	if (result == SHM_MQ_WOULD_BLOCK)
		return NULL;
	Assert(result == SHM_MQ_SUCCESS);

	/*
	 * Set up a dummy HeapTupleData pointing to the data from the shm_mq
	 * (which had better be sufficiently aligned).
	 */
	ItemPointerSetInvalid(&htup.t_self);
	htup.t_tableOid = InvalidOid;
	htup.t_len = nbytes;
	htup.t_data = data;

	return heap_copytuple(&htup);
}