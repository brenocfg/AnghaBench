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
struct TYPE_8__ {TYPE_4__** unshared; } ;
struct TYPE_12__ {int nbuckets; int nSkewBuckets; int* skewBucketNums; TYPE_3__** skewBucket; TYPE_1__ buckets; } ;
struct TYPE_9__ {TYPE_4__* unshared; } ;
struct TYPE_11__ {TYPE_2__ next; } ;
struct TYPE_10__ {TYPE_4__* tuples; } ;
typedef  TYPE_3__ HashSkewBucket ;
typedef  TYPE_4__* HashJoinTuple ;
typedef  TYPE_5__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  HJTUPLE_MINTUPLE (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderClearMatch (int /*<<< orphan*/ ) ; 

void
ExecHashTableResetMatchFlags(HashJoinTable hashtable)
{
	HashJoinTuple tuple;
	int			i;

	/* Reset all flags in the main table ... */
	for (i = 0; i < hashtable->nbuckets; i++)
	{
		for (tuple = hashtable->buckets.unshared[i]; tuple != NULL;
			 tuple = tuple->next.unshared)
			HeapTupleHeaderClearMatch(HJTUPLE_MINTUPLE(tuple));
	}

	/* ... and the same for the skew buckets, if any */
	for (i = 0; i < hashtable->nSkewBuckets; i++)
	{
		int			j = hashtable->skewBucketNums[i];
		HashSkewBucket *skewBucket = hashtable->skewBucket[j];

		for (tuple = skewBucket->tuples; tuple != NULL; tuple = tuple->next.unshared)
			HeapTupleHeaderClearMatch(HJTUPLE_MINTUPLE(tuple));
	}
}