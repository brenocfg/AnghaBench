#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ ConditionalLockBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 int /*<<< orphan*/  GIST_UNLOCK ; 
 scalar_t__ GetFreeIndexPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistPageGetDeleteXid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_NEW ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 scalar_t__ gistPageRecyclable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistXLogPageReuse (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistcheckpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Buffer
gistNewBuffer(Relation r)
{
	Buffer		buffer;
	bool		needLock;

	/* First, try to get a page from FSM */
	for (;;)
	{
		BlockNumber blkno = GetFreeIndexPage(r);

		if (blkno == InvalidBlockNumber)
			break;				/* nothing left in FSM */

		buffer = ReadBuffer(r, blkno);

		/*
		 * We have to guard against the possibility that someone else already
		 * recycled this page; the buffer may be locked if so.
		 */
		if (ConditionalLockBuffer(buffer))
		{
			Page		page = BufferGetPage(buffer);

			/*
			 * If the page was never initialized, it's OK to use.
			 */
			if (PageIsNew(page))
				return buffer;

			gistcheckpage(r, buffer);

			/*
			 * Otherwise, recycle it if deleted, and too old to have any
			 * processes interested in it.
			 */
			if (gistPageRecyclable(page))
			{
				/*
				 * If we are generating WAL for Hot Standby then create a WAL
				 * record that will allow us to conflict with queries running
				 * on standby, in case they have snapshots older than the
				 * page's deleteXid.
				 */
				if (XLogStandbyInfoActive() && RelationNeedsWAL(r))
					gistXLogPageReuse(r, blkno, GistPageGetDeleteXid(page));

				return buffer;
			}

			LockBuffer(buffer, GIST_UNLOCK);
		}

		/* Can't use it, so release buffer and try again */
		ReleaseBuffer(buffer);
	}

	/* Must extend the file */
	needLock = !RELATION_IS_LOCAL(r);

	if (needLock)
		LockRelationForExtension(r, ExclusiveLock);

	buffer = ReadBuffer(r, P_NEW);
	LockBuffer(buffer, GIST_EXCLUSIVE);

	if (needLock)
		UnlockRelationForExtension(r, ExclusiveLock);

	return buffer;
}