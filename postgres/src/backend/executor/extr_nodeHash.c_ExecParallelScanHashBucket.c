#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_13__ {int /*<<< orphan*/ * ecxt_innertuple; } ;
struct TYPE_12__ {scalar_t__ hj_CurHashValue; TYPE_1__* hj_CurTuple; int /*<<< orphan*/  hj_HashTupleSlot; int /*<<< orphan*/  hj_CurBucketNo; int /*<<< orphan*/  hj_HashTable; int /*<<< orphan*/ * hashclauses; } ;
struct TYPE_11__ {scalar_t__ hashvalue; } ;
typedef  TYPE_1__* HashJoinTuple ;
typedef  int /*<<< orphan*/  HashJoinTable ;
typedef  TYPE_2__ HashJoinState ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_3__ ExprContext ;

/* Variables and functions */
 TYPE_1__* ExecParallelHashFirstTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ExecParallelHashNextTuple (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ExecQualAndReset (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * ExecStoreMinimalTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HJTUPLE_MINTUPLE (TYPE_1__*) ; 

bool
ExecParallelScanHashBucket(HashJoinState *hjstate,
						   ExprContext *econtext)
{
	ExprState  *hjclauses = hjstate->hashclauses;
	HashJoinTable hashtable = hjstate->hj_HashTable;
	HashJoinTuple hashTuple = hjstate->hj_CurTuple;
	uint32		hashvalue = hjstate->hj_CurHashValue;

	/*
	 * hj_CurTuple is the address of the tuple last returned from the current
	 * bucket, or NULL if it's time to start scanning a new bucket.
	 */
	if (hashTuple != NULL)
		hashTuple = ExecParallelHashNextTuple(hashtable, hashTuple);
	else
		hashTuple = ExecParallelHashFirstTuple(hashtable,
											   hjstate->hj_CurBucketNo);

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

		hashTuple = ExecParallelHashNextTuple(hashtable, hashTuple);
	}

	/*
	 * no match
	 */
	return false;
}