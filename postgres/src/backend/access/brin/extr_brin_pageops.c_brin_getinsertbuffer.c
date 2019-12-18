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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BRIN_IS_REGULAR_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRIN_elog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BrinMaxItemSize ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  FreeSpaceMapVacuumRange (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetPageWithFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RecordAndGetPageWithFreeSpace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetTargetBlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationSetTargetBlock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_page_get_freespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_initialize_empty_new_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Buffer
brin_getinsertbuffer(Relation irel, Buffer oldbuf, Size itemsz,
					 bool *extended)
{
	BlockNumber oldblk;
	BlockNumber newblk;
	Page		page;
	Size		freespace;

	/* callers must have checked */
	Assert(itemsz <= BrinMaxItemSize);

	if (BufferIsValid(oldbuf))
		oldblk = BufferGetBlockNumber(oldbuf);
	else
		oldblk = InvalidBlockNumber;

	/* Choose initial target page, re-using existing target if known */
	newblk = RelationGetTargetBlock(irel);
	if (newblk == InvalidBlockNumber)
		newblk = GetPageWithFreeSpace(irel, itemsz);

	/*
	 * Loop until we find a page with sufficient free space.  By the time we
	 * return to caller out of this loop, both buffers are valid and locked;
	 * if we have to restart here, neither page is locked and newblk isn't
	 * pinned (if it's even valid).
	 */
	for (;;)
	{
		Buffer		buf;
		bool		extensionLockHeld = false;

		CHECK_FOR_INTERRUPTS();

		*extended = false;

		if (newblk == InvalidBlockNumber)
		{
			/*
			 * There's not enough free space in any existing index page,
			 * according to the FSM: extend the relation to obtain a shiny new
			 * page.
			 */
			if (!RELATION_IS_LOCAL(irel))
			{
				LockRelationForExtension(irel, ExclusiveLock);
				extensionLockHeld = true;
			}
			buf = ReadBuffer(irel, P_NEW);
			newblk = BufferGetBlockNumber(buf);
			*extended = true;

			BRIN_elog((DEBUG2, "brin_getinsertbuffer: extending to page %u",
					   BufferGetBlockNumber(buf)));
		}
		else if (newblk == oldblk)
		{
			/*
			 * There's an odd corner-case here where the FSM is out-of-date,
			 * and gave us the old page.
			 */
			buf = oldbuf;
		}
		else
		{
			buf = ReadBuffer(irel, newblk);
		}

		/*
		 * We lock the old buffer first, if it's earlier than the new one; but
		 * then we need to check that it hasn't been turned into a revmap page
		 * concurrently.  If we detect that that happened, give up and tell
		 * caller to start over.
		 */
		if (BufferIsValid(oldbuf) && oldblk < newblk)
		{
			LockBuffer(oldbuf, BUFFER_LOCK_EXCLUSIVE);
			if (!BRIN_IS_REGULAR_PAGE(BufferGetPage(oldbuf)))
			{
				LockBuffer(oldbuf, BUFFER_LOCK_UNLOCK);

				/*
				 * It is possible that the new page was obtained from
				 * extending the relation.  In that case, we must be sure to
				 * record it in the FSM before leaving, because otherwise the
				 * space would be lost forever.  However, we cannot let an
				 * uninitialized page get in the FSM, so we need to initialize
				 * it first.
				 */
				if (*extended)
					brin_initialize_empty_new_buffer(irel, buf);

				if (extensionLockHeld)
					UnlockRelationForExtension(irel, ExclusiveLock);

				ReleaseBuffer(buf);

				if (*extended)
				{
					FreeSpaceMapVacuumRange(irel, newblk, newblk + 1);
					/* shouldn't matter, but don't confuse caller */
					*extended = false;
				}

				return InvalidBuffer;
			}
		}

		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

		if (extensionLockHeld)
			UnlockRelationForExtension(irel, ExclusiveLock);

		page = BufferGetPage(buf);

		/*
		 * We have a new buffer to insert into.  Check that the new page has
		 * enough free space, and return it if it does; otherwise start over.
		 * (br_page_get_freespace also checks that the FSM didn't hand us a
		 * page that has since been repurposed for the revmap.)
		 */
		freespace = *extended ?
			BrinMaxItemSize : br_page_get_freespace(page);
		if (freespace >= itemsz)
		{
			RelationSetTargetBlock(irel, newblk);

			/*
			 * Lock the old buffer if not locked already.  Note that in this
			 * case we know for sure it's a regular page: it's later than the
			 * new page we just got, which is not a revmap page, and revmap
			 * pages are always consecutive.
			 */
			if (BufferIsValid(oldbuf) && oldblk > newblk)
			{
				LockBuffer(oldbuf, BUFFER_LOCK_EXCLUSIVE);
				Assert(BRIN_IS_REGULAR_PAGE(BufferGetPage(oldbuf)));
			}

			return buf;
		}

		/* This page is no good. */

		/*
		 * If an entirely new page does not contain enough free space for the
		 * new item, then surely that item is oversized.  Complain loudly; but
		 * first make sure we initialize the page and record it as free, for
		 * next time.
		 */
		if (*extended)
		{
			brin_initialize_empty_new_buffer(irel, buf);
			/* since this should not happen, skip FreeSpaceMapVacuum */

			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("index row size %zu exceeds maximum %zu for index \"%s\"",
							itemsz, freespace, RelationGetRelationName(irel))));
			return InvalidBuffer;	/* keep compiler quiet */
		}

		if (newblk != oldblk)
			UnlockReleaseBuffer(buf);
		if (BufferIsValid(oldbuf) && oldblk <= newblk)
			LockBuffer(oldbuf, BUFFER_LOCK_UNLOCK);

		/*
		 * Update the FSM with the new, presumably smaller, freespace value
		 * for this page, then search for a new target page.
		 */
		newblk = RecordAndGetPageWithFreeSpace(irel, newblk, freespace, itemsz);
	}
}