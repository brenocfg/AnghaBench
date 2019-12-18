#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer_atomic ;
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_12__ {int curbatch; int nbuckets; int /*<<< orphan*/  spacePeak; int /*<<< orphan*/  area; TYPE_1__* batches; int /*<<< orphan*/ * parallel_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  shared; } ;
struct TYPE_11__ {TYPE_2__ next; } ;
struct TYPE_10__ {scalar_t__ size; int /*<<< orphan*/  buckets; int /*<<< orphan*/  chunks; int /*<<< orphan*/  batch_barrier; } ;
struct TYPE_8__ {int /*<<< orphan*/  outer_tuples; int /*<<< orphan*/  inner_tuples; TYPE_3__* shared; } ;
typedef  TYPE_3__ ParallelHashJoinBatch ;
typedef  TYPE_4__* HashMemoryChunk ;
typedef  TYPE_5__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BarrierArriveAndDetach (int /*<<< orphan*/ *) ; 
 scalar_t__ BarrierPhase (int /*<<< orphan*/ *) ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  Max (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PHJ_BATCH_DONE ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sts_end_parallel_scan (int /*<<< orphan*/ ) ; 

void
ExecHashTableDetachBatch(HashJoinTable hashtable)
{
	if (hashtable->parallel_state != NULL &&
		hashtable->curbatch >= 0)
	{
		int			curbatch = hashtable->curbatch;
		ParallelHashJoinBatch *batch = hashtable->batches[curbatch].shared;

		/* Make sure any temporary files are closed. */
		sts_end_parallel_scan(hashtable->batches[curbatch].inner_tuples);
		sts_end_parallel_scan(hashtable->batches[curbatch].outer_tuples);

		/* Detach from the batch we were last working on. */
		if (BarrierArriveAndDetach(&batch->batch_barrier))
		{
			/*
			 * Technically we shouldn't access the barrier because we're no
			 * longer attached, but since there is no way it's moving after
			 * this point it seems safe to make the following assertion.
			 */
			Assert(BarrierPhase(&batch->batch_barrier) == PHJ_BATCH_DONE);

			/* Free shared chunks and buckets. */
			while (DsaPointerIsValid(batch->chunks))
			{
				HashMemoryChunk chunk =
				dsa_get_address(hashtable->area, batch->chunks);
				dsa_pointer next = chunk->next.shared;

				dsa_free(hashtable->area, batch->chunks);
				batch->chunks = next;
			}
			if (DsaPointerIsValid(batch->buckets))
			{
				dsa_free(hashtable->area, batch->buckets);
				batch->buckets = InvalidDsaPointer;
			}
		}

		/*
		 * Track the largest batch we've been attached to.  Though each
		 * backend might see a different subset of batches, explain.c will
		 * scan the results from all backends to find the largest value.
		 */
		hashtable->spacePeak =
			Max(hashtable->spacePeak,
				batch->size + sizeof(dsa_pointer_atomic) * hashtable->nbuckets);

		/* Remember that we are not attached to a batch. */
		hashtable->curbatch = -1;
	}
}