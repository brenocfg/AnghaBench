#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xact; } ;
struct TYPE_4__ {TYPE_1__ btpo; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BT_WRITE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ ConditionalLockBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ GetFreeIndexPage (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 int /*<<< orphan*/  _bt_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_log_reuse_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_page_recyclable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_pageinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

Buffer
_bt_getbuf(Relation rel, BlockNumber blkno, int access)
{
	Buffer		buf;

	if (blkno != P_NEW)
	{
		/* Read an existing block of the relation */
		buf = ReadBuffer(rel, blkno);
		LockBuffer(buf, access);
		_bt_checkpage(rel, buf);
	}
	else
	{
		bool		needLock;
		Page		page;

		Assert(access == BT_WRITE);

		/*
		 * First see if the FSM knows of any free pages.
		 *
		 * We can't trust the FSM's report unreservedly; we have to check that
		 * the page is still free.  (For example, an already-free page could
		 * have been re-used between the time the last VACUUM scanned it and
		 * the time the VACUUM made its FSM updates.)
		 *
		 * In fact, it's worse than that: we can't even assume that it's safe
		 * to take a lock on the reported page.  If somebody else has a lock
		 * on it, or even worse our own caller does, we could deadlock.  (The
		 * own-caller scenario is actually not improbable. Consider an index
		 * on a serial or timestamp column.  Nearly all splits will be at the
		 * rightmost page, so it's entirely likely that _bt_split will call us
		 * while holding a lock on the page most recently acquired from FSM. A
		 * VACUUM running concurrently with the previous split could well have
		 * placed that page back in FSM.)
		 *
		 * To get around that, we ask for only a conditional lock on the
		 * reported page.  If we fail, then someone else is using the page,
		 * and we may reasonably assume it's not free.  (If we happen to be
		 * wrong, the worst consequence is the page will be lost to use till
		 * the next VACUUM, which is no big problem.)
		 */
		for (;;)
		{
			blkno = GetFreeIndexPage(rel);
			if (blkno == InvalidBlockNumber)
				break;
			buf = ReadBuffer(rel, blkno);
			if (ConditionalLockBuffer(buf))
			{
				page = BufferGetPage(buf);
				if (_bt_page_recyclable(page))
				{
					/*
					 * If we are generating WAL for Hot Standby then create a
					 * WAL record that will allow us to conflict with queries
					 * running on standby, in case they have snapshots older
					 * than btpo.xact.  This can only apply if the page does
					 * have a valid btpo.xact value, ie not if it's new.  (We
					 * must check that because an all-zero page has no special
					 * space.)
					 */
					if (XLogStandbyInfoActive() && RelationNeedsWAL(rel) &&
						!PageIsNew(page))
					{
						BTPageOpaque opaque = (BTPageOpaque) PageGetSpecialPointer(page);

						_bt_log_reuse_page(rel, blkno, opaque->btpo.xact);
					}

					/* Okay to use page.  Re-initialize and return it */
					_bt_pageinit(page, BufferGetPageSize(buf));
					return buf;
				}
				elog(DEBUG2, "FSM returned nonrecyclable page");
				_bt_relbuf(rel, buf);
			}
			else
			{
				elog(DEBUG2, "FSM returned nonlockable page");
				/* couldn't get lock, so just drop pin */
				ReleaseBuffer(buf);
			}
		}

		/*
		 * Extend the relation by one page.
		 *
		 * We have to use a lock to ensure no one else is extending the rel at
		 * the same time, else we will both try to initialize the same new
		 * page.  We can skip locking for new or temp relations, however,
		 * since no one else could be accessing them.
		 */
		needLock = !RELATION_IS_LOCAL(rel);

		if (needLock)
			LockRelationForExtension(rel, ExclusiveLock);

		buf = ReadBuffer(rel, P_NEW);

		/* Acquire buffer lock on new page */
		LockBuffer(buf, BT_WRITE);

		/*
		 * Release the file-extension lock; it's now OK for someone else to
		 * extend the relation some more.  Note that we cannot release this
		 * lock before we have buffer lock on the new page, or we risk a race
		 * condition against btvacuumscan --- see comments therein.
		 */
		if (needLock)
			UnlockRelationForExtension(rel, ExclusiveLock);

		/* Initialize the new page before returning it */
		page = BufferGetPage(buf);
		Assert(PageIsNew(page));
		_bt_pageinit(page, BufferGetPageSize(buf));
	}

	/* ref count and lock type are correct */
	return buf;
}