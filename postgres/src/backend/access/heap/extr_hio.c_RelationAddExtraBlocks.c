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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  BulkInsertState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeSpaceMapVacuumRange (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  P_NEW ; 
 int /*<<< orphan*/  PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_ZERO_AND_LOCK ; 
 int /*<<< orphan*/  ReadBufferBI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordPageWithFreeSpace (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int RelationExtensionLockWaiterCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RelationAddExtraBlocks(Relation relation, BulkInsertState bistate)
{
	BlockNumber blockNum,
				firstBlock = InvalidBlockNumber;
	int			extraBlocks;
	int			lockWaiters;

	/* Use the length of the lock wait queue to judge how much to extend. */
	lockWaiters = RelationExtensionLockWaiterCount(relation);
	if (lockWaiters <= 0)
		return;

	/*
	 * It might seem like multiplying the number of lock waiters by as much as
	 * 20 is too aggressive, but benchmarking revealed that smaller numbers
	 * were insufficient.  512 is just an arbitrary cap to prevent
	 * pathological results.
	 */
	extraBlocks = Min(512, lockWaiters * 20);

	do
	{
		Buffer		buffer;
		Page		page;
		Size		freespace;

		/*
		 * Extend by one page.  This should generally match the main-line
		 * extension code in RelationGetBufferForTuple, except that we hold
		 * the relation extension lock throughout, and we don't immediately
		 * initialize the page (see below).
		 */
		buffer = ReadBufferBI(relation, P_NEW, RBM_ZERO_AND_LOCK, bistate);
		page = BufferGetPage(buffer);

		if (!PageIsNew(page))
			elog(ERROR, "page %u of relation \"%s\" should be empty but is not",
				 BufferGetBlockNumber(buffer),
				 RelationGetRelationName(relation));

		/*
		 * Add the page to the FSM without initializing. If we were to
		 * initialize here, the page would potentially get flushed out to disk
		 * before we add any useful content. There's no guarantee that that'd
		 * happen before a potential crash, so we need to deal with
		 * uninitialized pages anyway, thus avoid the potential for
		 * unnecessary writes.
		 */

		/* we'll need this info below */
		blockNum = BufferGetBlockNumber(buffer);
		freespace = BufferGetPageSize(buffer) - SizeOfPageHeaderData;

		UnlockReleaseBuffer(buffer);

		/* Remember first block number thus added. */
		if (firstBlock == InvalidBlockNumber)
			firstBlock = blockNum;

		/*
		 * Immediately update the bottom level of the FSM.  This has a good
		 * chance of making this page visible to other concurrently inserting
		 * backends, and we want that to happen without delay.
		 */
		RecordPageWithFreeSpace(relation, blockNum, freespace);
	}
	while (--extraBlocks > 0);

	/*
	 * Updating the upper levels of the free space map is too expensive to do
	 * for every block, but it's worth doing once at the end to make sure that
	 * subsequent insertion activity sees all of those nifty free pages we
	 * just inserted.
	 */
	FreeSpaceMapVacuumRange(relation, firstBlock, blockNum + 1);
}