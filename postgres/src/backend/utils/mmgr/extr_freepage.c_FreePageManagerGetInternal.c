#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ npages; int /*<<< orphan*/  first_page; } ;
struct TYPE_21__ {int found; size_t index; TYPE_14__* page; } ;
struct TYPE_20__ {size_t contiguous_pages; int contiguous_pages_dirty; size_t singleton_first_page; scalar_t__ singleton_npages; int /*<<< orphan*/  btree_root; int /*<<< orphan*/ * freelist; } ;
struct TYPE_19__ {size_t npages; scalar_t__ magic; int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;
struct TYPE_18__ {TYPE_5__* leaf_key; } ;
struct TYPE_17__ {TYPE_1__ u; } ;
typedef  size_t Size ;
typedef  TYPE_2__ FreePageSpanLeader ;
typedef  TYPE_3__ FreePageManager ;
typedef  TYPE_4__ FreePageBtreeSearchResult ;
typedef  TYPE_5__ FreePageBtreeLeafKey ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t FPM_NUM_FREELISTS ; 
 scalar_t__ FREE_PAGE_SPAN_LEADER_MAGIC ; 
 int /*<<< orphan*/  FreePageBtreeAdjustAncestorKeys (TYPE_3__*,TYPE_14__*) ; 
 int /*<<< orphan*/  FreePageBtreeRemove (TYPE_3__*,TYPE_14__*,size_t) ; 
 int /*<<< orphan*/  FreePageBtreeSearch (TYPE_3__*,size_t,TYPE_4__*) ; 
 int /*<<< orphan*/  FreePagePushSpanLeader (TYPE_3__*,size_t,size_t) ; 
 size_t Min (size_t,size_t) ; 
 size_t fpm_pointer_to_page (char*,TYPE_2__*) ; 
 char* fpm_segment_base (TYPE_3__*) ; 
 TYPE_2__* relptr_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relptr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ relptr_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
FreePageManagerGetInternal(FreePageManager *fpm, Size npages, Size *first_page)
{
	char	   *base = fpm_segment_base(fpm);
	FreePageSpanLeader *victim = NULL;
	FreePageSpanLeader *prev;
	FreePageSpanLeader *next;
	FreePageBtreeSearchResult result;
	Size		victim_page = 0;	/* placate compiler */
	Size		f;

	/*
	 * Search for a free span.
	 *
	 * Right now, we use a simple best-fit policy here, but it's possible for
	 * this to result in memory fragmentation if we're repeatedly asked to
	 * allocate chunks just a little smaller than what we have available.
	 * Hopefully, this is unlikely, because we expect most requests to be
	 * single pages or superblock-sized chunks -- but no policy can be optimal
	 * under all circumstances unless it has knowledge of future allocation
	 * patterns.
	 */
	for (f = Min(npages, FPM_NUM_FREELISTS) - 1; f < FPM_NUM_FREELISTS; ++f)
	{
		/* Skip empty freelists. */
		if (relptr_is_null(fpm->freelist[f]))
			continue;

		/*
		 * All of the freelists except the last one contain only items of a
		 * single size, so we just take the first one.  But the final free
		 * list contains everything too big for any of the other lists, so we
		 * need to search the list.
		 */
		if (f < FPM_NUM_FREELISTS - 1)
			victim = relptr_access(base, fpm->freelist[f]);
		else
		{
			FreePageSpanLeader *candidate;

			candidate = relptr_access(base, fpm->freelist[f]);
			do
			{
				if (candidate->npages >= npages && (victim == NULL ||
													victim->npages > candidate->npages))
				{
					victim = candidate;
					if (victim->npages == npages)
						break;
				}
				candidate = relptr_access(base, candidate->next);
			} while (candidate != NULL);
		}
		break;
	}

	/* If we didn't find an allocatable span, return failure. */
	if (victim == NULL)
		return false;

	/* Remove span from free list. */
	Assert(victim->magic == FREE_PAGE_SPAN_LEADER_MAGIC);
	prev = relptr_access(base, victim->prev);
	next = relptr_access(base, victim->next);
	if (prev != NULL)
		relptr_copy(prev->next, victim->next);
	else
		relptr_copy(fpm->freelist[f], victim->next);
	if (next != NULL)
		relptr_copy(next->prev, victim->prev);
	victim_page = fpm_pointer_to_page(base, victim);

	/* Decide whether we might be invalidating contiguous_pages. */
	if (f == FPM_NUM_FREELISTS - 1 &&
		victim->npages == fpm->contiguous_pages)
	{
		/*
		 * The victim span came from the oversized freelist, and had the same
		 * size as the longest span.  There may or may not be another one of
		 * the same size, so contiguous_pages must be recomputed just to be
		 * safe.
		 */
		fpm->contiguous_pages_dirty = true;
	}
	else if (f + 1 == fpm->contiguous_pages &&
			 relptr_is_null(fpm->freelist[f]))
	{
		/*
		 * The victim span came from a fixed sized freelist, and it was the
		 * list for spans of the same size as the current longest span, and
		 * the list is now empty after removing the victim.  So
		 * contiguous_pages must be recomputed without a doubt.
		 */
		fpm->contiguous_pages_dirty = true;
	}

	/*
	 * If we haven't initialized the btree yet, the victim must be the single
	 * span stored within the FreePageManager itself.  Otherwise, we need to
	 * update the btree.
	 */
	if (relptr_is_null(fpm->btree_root))
	{
		Assert(victim_page == fpm->singleton_first_page);
		Assert(victim->npages == fpm->singleton_npages);
		Assert(victim->npages >= npages);
		fpm->singleton_first_page += npages;
		fpm->singleton_npages -= npages;
		if (fpm->singleton_npages > 0)
			FreePagePushSpanLeader(fpm, fpm->singleton_first_page,
								   fpm->singleton_npages);
	}
	else
	{
		/*
		 * If the span we found is exactly the right size, remove it from the
		 * btree completely.  Otherwise, adjust the btree entry to reflect the
		 * still-unallocated portion of the span, and put that portion on the
		 * appropriate free list.
		 */
		FreePageBtreeSearch(fpm, victim_page, &result);
		Assert(result.found);
		if (victim->npages == npages)
			FreePageBtreeRemove(fpm, result.page, result.index);
		else
		{
			FreePageBtreeLeafKey *key;

			/* Adjust btree to reflect remaining pages. */
			Assert(victim->npages > npages);
			key = &result.page->u.leaf_key[result.index];
			Assert(key->npages == victim->npages);
			key->first_page += npages;
			key->npages -= npages;
			if (result.index == 0)
				FreePageBtreeAdjustAncestorKeys(fpm, result.page);

			/* Put the unallocated pages back on the appropriate free list. */
			FreePagePushSpanLeader(fpm, victim_page + npages,
								   victim->npages - npages);
		}
	}

	/* Return results to caller. */
	*first_page = fpm_pointer_to_page(base, victim);
	return true;
}