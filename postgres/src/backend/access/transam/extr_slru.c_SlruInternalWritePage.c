#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* shared; } ;
struct TYPE_13__ {int num_files; int /*<<< orphan*/ * fd; } ;
struct TYPE_12__ {int* page_number; scalar_t__* page_status; int* page_dirty; TYPE_1__* buffer_locks; int /*<<< orphan*/ * ControlLock; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__* SlruShared ;
typedef  TYPE_3__* SlruFlush ;
typedef  TYPE_4__* SlruCtl ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CloseTransientFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ SLRU_PAGE_VALID ; 
 scalar_t__ SLRU_PAGE_WRITE_IN_PROGRESS ; 
 int /*<<< orphan*/  SimpleLruWaitIO (TYPE_4__*,int) ; 
 int SlruPhysicalWritePage (TYPE_4__*,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  SlruReportIOError (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SlruInternalWritePage(SlruCtl ctl, int slotno, SlruFlush fdata)
{
	SlruShared	shared = ctl->shared;
	int			pageno = shared->page_number[slotno];
	bool		ok;

	/* If a write is in progress, wait for it to finish */
	while (shared->page_status[slotno] == SLRU_PAGE_WRITE_IN_PROGRESS &&
		   shared->page_number[slotno] == pageno)
	{
		SimpleLruWaitIO(ctl, slotno);
	}

	/*
	 * Do nothing if page is not dirty, or if buffer no longer contains the
	 * same page we were called for.
	 */
	if (!shared->page_dirty[slotno] ||
		shared->page_status[slotno] != SLRU_PAGE_VALID ||
		shared->page_number[slotno] != pageno)
		return;

	/*
	 * Mark the slot write-busy, and clear the dirtybit.  After this point, a
	 * transaction status update on this page will mark it dirty again.
	 */
	shared->page_status[slotno] = SLRU_PAGE_WRITE_IN_PROGRESS;
	shared->page_dirty[slotno] = false;

	/* Acquire per-buffer lock (cannot deadlock, see notes at top) */
	LWLockAcquire(&shared->buffer_locks[slotno].lock, LW_EXCLUSIVE);

	/* Release control lock while doing I/O */
	LWLockRelease(shared->ControlLock);

	/* Do the write */
	ok = SlruPhysicalWritePage(ctl, pageno, slotno, fdata);

	/* If we failed, and we're in a flush, better close the files */
	if (!ok && fdata)
	{
		int			i;

		for (i = 0; i < fdata->num_files; i++)
			CloseTransientFile(fdata->fd[i]);
	}

	/* Re-acquire control lock and update page state */
	LWLockAcquire(shared->ControlLock, LW_EXCLUSIVE);

	Assert(shared->page_number[slotno] == pageno &&
		   shared->page_status[slotno] == SLRU_PAGE_WRITE_IN_PROGRESS);

	/* If we failed to write, mark the page dirty again */
	if (!ok)
		shared->page_dirty[slotno] = true;

	shared->page_status[slotno] = SLRU_PAGE_VALID;

	LWLockRelease(&shared->buffer_locks[slotno].lock);

	/* Now it's okay to ereport if we failed */
	if (!ok)
		SlruReportIOError(ctl, pageno, InvalidTransactionId);
}