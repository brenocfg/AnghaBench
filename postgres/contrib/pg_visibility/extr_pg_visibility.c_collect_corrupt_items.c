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
struct TYPE_7__ {int next; int count; int /*<<< orphan*/  tids; } ;
typedef  TYPE_1__ corrupt_items ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int /*<<< orphan*/  t_self; scalar_t__ t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_len; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ HeapTupleHeader ;
typedef  TYPE_2__ HeapTupleData ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BAS_BULKREAD ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GetAccessStrategy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetOldestXmin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsRedirected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PROCARRAY_FLAGS_VACUUM ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 scalar_t__ ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 scalar_t__ VM_ALL_FROZEN (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 scalar_t__ VM_ALL_VISIBLE (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  check_relation_relkind (int /*<<< orphan*/ ) ; 
 scalar_t__ heap_tuple_needs_eventual_freeze (scalar_t__) ; 
 int /*<<< orphan*/  palloc (int) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  record_corrupt_item (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuple_all_visible (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static corrupt_items *
collect_corrupt_items(Oid relid, bool all_visible, bool all_frozen)
{
	Relation	rel;
	BlockNumber nblocks;
	corrupt_items *items;
	BlockNumber blkno;
	Buffer		vmbuffer = InvalidBuffer;
	BufferAccessStrategy bstrategy = GetAccessStrategy(BAS_BULKREAD);
	TransactionId OldestXmin = InvalidTransactionId;

	if (all_visible)
	{
		/* Don't pass rel; that will fail in recovery. */
		OldestXmin = GetOldestXmin(NULL, PROCARRAY_FLAGS_VACUUM);
	}

	rel = relation_open(relid, AccessShareLock);

	/* Only some relkinds have a visibility map */
	check_relation_relkind(rel);

	nblocks = RelationGetNumberOfBlocks(rel);

	/*
	 * Guess an initial array size. We don't expect many corrupted tuples, so
	 * start with a small array.  This function uses the "next" field to track
	 * the next offset where we can store an item (which is the same thing as
	 * the number of items found so far) and the "count" field to track the
	 * number of entries allocated.  We'll repurpose these fields before
	 * returning.
	 */
	items = palloc0(sizeof(corrupt_items));
	items->next = 0;
	items->count = 64;
	items->tids = palloc(items->count * sizeof(ItemPointerData));

	/* Loop over every block in the relation. */
	for (blkno = 0; blkno < nblocks; ++blkno)
	{
		bool		check_frozen = false;
		bool		check_visible = false;
		Buffer		buffer;
		Page		page;
		OffsetNumber offnum,
					maxoff;

		/* Make sure we are interruptible. */
		CHECK_FOR_INTERRUPTS();

		/* Use the visibility map to decide whether to check this page. */
		if (all_frozen && VM_ALL_FROZEN(rel, blkno, &vmbuffer))
			check_frozen = true;
		if (all_visible && VM_ALL_VISIBLE(rel, blkno, &vmbuffer))
			check_visible = true;
		if (!check_visible && !check_frozen)
			continue;

		/* Read and lock the page. */
		buffer = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL,
									bstrategy);
		LockBuffer(buffer, BUFFER_LOCK_SHARE);

		page = BufferGetPage(buffer);
		maxoff = PageGetMaxOffsetNumber(page);

		/*
		 * The visibility map bits might have changed while we were acquiring
		 * the page lock.  Recheck to avoid returning spurious results.
		 */
		if (check_frozen && !VM_ALL_FROZEN(rel, blkno, &vmbuffer))
			check_frozen = false;
		if (check_visible && !VM_ALL_VISIBLE(rel, blkno, &vmbuffer))
			check_visible = false;
		if (!check_visible && !check_frozen)
		{
			UnlockReleaseBuffer(buffer);
			continue;
		}

		/* Iterate over each tuple on the page. */
		for (offnum = FirstOffsetNumber;
			 offnum <= maxoff;
			 offnum = OffsetNumberNext(offnum))
		{
			HeapTupleData tuple;
			ItemId		itemid;

			itemid = PageGetItemId(page, offnum);

			/* Unused or redirect line pointers are of no interest. */
			if (!ItemIdIsUsed(itemid) || ItemIdIsRedirected(itemid))
				continue;

			/* Dead line pointers are neither all-visible nor frozen. */
			if (ItemIdIsDead(itemid))
			{
				ItemPointerSet(&(tuple.t_self), blkno, offnum);
				record_corrupt_item(items, &tuple.t_self);
				continue;
			}

			/* Initialize a HeapTupleData structure for checks below. */
			ItemPointerSet(&(tuple.t_self), blkno, offnum);
			tuple.t_data = (HeapTupleHeader) PageGetItem(page, itemid);
			tuple.t_len = ItemIdGetLength(itemid);
			tuple.t_tableOid = relid;

			/*
			 * If we're checking whether the page is all-visible, we expect
			 * the tuple to be all-visible.
			 */
			if (check_visible &&
				!tuple_all_visible(&tuple, OldestXmin, buffer))
			{
				TransactionId RecomputedOldestXmin;

				/*
				 * Time has passed since we computed OldestXmin, so it's
				 * possible that this tuple is all-visible in reality even
				 * though it doesn't appear so based on our
				 * previously-computed value.  Let's compute a new value so we
				 * can be certain whether there is a problem.
				 *
				 * From a concurrency point of view, it sort of sucks to
				 * retake ProcArrayLock here while we're holding the buffer
				 * exclusively locked, but it should be safe against
				 * deadlocks, because surely GetOldestXmin() should never take
				 * a buffer lock. And this shouldn't happen often, so it's
				 * worth being careful so as to avoid false positives.
				 */
				RecomputedOldestXmin = GetOldestXmin(NULL, PROCARRAY_FLAGS_VACUUM);

				if (!TransactionIdPrecedes(OldestXmin, RecomputedOldestXmin))
					record_corrupt_item(items, &tuple.t_self);
				else
				{
					OldestXmin = RecomputedOldestXmin;
					if (!tuple_all_visible(&tuple, OldestXmin, buffer))
						record_corrupt_item(items, &tuple.t_self);
				}
			}

			/*
			 * If we're checking whether the page is all-frozen, we expect the
			 * tuple to be in a state where it will never need freezing.
			 */
			if (check_frozen)
			{
				if (heap_tuple_needs_eventual_freeze(tuple.t_data))
					record_corrupt_item(items, &tuple.t_self);
			}
		}

		UnlockReleaseBuffer(buffer);
	}

	/* Clean up. */
	if (vmbuffer != InvalidBuffer)
		ReleaseBuffer(vmbuffer);
	relation_close(rel, AccessShareLock);

	/*
	 * Before returning, repurpose the fields to match caller's expectations.
	 * next is now the next item that should be read (rather than written) and
	 * count is now the number of items we wrote (rather than the number we
	 * allocated).
	 */
	items->count = items->next;
	items->next = 0;

	return items;
}