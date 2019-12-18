#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_17__ {scalar_t__ spaceUsed; int spaceUsedSkew; scalar_t__ spacePeak; scalar_t__ spaceAllowedSkew; scalar_t__ spaceAllowed; TYPE_1__** skewBucket; int /*<<< orphan*/  batchCxt; } ;
struct TYPE_14__ {TYPE_4__* unshared; } ;
struct TYPE_16__ {TYPE_2__ next; int /*<<< orphan*/  hashvalue; } ;
struct TYPE_15__ {int t_len; } ;
struct TYPE_13__ {TYPE_4__* tuples; } ;
typedef  TYPE_3__* MinimalTuple ;
typedef  TYPE_4__* HashJoinTuple ;
typedef  TYPE_5__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__* ExecFetchSlotMinimalTuple (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ExecHashIncreaseNumBatches (TYPE_5__*) ; 
 int /*<<< orphan*/  ExecHashRemoveNextSkewBucket (TYPE_5__*) ; 
 int /*<<< orphan*/  HJTUPLE_MINTUPLE (TYPE_4__*) ; 
 int HJTUPLE_OVERHEAD ; 
 int /*<<< orphan*/  HeapTupleHeaderClearMatch (int /*<<< orphan*/ ) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_free_minimal_tuple (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

__attribute__((used)) static void
ExecHashSkewTableInsert(HashJoinTable hashtable,
						TupleTableSlot *slot,
						uint32 hashvalue,
						int bucketNumber)
{
	bool		shouldFree;
	MinimalTuple tuple = ExecFetchSlotMinimalTuple(slot, &shouldFree);
	HashJoinTuple hashTuple;
	int			hashTupleSize;

	/* Create the HashJoinTuple */
	hashTupleSize = HJTUPLE_OVERHEAD + tuple->t_len;
	hashTuple = (HashJoinTuple) MemoryContextAlloc(hashtable->batchCxt,
												   hashTupleSize);
	hashTuple->hashvalue = hashvalue;
	memcpy(HJTUPLE_MINTUPLE(hashTuple), tuple, tuple->t_len);
	HeapTupleHeaderClearMatch(HJTUPLE_MINTUPLE(hashTuple));

	/* Push it onto the front of the skew bucket's list */
	hashTuple->next.unshared = hashtable->skewBucket[bucketNumber]->tuples;
	hashtable->skewBucket[bucketNumber]->tuples = hashTuple;
	Assert(hashTuple != hashTuple->next.unshared);

	/* Account for space used, and back off if we've used too much */
	hashtable->spaceUsed += hashTupleSize;
	hashtable->spaceUsedSkew += hashTupleSize;
	if (hashtable->spaceUsed > hashtable->spacePeak)
		hashtable->spacePeak = hashtable->spaceUsed;
	while (hashtable->spaceUsedSkew > hashtable->spaceAllowedSkew)
		ExecHashRemoveNextSkewBucket(hashtable);

	/* Check we are not over the total spaceAllowed, either */
	if (hashtable->spaceUsed > hashtable->spaceAllowed)
		ExecHashIncreaseNumBatches(hashtable);

	if (shouldFree)
		heap_free_minimal_tuple(tuple);
}