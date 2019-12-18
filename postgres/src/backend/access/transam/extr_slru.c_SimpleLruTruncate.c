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
struct TYPE_8__ {scalar_t__ (* PagePrecedes ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  Dir; TYPE_1__* shared; } ;
struct TYPE_7__ {int num_slots; scalar_t__* page_status; int /*<<< orphan*/  ControlLock; int /*<<< orphan*/ * page_dirty; int /*<<< orphan*/ * page_number; int /*<<< orphan*/  latest_page_number; } ;
typedef  TYPE_1__* SlruShared ;
typedef  TYPE_2__* SlruCtl ;

/* Variables and functions */
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 scalar_t__ SLRU_PAGE_EMPTY ; 
 scalar_t__ SLRU_PAGE_VALID ; 
 int /*<<< orphan*/  SimpleLruWaitIO (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SlruInternalWritePage (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SlruScanDirCbDeleteCutoff ; 
 int /*<<< orphan*/  SlruScanDirectory (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 

void
SimpleLruTruncate(SlruCtl ctl, int cutoffPage)
{
	SlruShared	shared = ctl->shared;
	int			slotno;

	/*
	 * The cutoff point is the start of the segment containing cutoffPage.
	 */
	cutoffPage -= cutoffPage % SLRU_PAGES_PER_SEGMENT;

	/*
	 * Scan shared memory and remove any pages preceding the cutoff page, to
	 * ensure we won't rewrite them later.  (Since this is normally called in
	 * or just after a checkpoint, any dirty pages should have been flushed
	 * already ... we're just being extra careful here.)
	 */
	LWLockAcquire(shared->ControlLock, LW_EXCLUSIVE);

restart:;

	/*
	 * While we are holding the lock, make an important safety check: the
	 * planned cutoff point must be <= the current endpoint page. Otherwise we
	 * have already wrapped around, and proceeding with the truncation would
	 * risk removing the current segment.
	 */
	if (ctl->PagePrecedes(shared->latest_page_number, cutoffPage))
	{
		LWLockRelease(shared->ControlLock);
		ereport(LOG,
				(errmsg("could not truncate directory \"%s\": apparent wraparound",
						ctl->Dir)));
		return;
	}

	for (slotno = 0; slotno < shared->num_slots; slotno++)
	{
		if (shared->page_status[slotno] == SLRU_PAGE_EMPTY)
			continue;
		if (!ctl->PagePrecedes(shared->page_number[slotno], cutoffPage))
			continue;

		/*
		 * If page is clean, just change state to EMPTY (expected case).
		 */
		if (shared->page_status[slotno] == SLRU_PAGE_VALID &&
			!shared->page_dirty[slotno])
		{
			shared->page_status[slotno] = SLRU_PAGE_EMPTY;
			continue;
		}

		/*
		 * Hmm, we have (or may have) I/O operations acting on the page, so
		 * we've got to wait for them to finish and then start again. This is
		 * the same logic as in SlruSelectLRUPage.  (XXX if page is dirty,
		 * wouldn't it be OK to just discard it without writing it?  For now,
		 * keep the logic the same as it was.)
		 */
		if (shared->page_status[slotno] == SLRU_PAGE_VALID)
			SlruInternalWritePage(ctl, slotno, NULL);
		else
			SimpleLruWaitIO(ctl, slotno);
		goto restart;
	}

	LWLockRelease(shared->ControlLock);

	/* Now we can remove the old segment(s) */
	(void) SlruScanDirectory(ctl, SlruScanDirCbDeleteCutoff, &cutoffPage);
}