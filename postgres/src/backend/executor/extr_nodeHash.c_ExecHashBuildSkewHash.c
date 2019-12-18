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
typedef  int uint32 ;
struct TYPE_12__ {int nvalues; int /*<<< orphan*/ * values; scalar_t__* numbers; } ;
struct TYPE_11__ {int /*<<< orphan*/  skewInherit; int /*<<< orphan*/  skewColumn; int /*<<< orphan*/  skewTable; } ;
struct TYPE_10__ {int skewEnabled; int skewBucketLen; int* skewBucketNums; scalar_t__ spaceUsed; int spaceUsedSkew; scalar_t__ spacePeak; size_t nSkewBuckets; TYPE_1__** skewBucket; int /*<<< orphan*/  batchCxt; int /*<<< orphan*/ * collations; int /*<<< orphan*/ * outer_hashfunctions; } ;
struct TYPE_9__ {int hashvalue; int /*<<< orphan*/ * tuples; } ;
typedef  int /*<<< orphan*/  HeapTupleData ;
typedef  TYPE_1__ HashSkewBucket ;
typedef  TYPE_2__* HashJoinTable ;
typedef  TYPE_3__ Hash ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  TYPE_4__ AttStatsSlot ;

/* Variables and functions */
 int ATTSTATSSLOT_NUMBERS ; 
 int ATTSTATSSLOT_VALUES ; 
 int /*<<< orphan*/  BoolGetDatum (int /*<<< orphan*/ ) ; 
 int DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 scalar_t__ SKEW_BUCKET_OVERHEAD ; 
 double SKEW_MIN_OUTER_FRACTION ; 
 int /*<<< orphan*/  STATISTIC_KIND_MCV ; 
 int /*<<< orphan*/  STATRELATTINH ; 
 int /*<<< orphan*/ * SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_attstatsslot (TYPE_4__*) ; 
 scalar_t__ get_attstatsslot (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ExecHashBuildSkewHash(HashJoinTable hashtable, Hash *node, int mcvsToUse)
{
	HeapTupleData *statsTuple;
	AttStatsSlot sslot;

	/* Do nothing if planner didn't identify the outer relation's join key */
	if (!OidIsValid(node->skewTable))
		return;
	/* Also, do nothing if we don't have room for at least one skew bucket */
	if (mcvsToUse <= 0)
		return;

	/*
	 * Try to find the MCV statistics for the outer relation's join key.
	 */
	statsTuple = SearchSysCache3(STATRELATTINH,
								 ObjectIdGetDatum(node->skewTable),
								 Int16GetDatum(node->skewColumn),
								 BoolGetDatum(node->skewInherit));
	if (!HeapTupleIsValid(statsTuple))
		return;

	if (get_attstatsslot(&sslot, statsTuple,
						 STATISTIC_KIND_MCV, InvalidOid,
						 ATTSTATSSLOT_VALUES | ATTSTATSSLOT_NUMBERS))
	{
		double		frac;
		int			nbuckets;
		FmgrInfo   *hashfunctions;
		int			i;

		if (mcvsToUse > sslot.nvalues)
			mcvsToUse = sslot.nvalues;

		/*
		 * Calculate the expected fraction of outer relation that will
		 * participate in the skew optimization.  If this isn't at least
		 * SKEW_MIN_OUTER_FRACTION, don't use skew optimization.
		 */
		frac = 0;
		for (i = 0; i < mcvsToUse; i++)
			frac += sslot.numbers[i];
		if (frac < SKEW_MIN_OUTER_FRACTION)
		{
			free_attstatsslot(&sslot);
			ReleaseSysCache(statsTuple);
			return;
		}

		/*
		 * Okay, set up the skew hashtable.
		 *
		 * skewBucket[] is an open addressing hashtable with a power of 2 size
		 * that is greater than the number of MCV values.  (This ensures there
		 * will be at least one null entry, so searches will always
		 * terminate.)
		 *
		 * Note: this code could fail if mcvsToUse exceeds INT_MAX/8 or
		 * MaxAllocSize/sizeof(void *)/8, but that is not currently possible
		 * since we limit pg_statistic entries to much less than that.
		 */
		nbuckets = 2;
		while (nbuckets <= mcvsToUse)
			nbuckets <<= 1;
		/* use two more bits just to help avoid collisions */
		nbuckets <<= 2;

		hashtable->skewEnabled = true;
		hashtable->skewBucketLen = nbuckets;

		/*
		 * We allocate the bucket memory in the hashtable's batch context. It
		 * is only needed during the first batch, and this ensures it will be
		 * automatically removed once the first batch is done.
		 */
		hashtable->skewBucket = (HashSkewBucket **)
			MemoryContextAllocZero(hashtable->batchCxt,
								   nbuckets * sizeof(HashSkewBucket *));
		hashtable->skewBucketNums = (int *)
			MemoryContextAllocZero(hashtable->batchCxt,
								   mcvsToUse * sizeof(int));

		hashtable->spaceUsed += nbuckets * sizeof(HashSkewBucket *)
			+ mcvsToUse * sizeof(int);
		hashtable->spaceUsedSkew += nbuckets * sizeof(HashSkewBucket *)
			+ mcvsToUse * sizeof(int);
		if (hashtable->spaceUsed > hashtable->spacePeak)
			hashtable->spacePeak = hashtable->spaceUsed;

		/*
		 * Create a skew bucket for each MCV hash value.
		 *
		 * Note: it is very important that we create the buckets in order of
		 * decreasing MCV frequency.  If we have to remove some buckets, they
		 * must be removed in reverse order of creation (see notes in
		 * ExecHashRemoveNextSkewBucket) and we want the least common MCVs to
		 * be removed first.
		 */
		hashfunctions = hashtable->outer_hashfunctions;

		for (i = 0; i < mcvsToUse; i++)
		{
			uint32		hashvalue;
			int			bucket;

			hashvalue = DatumGetUInt32(FunctionCall1Coll(&hashfunctions[0],
														 hashtable->collations[0],
														 sslot.values[i]));

			/*
			 * While we have not hit a hole in the hashtable and have not hit
			 * the desired bucket, we have collided with some previous hash
			 * value, so try the next bucket location.  NB: this code must
			 * match ExecHashGetSkewBucket.
			 */
			bucket = hashvalue & (nbuckets - 1);
			while (hashtable->skewBucket[bucket] != NULL &&
				   hashtable->skewBucket[bucket]->hashvalue != hashvalue)
				bucket = (bucket + 1) & (nbuckets - 1);

			/*
			 * If we found an existing bucket with the same hashvalue, leave
			 * it alone.  It's okay for two MCVs to share a hashvalue.
			 */
			if (hashtable->skewBucket[bucket] != NULL)
				continue;

			/* Okay, create a new skew bucket for this hashvalue. */
			hashtable->skewBucket[bucket] = (HashSkewBucket *)
				MemoryContextAlloc(hashtable->batchCxt,
								   sizeof(HashSkewBucket));
			hashtable->skewBucket[bucket]->hashvalue = hashvalue;
			hashtable->skewBucket[bucket]->tuples = NULL;
			hashtable->skewBucketNums[hashtable->nSkewBuckets] = bucket;
			hashtable->nSkewBuckets++;
			hashtable->spaceUsed += SKEW_BUCKET_OVERHEAD;
			hashtable->spaceUsedSkew += SKEW_BUCKET_OVERHEAD;
			if (hashtable->spaceUsed > hashtable->spacePeak)
				hashtable->spacePeak = hashtable->spaceUsed;
		}

		free_attstatsslot(&sslot);
	}

	ReleaseSysCache(statsTuple);
}