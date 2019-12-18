#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_18__ {int /*<<< orphan*/ * ecxt_innertuple; } ;
struct TYPE_17__ {size_t hj_CurBucketNo; size_t hj_CurSkewBucketNo; TYPE_4__* hj_CurTuple; int /*<<< orphan*/  hj_HashTupleSlot; TYPE_5__* hj_HashTable; } ;
struct TYPE_12__ {TYPE_4__** unshared; } ;
struct TYPE_16__ {size_t nbuckets; size_t nSkewBuckets; int* skewBucketNums; TYPE_2__** skewBucket; TYPE_1__ buckets; } ;
struct TYPE_14__ {TYPE_4__* unshared; } ;
struct TYPE_15__ {TYPE_3__ next; } ;
struct TYPE_13__ {TYPE_4__* tuples; } ;
typedef  TYPE_4__* HashJoinTuple ;
typedef  TYPE_5__* HashJoinTable ;
typedef  TYPE_6__ HashJoinState ;
typedef  TYPE_7__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/ * ExecStoreMinimalTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HJTUPLE_MINTUPLE (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderHasMatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_7__*) ; 

bool
ExecScanHashTableForUnmatched(HashJoinState *hjstate, ExprContext *econtext)
{
	HashJoinTable hashtable = hjstate->hj_HashTable;
	HashJoinTuple hashTuple = hjstate->hj_CurTuple;

	for (;;)
	{
		/*
		 * hj_CurTuple is the address of the tuple last returned from the
		 * current bucket, or NULL if it's time to start scanning a new
		 * bucket.
		 */
		if (hashTuple != NULL)
			hashTuple = hashTuple->next.unshared;
		else if (hjstate->hj_CurBucketNo < hashtable->nbuckets)
		{
			hashTuple = hashtable->buckets.unshared[hjstate->hj_CurBucketNo];
			hjstate->hj_CurBucketNo++;
		}
		else if (hjstate->hj_CurSkewBucketNo < hashtable->nSkewBuckets)
		{
			int			j = hashtable->skewBucketNums[hjstate->hj_CurSkewBucketNo];

			hashTuple = hashtable->skewBucket[j]->tuples;
			hjstate->hj_CurSkewBucketNo++;
		}
		else
			break;				/* finished all buckets */

		while (hashTuple != NULL)
		{
			if (!HeapTupleHeaderHasMatch(HJTUPLE_MINTUPLE(hashTuple)))
			{
				TupleTableSlot *inntuple;

				/* insert hashtable's tuple into exec slot */
				inntuple = ExecStoreMinimalTuple(HJTUPLE_MINTUPLE(hashTuple),
												 hjstate->hj_HashTupleSlot,
												 false);	/* do not pfree */
				econtext->ecxt_innertuple = inntuple;

				/*
				 * Reset temp memory each time; although this function doesn't
				 * do any qual eval, the caller will, so let's keep it
				 * parallel to ExecScanHashBucket.
				 */
				ResetExprContext(econtext);

				hjstate->hj_CurTuple = hashTuple;
				return true;
			}

			hashTuple = hashTuple->next.unshared;
		}

		/* allow this loop to be cancellable */
		CHECK_FOR_INTERRUPTS();
	}

	/*
	 * no more unmatched tuples
	 */
	return false;
}