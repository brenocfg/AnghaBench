#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_12__ {TYPE_1__* batches; int /*<<< orphan*/  area; TYPE_2__* parallel_state; } ;
struct TYPE_11__ {scalar_t__ t_len; } ;
struct TYPE_10__ {int old_nbatch; int /*<<< orphan*/  fileset; int /*<<< orphan*/  old_batches; } ;
struct TYPE_9__ {size_t estimated_size; int /*<<< orphan*/  inner_tuples; int /*<<< orphan*/  old_ntuples; int /*<<< orphan*/  ntuples; } ;
typedef  int /*<<< orphan*/  SharedTuplestoreAccessor ;
typedef  TYPE_2__ ParallelHashJoinState ;
typedef  int /*<<< orphan*/  ParallelHashJoinBatch ;
typedef  TYPE_3__* MinimalTuple ;
typedef  TYPE_4__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExecHashGetBucketAndBatch (TYPE_4__*,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ HJTUPLE_OVERHEAD ; 
 size_t MAXALIGN (scalar_t__) ; 
 int /*<<< orphan*/ * NthParallelHashJoinBatch (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ParallelHashJoinBatchInner (int /*<<< orphan*/ *) ; 
 scalar_t__ ParallelWorkerNumber ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * sts_attach (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sts_begin_parallel_scan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sts_end_parallel_scan (int /*<<< orphan*/ *) ; 
 TYPE_3__* sts_parallel_scan_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sts_puttuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
ExecParallelHashRepartitionRest(HashJoinTable hashtable)
{
	ParallelHashJoinState *pstate = hashtable->parallel_state;
	int			old_nbatch = pstate->old_nbatch;
	SharedTuplestoreAccessor **old_inner_tuples;
	ParallelHashJoinBatch *old_batches;
	int			i;

	/* Get our hands on the previous generation of batches. */
	old_batches = (ParallelHashJoinBatch *)
		dsa_get_address(hashtable->area, pstate->old_batches);
	old_inner_tuples = palloc0(sizeof(SharedTuplestoreAccessor *) * old_nbatch);
	for (i = 1; i < old_nbatch; ++i)
	{
		ParallelHashJoinBatch *shared =
		NthParallelHashJoinBatch(old_batches, i);

		old_inner_tuples[i] = sts_attach(ParallelHashJoinBatchInner(shared),
										 ParallelWorkerNumber + 1,
										 &pstate->fileset);
	}

	/* Join in the effort to repartition them. */
	for (i = 1; i < old_nbatch; ++i)
	{
		MinimalTuple tuple;
		uint32		hashvalue;

		/* Scan one partition from the previous generation. */
		sts_begin_parallel_scan(old_inner_tuples[i]);
		while ((tuple = sts_parallel_scan_next(old_inner_tuples[i], &hashvalue)))
		{
			size_t		tuple_size = MAXALIGN(HJTUPLE_OVERHEAD + tuple->t_len);
			int			bucketno;
			int			batchno;

			/* Decide which partition it goes to in the new generation. */
			ExecHashGetBucketAndBatch(hashtable, hashvalue, &bucketno,
									  &batchno);

			hashtable->batches[batchno].estimated_size += tuple_size;
			++hashtable->batches[batchno].ntuples;
			++hashtable->batches[i].old_ntuples;

			/* Store the tuple its new batch. */
			sts_puttuple(hashtable->batches[batchno].inner_tuples,
						 &hashvalue, tuple);

			CHECK_FOR_INTERRUPTS();
		}
		sts_end_parallel_scan(old_inner_tuples[i]);
	}

	pfree(old_inner_tuples);
}