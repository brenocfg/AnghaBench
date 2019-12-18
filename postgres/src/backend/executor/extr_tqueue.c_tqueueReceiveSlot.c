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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ TQueueDestReceiver ;
typedef  TYPE_2__* HeapTuple ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* ExecFetchSlotHeapTuple (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ SHM_MQ_DETACHED ; 
 scalar_t__ SHM_MQ_SUCCESS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 scalar_t__ shm_mq_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
tqueueReceiveSlot(TupleTableSlot *slot, DestReceiver *self)
{
	TQueueDestReceiver *tqueue = (TQueueDestReceiver *) self;
	HeapTuple	tuple;
	shm_mq_result result;
	bool		should_free;

	/* Send the tuple itself. */
	tuple = ExecFetchSlotHeapTuple(slot, true, &should_free);
	result = shm_mq_send(tqueue->queue, tuple->t_len, tuple->t_data, false);

	if (should_free)
		heap_freetuple(tuple);

	/* Check for failure. */
	if (result == SHM_MQ_DETACHED)
		return false;
	else if (result != SHM_MQ_SUCCESS)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("could not send tuple to shared-memory queue")));

	return true;
}