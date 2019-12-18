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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_18__ {int /*<<< orphan*/ * ecxt_innertuple; } ;
struct TYPE_17__ {scalar_t__ hj_CurHashValue; size_t hj_CurSkewBucketNo; size_t hj_CurBucketNo; TYPE_4__* hj_CurTuple; int /*<<< orphan*/  hj_HashTupleSlot; TYPE_5__* hj_HashTable; int /*<<< orphan*/ * hashclauses; } ;
struct TYPE_13__ {TYPE_4__** unshared; } ;
struct TYPE_16__ {TYPE_2__ buckets; TYPE_1__** skewBucket; } ;
struct TYPE_14__ {TYPE_4__* unshared; } ;
struct TYPE_15__ {scalar_t__ hashvalue; TYPE_3__ next; } ;
struct TYPE_12__ {TYPE_4__* tuples; } ;
typedef  TYPE_4__* HashJoinTuple ;
typedef  TYPE_5__* HashJoinTable ;
typedef  TYPE_6__ HashJoinState ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_7__ ExprContext ;

/* Variables and functions */
 scalar_t__ ExecQualAndReset (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/ * ExecStoreMinimalTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HJTUPLE_MINTUPLE (TYPE_4__*) ; 
 size_t INVALID_SKEW_BUCKET_NO ; 

bool
ExecScanHashBucket(HashJoinState *hjstate,
				   ExprContext *econtext)
{
	ExprState  *hjclauses = hjstate->hashclauses;
	HashJoinTable hashtable = hjstate->hj_HashTable;
	HashJoinTuple hashTuple = hjstate->hj_CurTuple;
	uint32		hashvalue = hjstate->hj_CurHashValue;

	/*
	 * hj_CurTuple is the address of the tuple last returned from the current
	 * bucket, or NULL if it's time to start scanning a new bucket.
	 *
	 * If the tuple hashed to a skew bucket then scan the skew bucket
	 * otherwise scan the standard hashtable bucket.
	 */
	if (hashTuple != NULL)
		hashTuple = hashTuple->next.unshared;
	else if (hjstate->hj_CurSkewBucketNo != INVALID_SKEW_BUCKET_NO)
		hashTuple = hashtable->skewBucket[hjstate->hj_CurSkewBucketNo]->tuples;
	else
		hashTuple = hashtable->buckets.unshared[hjstate->hj_CurBucketNo];

	while (hashTuple != NULL)
	{
		if (hashTuple->hashvalue == hashvalue)
		{
			TupleTableSlot *inntuple;

			/* insert hashtable's tuple into exec slot so ExecQual sees it */
			inntuple = ExecStoreMinimalTuple(HJTUPLE_MINTUPLE(hashTuple),
											 hjstate->hj_HashTupleSlot,
											 false);	/* do not pfree */
			econtext->ecxt_innertuple = inntuple;

			if (ExecQualAndReset(hjclauses, econtext))
			{
				hjstate->hj_CurTuple = hashTuple;
				return true;
			}
		}

		hashTuple = hashTuple->next.unshared;
	}

	/*
	 * no match
	 */
	return false;
}