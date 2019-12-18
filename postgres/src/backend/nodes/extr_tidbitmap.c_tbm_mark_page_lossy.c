#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int bitmapword ;
struct TYPE_8__ {char status; int blockno; int ischunk; int* words; } ;
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  npages; int /*<<< orphan*/  nchunks; int /*<<< orphan*/  nentries; int /*<<< orphan*/  pagetable; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  TYPE_2__ PagetableEntry ;
typedef  int BlockNumber ;

/* Variables and functions */
 int BITNUM (int) ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int PAGES_PER_CHUNK ; 
 scalar_t__ TBM_HASH ; 
 int WORDNUM (int) ; 
 scalar_t__ pagetable_delete (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* pagetable_insert (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  tbm_create_pagetable (TYPE_1__*) ; 

__attribute__((used)) static void
tbm_mark_page_lossy(TIDBitmap *tbm, BlockNumber pageno)
{
	PagetableEntry *page;
	bool		found;
	BlockNumber chunk_pageno;
	int			bitno;
	int			wordnum;
	int			bitnum;

	/* We force the bitmap into hashtable mode whenever it's lossy */
	if (tbm->status != TBM_HASH)
		tbm_create_pagetable(tbm);

	bitno = pageno % PAGES_PER_CHUNK;
	chunk_pageno = pageno - bitno;

	/*
	 * Remove any extant non-lossy entry for the page.  If the page is its own
	 * chunk header, however, we skip this and handle the case below.
	 */
	if (bitno != 0)
	{
		if (pagetable_delete(tbm->pagetable, pageno))
		{
			/* It was present, so adjust counts */
			tbm->nentries--;
			tbm->npages--;		/* assume it must have been non-lossy */
		}
	}

	/* Look up or create entry for chunk-header page */
	page = pagetable_insert(tbm->pagetable, chunk_pageno, &found);

	/* Initialize it if not present before */
	if (!found)
	{
		char		oldstatus = page->status;

		MemSet(page, 0, sizeof(PagetableEntry));
		page->status = oldstatus;
		page->blockno = chunk_pageno;
		page->ischunk = true;
		/* must count it too */
		tbm->nentries++;
		tbm->nchunks++;
	}
	else if (!page->ischunk)
	{
		char		oldstatus = page->status;

		/* chunk header page was formerly non-lossy, make it lossy */
		MemSet(page, 0, sizeof(PagetableEntry));
		page->status = oldstatus;
		page->blockno = chunk_pageno;
		page->ischunk = true;
		/* we assume it had some tuple bit(s) set, so mark it lossy */
		page->words[0] = ((bitmapword) 1 << 0);
		/* adjust counts */
		tbm->nchunks++;
		tbm->npages--;
	}

	/* Now set the original target page's bit */
	wordnum = WORDNUM(bitno);
	bitnum = BITNUM(bitno);
	page->words[wordnum] |= ((bitmapword) 1 << bitnum);
}