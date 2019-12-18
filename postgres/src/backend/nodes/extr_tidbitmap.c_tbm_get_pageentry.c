#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ blockno; char status; } ;
struct TYPE_8__ {scalar_t__ status; int /*<<< orphan*/  npages; int /*<<< orphan*/  nentries; int /*<<< orphan*/  pagetable; TYPE_2__ entry1; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  TYPE_2__ PagetableEntry ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TBM_EMPTY ; 
 scalar_t__ TBM_ONE_PAGE ; 
 TYPE_2__* pagetable_insert (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  tbm_create_pagetable (TYPE_1__*) ; 

__attribute__((used)) static PagetableEntry *
tbm_get_pageentry(TIDBitmap *tbm, BlockNumber pageno)
{
	PagetableEntry *page;
	bool		found;

	if (tbm->status == TBM_EMPTY)
	{
		/* Use the fixed slot */
		page = &tbm->entry1;
		found = false;
		tbm->status = TBM_ONE_PAGE;
	}
	else
	{
		if (tbm->status == TBM_ONE_PAGE)
		{
			page = &tbm->entry1;
			if (page->blockno == pageno)
				return page;
			/* Time to switch from one page to a hashtable */
			tbm_create_pagetable(tbm);
		}

		/* Look up or create an entry */
		page = pagetable_insert(tbm->pagetable, pageno, &found);
	}

	/* Initialize it if not present before */
	if (!found)
	{
		char		oldstatus = page->status;

		MemSet(page, 0, sizeof(PagetableEntry));
		page->status = oldstatus;
		page->blockno = pageno;
		/* must count it too */
		tbm->nentries++;
		tbm->npages++;
	}

	return page;
}