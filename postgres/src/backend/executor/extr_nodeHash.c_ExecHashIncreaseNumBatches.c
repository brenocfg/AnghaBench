#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_6__** unshared; } ;
struct TYPE_31__ {int nbatch; int curbatch; int growEnabled; int spaceUsed; int nbuckets_optimal; int nbuckets; TYPE_6__** innerBatchFile; TYPE_3__ buckets; TYPE_5__* chunks; int /*<<< orphan*/  log2_nbuckets_optimal; int /*<<< orphan*/  log2_nbuckets; TYPE_6__** outerBatchFile; int /*<<< orphan*/  hashCxt; } ;
struct TYPE_26__ {TYPE_6__* unshared; } ;
struct TYPE_30__ {int /*<<< orphan*/  hashvalue; TYPE_2__ next; } ;
struct TYPE_25__ {TYPE_5__* unshared; } ;
struct TYPE_29__ {size_t used; TYPE_1__ next; } ;
struct TYPE_28__ {int t_len; } ;
typedef  TYPE_4__* MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_5__* HashMemoryChunk ;
typedef  TYPE_6__* HashJoinTuple ;
typedef  TYPE_7__* HashJoinTable ;
typedef  TYPE_6__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExecHashGetBucketAndBatch (TYPE_7__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ExecHashJoinSaveTuple (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__**) ; 
 scalar_t__ HASH_CHUNK_DATA (TYPE_5__*) ; 
 TYPE_4__* HJTUPLE_MINTUPLE (TYPE_6__*) ; 
 int HJTUPLE_OVERHEAD ; 
 int INT_MAX ; 
 scalar_t__ MAXALIGN (int) ; 
 int MaxAllocSize ; 
 int /*<<< orphan*/  MemSet (TYPE_6__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  PrepareTempTablespaces () ; 
 int /*<<< orphan*/  dense_alloc (TYPE_7__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_5__*) ; 
 int /*<<< orphan*/  printf (char*,TYPE_7__*,...) ; 
 TYPE_6__** repalloc (TYPE_6__**,int) ; 

__attribute__((used)) static void
ExecHashIncreaseNumBatches(HashJoinTable hashtable)
{
	int			oldnbatch = hashtable->nbatch;
	int			curbatch = hashtable->curbatch;
	int			nbatch;
	MemoryContext oldcxt;
	long		ninmemory;
	long		nfreed;
	HashMemoryChunk oldchunks;

	/* do nothing if we've decided to shut off growth */
	if (!hashtable->growEnabled)
		return;

	/* safety check to avoid overflow */
	if (oldnbatch > Min(INT_MAX / 2, MaxAllocSize / (sizeof(void *) * 2)))
		return;

	nbatch = oldnbatch * 2;
	Assert(nbatch > 1);

#ifdef HJDEBUG
	printf("Hashjoin %p: increasing nbatch to %d because space = %zu\n",
		   hashtable, nbatch, hashtable->spaceUsed);
#endif

	oldcxt = MemoryContextSwitchTo(hashtable->hashCxt);

	if (hashtable->innerBatchFile == NULL)
	{
		/* we had no file arrays before */
		hashtable->innerBatchFile = (BufFile **)
			palloc0(nbatch * sizeof(BufFile *));
		hashtable->outerBatchFile = (BufFile **)
			palloc0(nbatch * sizeof(BufFile *));
		/* time to establish the temp tablespaces, too */
		PrepareTempTablespaces();
	}
	else
	{
		/* enlarge arrays and zero out added entries */
		hashtable->innerBatchFile = (BufFile **)
			repalloc(hashtable->innerBatchFile, nbatch * sizeof(BufFile *));
		hashtable->outerBatchFile = (BufFile **)
			repalloc(hashtable->outerBatchFile, nbatch * sizeof(BufFile *));
		MemSet(hashtable->innerBatchFile + oldnbatch, 0,
			   (nbatch - oldnbatch) * sizeof(BufFile *));
		MemSet(hashtable->outerBatchFile + oldnbatch, 0,
			   (nbatch - oldnbatch) * sizeof(BufFile *));
	}

	MemoryContextSwitchTo(oldcxt);

	hashtable->nbatch = nbatch;

	/*
	 * Scan through the existing hash table entries and dump out any that are
	 * no longer of the current batch.
	 */
	ninmemory = nfreed = 0;

	/* If know we need to resize nbuckets, we can do it while rebatching. */
	if (hashtable->nbuckets_optimal != hashtable->nbuckets)
	{
		/* we never decrease the number of buckets */
		Assert(hashtable->nbuckets_optimal > hashtable->nbuckets);

		hashtable->nbuckets = hashtable->nbuckets_optimal;
		hashtable->log2_nbuckets = hashtable->log2_nbuckets_optimal;

		hashtable->buckets.unshared =
			repalloc(hashtable->buckets.unshared,
					 sizeof(HashJoinTuple) * hashtable->nbuckets);
	}

	/*
	 * We will scan through the chunks directly, so that we can reset the
	 * buckets now and not have to keep track which tuples in the buckets have
	 * already been processed. We will free the old chunks as we go.
	 */
	memset(hashtable->buckets.unshared, 0,
		   sizeof(HashJoinTuple) * hashtable->nbuckets);
	oldchunks = hashtable->chunks;
	hashtable->chunks = NULL;

	/* so, let's scan through the old chunks, and all tuples in each chunk */
	while (oldchunks != NULL)
	{
		HashMemoryChunk nextchunk = oldchunks->next.unshared;

		/* position within the buffer (up to oldchunks->used) */
		size_t		idx = 0;

		/* process all tuples stored in this chunk (and then free it) */
		while (idx < oldchunks->used)
		{
			HashJoinTuple hashTuple = (HashJoinTuple) (HASH_CHUNK_DATA(oldchunks) + idx);
			MinimalTuple tuple = HJTUPLE_MINTUPLE(hashTuple);
			int			hashTupleSize = (HJTUPLE_OVERHEAD + tuple->t_len);
			int			bucketno;
			int			batchno;

			ninmemory++;
			ExecHashGetBucketAndBatch(hashtable, hashTuple->hashvalue,
									  &bucketno, &batchno);

			if (batchno == curbatch)
			{
				/* keep tuple in memory - copy it into the new chunk */
				HashJoinTuple copyTuple;

				copyTuple = (HashJoinTuple) dense_alloc(hashtable, hashTupleSize);
				memcpy(copyTuple, hashTuple, hashTupleSize);

				/* and add it back to the appropriate bucket */
				copyTuple->next.unshared = hashtable->buckets.unshared[bucketno];
				hashtable->buckets.unshared[bucketno] = copyTuple;
			}
			else
			{
				/* dump it out */
				Assert(batchno > curbatch);
				ExecHashJoinSaveTuple(HJTUPLE_MINTUPLE(hashTuple),
									  hashTuple->hashvalue,
									  &hashtable->innerBatchFile[batchno]);

				hashtable->spaceUsed -= hashTupleSize;
				nfreed++;
			}

			/* next tuple in this chunk */
			idx += MAXALIGN(hashTupleSize);

			/* allow this loop to be cancellable */
			CHECK_FOR_INTERRUPTS();
		}

		/* we're done with this chunk - free it and proceed to the next one */
		pfree(oldchunks);
		oldchunks = nextchunk;
	}

#ifdef HJDEBUG
	printf("Hashjoin %p: freed %ld of %ld tuples, space now %zu\n",
		   hashtable, nfreed, ninmemory, hashtable->spaceUsed);
#endif

	/*
	 * If we dumped out either all or none of the tuples in the table, disable
	 * further expansion of nbatch.  This situation implies that we have
	 * enough tuples of identical hashvalues to overflow spaceAllowed.
	 * Increasing nbatch will not fix it since there's no way to subdivide the
	 * group any more finely. We have to just gut it out and hope the server
	 * has enough RAM.
	 */
	if (nfreed == 0 || nfreed == ninmemory)
	{
		hashtable->growEnabled = false;
#ifdef HJDEBUG
		printf("Hashjoin %p: disabling further increase of nbatch\n",
			   hashtable);
#endif
	}
}