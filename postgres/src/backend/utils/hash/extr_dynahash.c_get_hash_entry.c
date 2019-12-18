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
struct TYPE_12__ {struct TYPE_12__* link; } ;
struct TYPE_11__ {TYPE_1__* freeList; int /*<<< orphan*/  nelem_alloc; } ;
struct TYPE_10__ {TYPE_3__* hctl; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  nentries; TYPE_4__* freeList; } ;
typedef  TYPE_2__ HTAB ;
typedef  TYPE_3__ HASHHDR ;
typedef  TYPE_4__* HASHBUCKET ;

/* Variables and functions */
 scalar_t__ IS_PARTITIONED (TYPE_3__*) ; 
 int NUM_FREELISTS ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  element_alloc (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HASHBUCKET
get_hash_entry(HTAB *hashp, int freelist_idx)
{
	HASHHDR    *hctl = hashp->hctl;
	HASHBUCKET	newElement;

	for (;;)
	{
		/* if partitioned, must lock to touch nentries and freeList */
		if (IS_PARTITIONED(hctl))
			SpinLockAcquire(&hctl->freeList[freelist_idx].mutex);

		/* try to get an entry from the freelist */
		newElement = hctl->freeList[freelist_idx].freeList;

		if (newElement != NULL)
			break;

		if (IS_PARTITIONED(hctl))
			SpinLockRelease(&hctl->freeList[freelist_idx].mutex);

		/*
		 * No free elements in this freelist.  In a partitioned table, there
		 * might be entries in other freelists, but to reduce contention we
		 * prefer to first try to get another chunk of buckets from the main
		 * shmem allocator.  If that fails, though, we *MUST* root through all
		 * the other freelists before giving up.  There are multiple callers
		 * that assume that they can allocate every element in the initially
		 * requested table size, or that deleting an element guarantees they
		 * can insert a new element, even if shared memory is entirely full.
		 * Failing because the needed element is in a different freelist is
		 * not acceptable.
		 */
		if (!element_alloc(hashp, hctl->nelem_alloc, freelist_idx))
		{
			int			borrow_from_idx;

			if (!IS_PARTITIONED(hctl))
				return NULL;	/* out of memory */

			/* try to borrow element from another freelist */
			borrow_from_idx = freelist_idx;
			for (;;)
			{
				borrow_from_idx = (borrow_from_idx + 1) % NUM_FREELISTS;
				if (borrow_from_idx == freelist_idx)
					break;		/* examined all freelists, fail */

				SpinLockAcquire(&(hctl->freeList[borrow_from_idx].mutex));
				newElement = hctl->freeList[borrow_from_idx].freeList;

				if (newElement != NULL)
				{
					hctl->freeList[borrow_from_idx].freeList = newElement->link;
					SpinLockRelease(&(hctl->freeList[borrow_from_idx].mutex));

					/* careful: count the new element in its proper freelist */
					SpinLockAcquire(&hctl->freeList[freelist_idx].mutex);
					hctl->freeList[freelist_idx].nentries++;
					SpinLockRelease(&hctl->freeList[freelist_idx].mutex);

					return newElement;
				}

				SpinLockRelease(&(hctl->freeList[borrow_from_idx].mutex));
			}

			/* no elements available to borrow either, so out of memory */
			return NULL;
		}
	}

	/* remove entry from freelist, bump nentries */
	hctl->freeList[freelist_idx].freeList = newElement->link;
	hctl->freeList[freelist_idx].nentries++;

	if (IS_PARTITIONED(hctl))
		SpinLockRelease(&hctl->freeList[freelist_idx].mutex);

	return newElement;
}