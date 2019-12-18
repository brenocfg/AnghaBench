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
typedef  int /*<<< orphan*/  TransactionId ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionalLockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_DEFAULT_FILLFACTOR ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ IsCatalogRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Max (scalar_t__,int) ; 
 scalar_t__ PageGetHeapFreeSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsFull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIsPrunable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecentGlobalDataXmin ; 
 int /*<<< orphan*/  RecentGlobalXmin ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ RelationGetTargetPageFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationIsAccessibleInLogicalDecoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdLimitedForOldSnapshots (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_page_prune (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
heap_page_prune_opt(Relation relation, Buffer buffer)
{
	Page		page = BufferGetPage(buffer);
	Size		minfree;
	TransactionId OldestXmin;

	/*
	 * We can't write WAL in recovery mode, so there's no point trying to
	 * clean the page. The master will likely issue a cleaning WAL record soon
	 * anyway, so this is no particular loss.
	 */
	if (RecoveryInProgress())
		return;

	/*
	 * Use the appropriate xmin horizon for this relation. If it's a proper
	 * catalog relation or a user defined, additional, catalog relation, we
	 * need to use the horizon that includes slots, otherwise the data-only
	 * horizon can be used. Note that the toast relation of user defined
	 * relations are *not* considered catalog relations.
	 *
	 * It is OK to apply the old snapshot limit before acquiring the cleanup
	 * lock because the worst that can happen is that we are not quite as
	 * aggressive about the cleanup (by however many transaction IDs are
	 * consumed between this point and acquiring the lock).  This allows us to
	 * save significant overhead in the case where the page is found not to be
	 * prunable.
	 */
	if (IsCatalogRelation(relation) ||
		RelationIsAccessibleInLogicalDecoding(relation))
		OldestXmin = RecentGlobalXmin;
	else
		OldestXmin =
			TransactionIdLimitedForOldSnapshots(RecentGlobalDataXmin,
												relation);

	Assert(TransactionIdIsValid(OldestXmin));

	/*
	 * Let's see if we really need pruning.
	 *
	 * Forget it if page is not hinted to contain something prunable that's
	 * older than OldestXmin.
	 */
	if (!PageIsPrunable(page, OldestXmin))
		return;

	/*
	 * We prune when a previous UPDATE failed to find enough space on the page
	 * for a new tuple version, or when free space falls below the relation's
	 * fill-factor target (but not less than 10%).
	 *
	 * Checking free space here is questionable since we aren't holding any
	 * lock on the buffer; in the worst case we could get a bogus answer. It's
	 * unlikely to be *seriously* wrong, though, since reading either pd_lower
	 * or pd_upper is probably atomic.  Avoiding taking a lock seems more
	 * important than sometimes getting a wrong answer in what is after all
	 * just a heuristic estimate.
	 */
	minfree = RelationGetTargetPageFreeSpace(relation,
											 HEAP_DEFAULT_FILLFACTOR);
	minfree = Max(minfree, BLCKSZ / 10);

	if (PageIsFull(page) || PageGetHeapFreeSpace(page) < minfree)
	{
		/* OK, try to get exclusive buffer lock */
		if (!ConditionalLockBufferForCleanup(buffer))
			return;

		/*
		 * Now that we have buffer lock, get accurate information about the
		 * page's free space, and recheck the heuristic about whether to
		 * prune. (We needn't recheck PageIsPrunable, since no one else could
		 * have pruned while we hold pin.)
		 */
		if (PageIsFull(page) || PageGetHeapFreeSpace(page) < minfree)
		{
			TransactionId ignore = InvalidTransactionId;	/* return value not
															 * needed */

			/* OK to prune */
			(void) heap_page_prune(relation, buffer, OldestXmin, true, &ignore);
		}

		/* And release buffer lock */
		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
	}
}