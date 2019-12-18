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
struct TYPE_7__ {char* Dir; TYPE_1__* shared; } ;
struct TYPE_6__ {int num_slots; int* page_number; scalar_t__* page_status; int /*<<< orphan*/  ControlLock; int /*<<< orphan*/ * page_dirty; } ;
typedef  TYPE_1__* SlruShared ;
typedef  TYPE_2__* SlruCtl ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXPGPATH ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 scalar_t__ SLRU_PAGE_EMPTY ; 
 scalar_t__ SLRU_PAGE_VALID ; 
 int /*<<< orphan*/  SimpleLruWaitIO (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SlruInternalWritePage (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
SlruDeleteSegment(SlruCtl ctl, int segno)
{
	SlruShared	shared = ctl->shared;
	int			slotno;
	char		path[MAXPGPATH];
	bool		did_write;

	/* Clean out any possibly existing references to the segment. */
	LWLockAcquire(shared->ControlLock, LW_EXCLUSIVE);
restart:
	did_write = false;
	for (slotno = 0; slotno < shared->num_slots; slotno++)
	{
		int			pagesegno = shared->page_number[slotno] / SLRU_PAGES_PER_SEGMENT;

		if (shared->page_status[slotno] == SLRU_PAGE_EMPTY)
			continue;

		/* not the segment we're looking for */
		if (pagesegno != segno)
			continue;

		/* If page is clean, just change state to EMPTY (expected case). */
		if (shared->page_status[slotno] == SLRU_PAGE_VALID &&
			!shared->page_dirty[slotno])
		{
			shared->page_status[slotno] = SLRU_PAGE_EMPTY;
			continue;
		}

		/* Same logic as SimpleLruTruncate() */
		if (shared->page_status[slotno] == SLRU_PAGE_VALID)
			SlruInternalWritePage(ctl, slotno, NULL);
		else
			SimpleLruWaitIO(ctl, slotno);

		did_write = true;
	}

	/*
	 * Be extra careful and re-check. The IO functions release the control
	 * lock, so new pages could have been read in.
	 */
	if (did_write)
		goto restart;

	snprintf(path, MAXPGPATH, "%s/%04X", ctl->Dir, segno);
	ereport(DEBUG2,
			(errmsg("removing file \"%s\"", path)));
	unlink(path);

	LWLockRelease(shared->ControlLock);
}