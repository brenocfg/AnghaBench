#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ blockno; scalar_t__ ischunk; } ;
struct TYPE_6__ {scalar_t__ nentries; scalar_t__ status; int /*<<< orphan*/  pagetable; TYPE_2__ entry1; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  TYPE_2__ PagetableEntry ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ TBM_ONE_PAGE ; 
 TYPE_2__* pagetable_lookup (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const PagetableEntry *
tbm_find_pageentry(const TIDBitmap *tbm, BlockNumber pageno)
{
	const PagetableEntry *page;

	if (tbm->nentries == 0)		/* in case pagetable doesn't exist */
		return NULL;

	if (tbm->status == TBM_ONE_PAGE)
	{
		page = &tbm->entry1;
		if (page->blockno != pageno)
			return NULL;
		Assert(!page->ischunk);
		return page;
	}

	page = pagetable_lookup(tbm->pagetable, pageno);
	if (page == NULL)
		return NULL;
	if (page->ischunk)
		return NULL;			/* don't want a lossy chunk header */
	return page;
}