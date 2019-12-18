#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pagetable_iterator ;
struct TYPE_10__ {int /*<<< orphan*/  blockno; scalar_t__ ischunk; } ;
struct TYPE_9__ {scalar_t__ nentries; scalar_t__ status; int /*<<< orphan*/  pagetable; int /*<<< orphan*/  npages; int /*<<< orphan*/  nchunks; TYPE_2__ entry1; int /*<<< orphan*/  iterating; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  TYPE_2__ PagetableEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TBM_EMPTY ; 
 scalar_t__ TBM_HASH ; 
 scalar_t__ TBM_ONE_PAGE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pagetable_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* pagetable_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagetable_start_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tbm_intersect_page (TYPE_1__*,TYPE_2__*,TYPE_1__ const*) ; 

void
tbm_intersect(TIDBitmap *a, const TIDBitmap *b)
{
	Assert(!a->iterating);
	/* Nothing to do if a is empty */
	if (a->nentries == 0)
		return;
	/* Scan through chunks and pages in a, try to match to b */
	if (a->status == TBM_ONE_PAGE)
	{
		if (tbm_intersect_page(a, &a->entry1, b))
		{
			/* Page is now empty, remove it from a */
			Assert(!a->entry1.ischunk);
			a->npages--;
			a->nentries--;
			Assert(a->nentries == 0);
			a->status = TBM_EMPTY;
		}
	}
	else
	{
		pagetable_iterator i;
		PagetableEntry *apage;

		Assert(a->status == TBM_HASH);
		pagetable_start_iterate(a->pagetable, &i);
		while ((apage = pagetable_iterate(a->pagetable, &i)) != NULL)
		{
			if (tbm_intersect_page(a, apage, b))
			{
				/* Page or chunk is now empty, remove it from a */
				if (apage->ischunk)
					a->nchunks--;
				else
					a->npages--;
				a->nentries--;
				if (!pagetable_delete(a->pagetable, apage->blockno))
					elog(ERROR, "hash table corrupted");
			}
		}
	}
}