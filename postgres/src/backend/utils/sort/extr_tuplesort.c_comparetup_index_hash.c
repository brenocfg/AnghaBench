#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  low_mask; int /*<<< orphan*/  high_mask; int /*<<< orphan*/  max_buckets; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_9__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_8__ {scalar_t__ tuple; int /*<<< orphan*/  datum1; int /*<<< orphan*/  isnull1; } ;
typedef  TYPE_2__ SortTuple ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_3__* IndexTuple ;
typedef  scalar_t__ Bucket ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ _hash_hashkey2bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comparetup_index_hash(const SortTuple *a, const SortTuple *b,
					  Tuplesortstate *state)
{
	Bucket		bucket1;
	Bucket		bucket2;
	IndexTuple	tuple1;
	IndexTuple	tuple2;

	/*
	 * Fetch hash keys and mask off bits we don't want to sort by. We know
	 * that the first column of the index tuple is the hash key.
	 */
	Assert(!a->isnull1);
	bucket1 = _hash_hashkey2bucket(DatumGetUInt32(a->datum1),
								   state->max_buckets, state->high_mask,
								   state->low_mask);
	Assert(!b->isnull1);
	bucket2 = _hash_hashkey2bucket(DatumGetUInt32(b->datum1),
								   state->max_buckets, state->high_mask,
								   state->low_mask);
	if (bucket1 > bucket2)
		return 1;
	else if (bucket1 < bucket2)
		return -1;

	/*
	 * If hash values are equal, we sort on ItemPointer.  This does not affect
	 * validity of the finished index, but it may be useful to have index
	 * scans in physical order.
	 */
	tuple1 = (IndexTuple) a->tuple;
	tuple2 = (IndexTuple) b->tuple;

	{
		BlockNumber blk1 = ItemPointerGetBlockNumber(&tuple1->t_tid);
		BlockNumber blk2 = ItemPointerGetBlockNumber(&tuple2->t_tid);

		if (blk1 != blk2)
			return (blk1 < blk2) ? -1 : 1;
	}
	{
		OffsetNumber pos1 = ItemPointerGetOffsetNumber(&tuple1->t_tid);
		OffsetNumber pos2 = ItemPointerGetOffsetNumber(&tuple2->t_tid);

		if (pos1 != pos2)
			return (pos1 < pos2) ? -1 : 1;
	}

	/* ItemPointer values should never be equal */
	Assert(false);

	return 0;
}