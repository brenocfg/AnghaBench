#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer_atomic ;
typedef  scalar_t__ dsa_pointer ;
struct TYPE_25__ {scalar_t__ t_len; } ;
struct TYPE_20__ {int /*<<< orphan*/ * shared; } ;
struct TYPE_24__ {TYPE_3__ buckets; TYPE_2__* batches; int /*<<< orphan*/  area; TYPE_4__* parallel_state; } ;
struct TYPE_23__ {int /*<<< orphan*/  hashvalue; } ;
struct TYPE_22__ {size_t used; } ;
struct TYPE_21__ {int nbuckets; int /*<<< orphan*/  grow_buckets_barrier; int /*<<< orphan*/  growth; int /*<<< orphan*/  chunk_work_queue; int /*<<< orphan*/  build_barrier; } ;
struct TYPE_19__ {TYPE_1__* shared; } ;
struct TYPE_18__ {size_t size; int /*<<< orphan*/  chunks; int /*<<< orphan*/  buckets; } ;
typedef  TYPE_4__ ParallelHashJoinState ;
typedef  TYPE_5__* HashMemoryChunk ;
typedef  TYPE_6__* HashJoinTuple ;
typedef  TYPE_7__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BarrierArriveAndWait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BarrierPhase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExecHashGetBucketAndBatch (TYPE_7__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ExecParallelHashEnsureBatchAccessors (TYPE_7__*) ; 
 TYPE_5__* ExecParallelHashPopChunkQueue (TYPE_7__*,scalar_t__*) ; 
 int /*<<< orphan*/  ExecParallelHashPushTuple (int /*<<< orphan*/ *,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ExecParallelHashTableSetCurrentBatch (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_CHUNK_DATA (TYPE_5__*) ; 
 scalar_t__ HASH_CHUNK_HEADER_SIZE ; 
 TYPE_8__* HJTUPLE_MINTUPLE (TYPE_6__*) ; 
 scalar_t__ HJTUPLE_OVERHEAD ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 size_t MAXALIGN (scalar_t__) ; 
 scalar_t__ PHJ_BUILD_HASHING_INNER ; 
 int /*<<< orphan*/  PHJ_GROWTH_OK ; 
#define  PHJ_GROW_BUCKETS_ALLOCATING 130 
#define  PHJ_GROW_BUCKETS_ELECTING 129 
 int PHJ_GROW_BUCKETS_PHASE (scalar_t__) ; 
#define  PHJ_GROW_BUCKETS_REINSERTING 128 
 int /*<<< orphan*/  WAIT_EVENT_HASH_GROW_BUCKETS_ALLOCATING ; 
 int /*<<< orphan*/  WAIT_EVENT_HASH_GROW_BUCKETS_ELECTING ; 
 int /*<<< orphan*/  WAIT_EVENT_HASH_GROW_BUCKETS_REINSERTING ; 
 int /*<<< orphan*/  dsa_allocate (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_pointer_atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExecParallelHashIncreaseNumBuckets(HashJoinTable hashtable)
{
	ParallelHashJoinState *pstate = hashtable->parallel_state;
	int			i;
	HashMemoryChunk chunk;
	dsa_pointer chunk_s;

	Assert(BarrierPhase(&pstate->build_barrier) == PHJ_BUILD_HASHING_INNER);

	/*
	 * It's unlikely, but we need to be prepared for new participants to show
	 * up while we're in the middle of this operation so we need to switch on
	 * barrier phase here.
	 */
	switch (PHJ_GROW_BUCKETS_PHASE(BarrierPhase(&pstate->grow_buckets_barrier)))
	{
		case PHJ_GROW_BUCKETS_ELECTING:
			/* Elect one participant to prepare to increase nbuckets. */
			if (BarrierArriveAndWait(&pstate->grow_buckets_barrier,
									 WAIT_EVENT_HASH_GROW_BUCKETS_ELECTING))
			{
				size_t		size;
				dsa_pointer_atomic *buckets;

				/* Double the size of the bucket array. */
				pstate->nbuckets *= 2;
				size = pstate->nbuckets * sizeof(dsa_pointer_atomic);
				hashtable->batches[0].shared->size += size / 2;
				dsa_free(hashtable->area, hashtable->batches[0].shared->buckets);
				hashtable->batches[0].shared->buckets =
					dsa_allocate(hashtable->area, size);
				buckets = (dsa_pointer_atomic *)
					dsa_get_address(hashtable->area,
									hashtable->batches[0].shared->buckets);
				for (i = 0; i < pstate->nbuckets; ++i)
					dsa_pointer_atomic_init(&buckets[i], InvalidDsaPointer);

				/* Put the chunk list onto the work queue. */
				pstate->chunk_work_queue = hashtable->batches[0].shared->chunks;

				/* Clear the flag. */
				pstate->growth = PHJ_GROWTH_OK;
			}
			/* Fall through. */

		case PHJ_GROW_BUCKETS_ALLOCATING:
			/* Wait for the above to complete. */
			BarrierArriveAndWait(&pstate->grow_buckets_barrier,
								 WAIT_EVENT_HASH_GROW_BUCKETS_ALLOCATING);
			/* Fall through. */

		case PHJ_GROW_BUCKETS_REINSERTING:
			/* Reinsert all tuples into the hash table. */
			ExecParallelHashEnsureBatchAccessors(hashtable);
			ExecParallelHashTableSetCurrentBatch(hashtable, 0);
			while ((chunk = ExecParallelHashPopChunkQueue(hashtable, &chunk_s)))
			{
				size_t		idx = 0;

				while (idx < chunk->used)
				{
					HashJoinTuple hashTuple = (HashJoinTuple) (HASH_CHUNK_DATA(chunk) + idx);
					dsa_pointer shared = chunk_s + HASH_CHUNK_HEADER_SIZE + idx;
					int			bucketno;
					int			batchno;

					ExecHashGetBucketAndBatch(hashtable, hashTuple->hashvalue,
											  &bucketno, &batchno);
					Assert(batchno == 0);

					/* add the tuple to the proper bucket */
					ExecParallelHashPushTuple(&hashtable->buckets.shared[bucketno],
											  hashTuple, shared);

					/* advance index past the tuple */
					idx += MAXALIGN(HJTUPLE_OVERHEAD +
									HJTUPLE_MINTUPLE(hashTuple)->t_len);
				}

				/* allow this loop to be cancellable */
				CHECK_FOR_INTERRUPTS();
			}
			BarrierArriveAndWait(&pstate->grow_buckets_barrier,
								 WAIT_EVENT_HASH_GROW_BUCKETS_REINSERTING);
	}
}