#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_14__ {int /*<<< orphan*/ * shared; } ;
struct TYPE_17__ {int curbatch; TYPE_1__ buckets; } ;
struct TYPE_16__ {int /*<<< orphan*/  hashvalue; } ;
struct TYPE_15__ {scalar_t__ t_len; } ;
typedef  TYPE_2__* MinimalTuple ;
typedef  TYPE_3__* HashJoinTuple ;
typedef  TYPE_4__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* ExecFetchSlotMinimalTuple (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ExecHashGetBucketAndBatch (TYPE_4__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ExecParallelHashPushTuple (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ExecParallelHashTupleAlloc (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HJTUPLE_MINTUPLE (TYPE_3__*) ; 
 scalar_t__ HJTUPLE_OVERHEAD ; 
 int /*<<< orphan*/  HeapTupleHeaderClearMatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free_minimal_tuple (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 

void
ExecParallelHashTableInsertCurrentBatch(HashJoinTable hashtable,
										TupleTableSlot *slot,
										uint32 hashvalue)
{
	bool		shouldFree;
	MinimalTuple tuple = ExecFetchSlotMinimalTuple(slot, &shouldFree);
	HashJoinTuple hashTuple;
	dsa_pointer shared;
	int			batchno;
	int			bucketno;

	ExecHashGetBucketAndBatch(hashtable, hashvalue, &bucketno, &batchno);
	Assert(batchno == hashtable->curbatch);
	hashTuple = ExecParallelHashTupleAlloc(hashtable,
										   HJTUPLE_OVERHEAD + tuple->t_len,
										   &shared);
	hashTuple->hashvalue = hashvalue;
	memcpy(HJTUPLE_MINTUPLE(hashTuple), tuple, tuple->t_len);
	HeapTupleHeaderClearMatch(HJTUPLE_MINTUPLE(hashTuple));
	ExecParallelHashPushTuple(&hashtable->buckets.shared[bucketno],
							  hashTuple, shared);

	if (shouldFree)
		heap_free_minimal_tuple(tuple);
}