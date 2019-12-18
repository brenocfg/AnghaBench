#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lastFilledBlock; TYPE_1__* stats; TYPE_2__* info; } ;
typedef  TYPE_3__ spgBulkDeleteState ;
struct TYPE_8__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
struct TYPE_7__ {int /*<<< orphan*/  pages_deleted; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ PageIsEmpty (scalar_t__) ; 
 scalar_t__ PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordFreeIndexPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistBlockIsRoot (int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistPageIsLeaf (scalar_t__) ; 
 int /*<<< orphan*/  SpGistSetLastUsedPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vacuumLeafPage (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vacuumLeafRoot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vacuumRedirectAndPlaceholder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

__attribute__((used)) static void
spgvacuumpage(spgBulkDeleteState *bds, BlockNumber blkno)
{
	Relation	index = bds->info->index;
	Buffer		buffer;
	Page		page;

	/* call vacuum_delay_point while not holding any buffer lock */
	vacuum_delay_point();

	buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
								RBM_NORMAL, bds->info->strategy);
	LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);
	page = (Page) BufferGetPage(buffer);

	if (PageIsNew(page))
	{
		/*
		 * We found an all-zero page, which could happen if the database
		 * crashed just after extending the file.  Recycle it.
		 */
	}
	else if (PageIsEmpty(page))
	{
		/* nothing to do */
	}
	else if (SpGistPageIsLeaf(page))
	{
		if (SpGistBlockIsRoot(blkno))
		{
			vacuumLeafRoot(bds, index, buffer);
			/* no need for vacuumRedirectAndPlaceholder */
		}
		else
		{
			vacuumLeafPage(bds, index, buffer, false);
			vacuumRedirectAndPlaceholder(index, buffer);
		}
	}
	else
	{
		/* inner page */
		vacuumRedirectAndPlaceholder(index, buffer);
	}

	/*
	 * The root pages must never be deleted, nor marked as available in FSM,
	 * because we don't want them ever returned by a search for a place to put
	 * a new tuple.  Otherwise, check for empty page, and make sure the FSM
	 * knows about it.
	 */
	if (!SpGistBlockIsRoot(blkno))
	{
		if (PageIsNew(page) || PageIsEmpty(page))
		{
			RecordFreeIndexPage(index, blkno);
			bds->stats->pages_deleted++;
		}
		else
		{
			SpGistSetLastUsedPage(index, buffer);
			bds->lastFilledBlock = blkno;
		}
	}

	UnlockReleaseBuffer(buffer);
}