#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cur; } ;
typedef  TYPE_1__ pagetable_iterator ;
struct TYPE_11__ {int blockno; scalar_t__ ischunk; } ;
struct TYPE_10__ {scalar_t__ iterating; scalar_t__ status; int nentries; int maxentries; int /*<<< orphan*/  lossify_start; int /*<<< orphan*/  pagetable; } ;
typedef  TYPE_2__ TIDBitmap ;
typedef  TYPE_3__ PagetableEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int INT_MAX ; 
 int Min (int,int) ; 
 int PAGES_PER_CHUNK ; 
 scalar_t__ TBM_HASH ; 
 scalar_t__ TBM_NOT_ITERATING ; 
 TYPE_3__* pagetable_iterate (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pagetable_start_iterate_at (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_mark_page_lossy (TYPE_2__*,int) ; 

__attribute__((used)) static void
tbm_lossify(TIDBitmap *tbm)
{
	pagetable_iterator i;
	PagetableEntry *page;

	/*
	 * XXX Really stupid implementation: this just lossifies pages in
	 * essentially random order.  We should be paying some attention to the
	 * number of bits set in each page, instead.
	 *
	 * Since we are called as soon as nentries exceeds maxentries, we should
	 * push nentries down to significantly less than maxentries, or else we'll
	 * just end up doing this again very soon.  We shoot for maxentries/2.
	 */
	Assert(tbm->iterating == TBM_NOT_ITERATING);
	Assert(tbm->status == TBM_HASH);

	pagetable_start_iterate_at(tbm->pagetable, &i, tbm->lossify_start);
	while ((page = pagetable_iterate(tbm->pagetable, &i)) != NULL)
	{
		if (page->ischunk)
			continue;			/* already a chunk header */

		/*
		 * If the page would become a chunk header, we won't save anything by
		 * converting it to lossy, so skip it.
		 */
		if ((page->blockno % PAGES_PER_CHUNK) == 0)
			continue;

		/* This does the dirty work ... */
		tbm_mark_page_lossy(tbm, page->blockno);

		if (tbm->nentries <= tbm->maxentries / 2)
		{
			/*
			 * We have made enough room. Remember where to start lossifying
			 * next round, so we evenly iterate over the hashtable.
			 */
			tbm->lossify_start = i.cur;
			break;
		}

		/*
		 * Note: tbm_mark_page_lossy may have inserted a lossy chunk into the
		 * hashtable and may have deleted the non-lossy chunk.  We can
		 * continue the same hash table scan, since failure to visit one
		 * element or visiting the newly inserted element, isn't fatal.
		 */
	}

	/*
	 * With a big bitmap and small work_mem, it's possible that we cannot get
	 * under maxentries.  Again, if that happens, we'd end up uselessly
	 * calling tbm_lossify over and over.  To prevent this from becoming a
	 * performance sink, force maxentries up to at least double the current
	 * number of entries.  (In essence, we're admitting inability to fit
	 * within work_mem when we do this.)  Note that this test will not fire if
	 * we broke out of the loop early; and if we didn't, the current number of
	 * entries is simply not reducible any further.
	 */
	if (tbm->nentries > tbm->maxentries / 2)
		tbm->maxentries = Min(tbm->nentries, (INT_MAX - 1) / 2) * 2;
}