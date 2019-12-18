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
typedef  int uint32 ;
struct TYPE_13__ {int max_bucket; long nsegs; long dsize; long low_mask; int high_mask; } ;
struct TYPE_12__ {struct TYPE_12__* link; int /*<<< orphan*/  hashvalue; } ;
struct TYPE_11__ {long sshift; TYPE_2__*** dir; int /*<<< orphan*/  ssize; TYPE_3__* hctl; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__** HASHSEGMENT ;
typedef  TYPE_3__ HASHHDR ;
typedef  TYPE_2__* HASHBUCKET ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IS_PARTITIONED (TYPE_3__*) ; 
 long MOD (long,int /*<<< orphan*/ ) ; 
 scalar_t__ calc_bucket (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_realloc (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_expansions ; 
 TYPE_2__** seg_alloc (TYPE_1__*) ; 

__attribute__((used)) static bool
expand_table(HTAB *hashp)
{
	HASHHDR    *hctl = hashp->hctl;
	HASHSEGMENT old_seg,
				new_seg;
	long		old_bucket,
				new_bucket;
	long		new_segnum,
				new_segndx;
	long		old_segnum,
				old_segndx;
	HASHBUCKET *oldlink,
			   *newlink;
	HASHBUCKET	currElement,
				nextElement;

	Assert(!IS_PARTITIONED(hctl));

#ifdef HASH_STATISTICS
	hash_expansions++;
#endif

	new_bucket = hctl->max_bucket + 1;
	new_segnum = new_bucket >> hashp->sshift;
	new_segndx = MOD(new_bucket, hashp->ssize);

	if (new_segnum >= hctl->nsegs)
	{
		/* Allocate new segment if necessary -- could fail if dir full */
		if (new_segnum >= hctl->dsize)
			if (!dir_realloc(hashp))
				return false;
		if (!(hashp->dir[new_segnum] = seg_alloc(hashp)))
			return false;
		hctl->nsegs++;
	}

	/* OK, we created a new bucket */
	hctl->max_bucket++;

	/*
	 * *Before* changing masks, find old bucket corresponding to same hash
	 * values; values in that bucket may need to be relocated to new bucket.
	 * Note that new_bucket is certainly larger than low_mask at this point,
	 * so we can skip the first step of the regular hash mask calc.
	 */
	old_bucket = (new_bucket & hctl->low_mask);

	/*
	 * If we crossed a power of 2, readjust masks.
	 */
	if ((uint32) new_bucket > hctl->high_mask)
	{
		hctl->low_mask = hctl->high_mask;
		hctl->high_mask = (uint32) new_bucket | hctl->low_mask;
	}

	/*
	 * Relocate records to the new bucket.  NOTE: because of the way the hash
	 * masking is done in calc_bucket, only one old bucket can need to be
	 * split at this point.  With a different way of reducing the hash value,
	 * that might not be true!
	 */
	old_segnum = old_bucket >> hashp->sshift;
	old_segndx = MOD(old_bucket, hashp->ssize);

	old_seg = hashp->dir[old_segnum];
	new_seg = hashp->dir[new_segnum];

	oldlink = &old_seg[old_segndx];
	newlink = &new_seg[new_segndx];

	for (currElement = *oldlink;
		 currElement != NULL;
		 currElement = nextElement)
	{
		nextElement = currElement->link;
		if ((long) calc_bucket(hctl, currElement->hashvalue) == old_bucket)
		{
			*oldlink = currElement;
			oldlink = &currElement->link;
		}
		else
		{
			*newlink = currElement;
			newlink = &currElement->link;
		}
	}
	/* don't forget to terminate the rebuilt hash chains... */
	*oldlink = NULL;
	*newlink = NULL;

	return true;
}