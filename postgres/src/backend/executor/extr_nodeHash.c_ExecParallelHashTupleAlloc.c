#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer_atomic ;
typedef  scalar_t__ dsa_pointer ;
struct TYPE_20__ {int curbatch; scalar_t__ current_chunk_shared; int nbatch; int nbuckets; int /*<<< orphan*/  area; TYPE_5__* current_chunk; TYPE_3__* batches; TYPE_4__* parallel_state; } ;
struct TYPE_15__ {scalar_t__ shared; } ;
struct TYPE_19__ {size_t maxlen; size_t used; TYPE_1__ next; } ;
struct TYPE_18__ {scalar_t__ growth; scalar_t__ space_allowed; int /*<<< orphan*/  lock; int /*<<< orphan*/  build_barrier; } ;
struct TYPE_17__ {int at_least_one_chunk; TYPE_2__* shared; scalar_t__ ntuples; } ;
struct TYPE_16__ {scalar_t__ size; int space_exhausted; int ntuples; scalar_t__ chunks; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_4__ ParallelHashJoinState ;
typedef  scalar_t__ ParallelHashGrowth ;
typedef  TYPE_5__* HashMemoryChunk ;
typedef  TYPE_5__* HashJoinTuple ;
typedef  TYPE_7__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BarrierPhase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecParallelHashIncreaseNumBatches (TYPE_7__*) ; 
 int /*<<< orphan*/  ExecParallelHashIncreaseNumBuckets (TYPE_7__*) ; 
 TYPE_5__* HASH_CHUNK_DATA (TYPE_5__*) ; 
 scalar_t__ HASH_CHUNK_HEADER_SIZE ; 
 scalar_t__ HASH_CHUNK_SIZE ; 
 size_t HASH_CHUNK_THRESHOLD ; 
 int INT_MAX ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 size_t MAXALIGN (size_t) ; 
 int MaxAllocSize ; 
 int NTUP_PER_BUCKET ; 
 scalar_t__ PHJ_BUILD_HASHING_INNER ; 
 scalar_t__ PHJ_GROWTH_DISABLED ; 
 scalar_t__ PHJ_GROWTH_NEED_MORE_BATCHES ; 
 scalar_t__ PHJ_GROWTH_NEED_MORE_BUCKETS ; 
 scalar_t__ dsa_allocate (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* dsa_get_address (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static HashJoinTuple
ExecParallelHashTupleAlloc(HashJoinTable hashtable, size_t size,
						   dsa_pointer *shared)
{
	ParallelHashJoinState *pstate = hashtable->parallel_state;
	dsa_pointer chunk_shared;
	HashMemoryChunk chunk;
	Size		chunk_size;
	HashJoinTuple result;
	int			curbatch = hashtable->curbatch;

	size = MAXALIGN(size);

	/*
	 * Fast path: if there is enough space in this backend's current chunk,
	 * then we can allocate without any locking.
	 */
	chunk = hashtable->current_chunk;
	if (chunk != NULL &&
		size <= HASH_CHUNK_THRESHOLD &&
		chunk->maxlen - chunk->used >= size)
	{

		chunk_shared = hashtable->current_chunk_shared;
		Assert(chunk == dsa_get_address(hashtable->area, chunk_shared));
		*shared = chunk_shared + HASH_CHUNK_HEADER_SIZE + chunk->used;
		result = (HashJoinTuple) (HASH_CHUNK_DATA(chunk) + chunk->used);
		chunk->used += size;

		Assert(chunk->used <= chunk->maxlen);
		Assert(result == dsa_get_address(hashtable->area, *shared));

		return result;
	}

	/* Slow path: try to allocate a new chunk. */
	LWLockAcquire(&pstate->lock, LW_EXCLUSIVE);

	/*
	 * Check if we need to help increase the number of buckets or batches.
	 */
	if (pstate->growth == PHJ_GROWTH_NEED_MORE_BATCHES ||
		pstate->growth == PHJ_GROWTH_NEED_MORE_BUCKETS)
	{
		ParallelHashGrowth growth = pstate->growth;

		hashtable->current_chunk = NULL;
		LWLockRelease(&pstate->lock);

		/* Another participant has commanded us to help grow. */
		if (growth == PHJ_GROWTH_NEED_MORE_BATCHES)
			ExecParallelHashIncreaseNumBatches(hashtable);
		else if (growth == PHJ_GROWTH_NEED_MORE_BUCKETS)
			ExecParallelHashIncreaseNumBuckets(hashtable);

		/* The caller must retry. */
		return NULL;
	}

	/* Oversized tuples get their own chunk. */
	if (size > HASH_CHUNK_THRESHOLD)
		chunk_size = size + HASH_CHUNK_HEADER_SIZE;
	else
		chunk_size = HASH_CHUNK_SIZE;

	/* Check if it's time to grow batches or buckets. */
	if (pstate->growth != PHJ_GROWTH_DISABLED)
	{
		Assert(curbatch == 0);
		Assert(BarrierPhase(&pstate->build_barrier) == PHJ_BUILD_HASHING_INNER);

		/*
		 * Check if our space limit would be exceeded.  To avoid choking on
		 * very large tuples or very low work_mem setting, we'll always allow
		 * each backend to allocate at least one chunk.
		 */
		if (hashtable->batches[0].at_least_one_chunk &&
			hashtable->batches[0].shared->size +
			chunk_size > pstate->space_allowed)
		{
			pstate->growth = PHJ_GROWTH_NEED_MORE_BATCHES;
			hashtable->batches[0].shared->space_exhausted = true;
			LWLockRelease(&pstate->lock);

			return NULL;
		}

		/* Check if our load factor limit would be exceeded. */
		if (hashtable->nbatch == 1)
		{
			hashtable->batches[0].shared->ntuples += hashtable->batches[0].ntuples;
			hashtable->batches[0].ntuples = 0;
			/* Guard against integer overflow and alloc size overflow */
			if (hashtable->batches[0].shared->ntuples + 1 >
				hashtable->nbuckets * NTUP_PER_BUCKET &&
				hashtable->nbuckets < (INT_MAX / 2) &&
				hashtable->nbuckets * 2 <=
				MaxAllocSize / sizeof(dsa_pointer_atomic))
			{
				pstate->growth = PHJ_GROWTH_NEED_MORE_BUCKETS;
				LWLockRelease(&pstate->lock);

				return NULL;
			}
		}
	}

	/* We are cleared to allocate a new chunk. */
	chunk_shared = dsa_allocate(hashtable->area, chunk_size);
	hashtable->batches[curbatch].shared->size += chunk_size;
	hashtable->batches[curbatch].at_least_one_chunk = true;

	/* Set up the chunk. */
	chunk = (HashMemoryChunk) dsa_get_address(hashtable->area, chunk_shared);
	*shared = chunk_shared + HASH_CHUNK_HEADER_SIZE;
	chunk->maxlen = chunk_size - HASH_CHUNK_HEADER_SIZE;
	chunk->used = size;

	/*
	 * Push it onto the list of chunks, so that it can be found if we need to
	 * increase the number of buckets or batches (batch 0 only) and later for
	 * freeing the memory (all batches).
	 */
	chunk->next.shared = hashtable->batches[curbatch].shared->chunks;
	hashtable->batches[curbatch].shared->chunks = chunk_shared;

	if (size <= HASH_CHUNK_THRESHOLD)
	{
		/*
		 * Make this the current chunk so that we can use the fast path to
		 * fill the rest of it up in future calls.
		 */
		hashtable->current_chunk = chunk;
		hashtable->current_chunk_shared = chunk_shared;
	}
	LWLockRelease(&pstate->lock);

	Assert(HASH_CHUNK_DATA(chunk) == dsa_get_address(hashtable->area, *shared));
	result = (HashJoinTuple) HASH_CHUNK_DATA(chunk);

	return result;
}