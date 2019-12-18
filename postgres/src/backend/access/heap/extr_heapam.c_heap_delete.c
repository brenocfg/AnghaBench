#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;

/* Type definitions */
struct TYPE_51__ {int /*<<< orphan*/  t_hoff; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_infomask2; } ;
typedef  TYPE_3__ xl_heap_header ;
struct TYPE_52__ {int /*<<< orphan*/  flags; scalar_t__ xmax; int /*<<< orphan*/  offnum; int /*<<< orphan*/  infobits_set; } ;
typedef  TYPE_4__ xl_heap_delete ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_57__ {int t_len; TYPE_1__* t_data; } ;
struct TYPE_56__ {int /*<<< orphan*/  t_self; TYPE_7__* t_data; int /*<<< orphan*/  t_len; int /*<<< orphan*/  t_tableOid; } ;
struct TYPE_55__ {int t_infomask; int t_infomask2; int /*<<< orphan*/  t_ctid; } ;
struct TYPE_54__ {TYPE_2__* rd_rel; } ;
struct TYPE_53__ {int /*<<< orphan*/  cmax; int /*<<< orphan*/  xmax; int /*<<< orphan*/  ctid; } ;
struct TYPE_50__ {scalar_t__ relreplident; scalar_t__ relkind; } ;
struct TYPE_49__ {int /*<<< orphan*/  t_hoff; int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_infomask2; } ;
typedef  scalar_t__ TM_Result ;
typedef  TYPE_5__ TM_FailureData ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_6__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_7__* HeapTupleHeader ;
typedef  TYPE_8__ HeapTupleData ;
typedef  TYPE_9__* HeapTuple ;
typedef  int /*<<< orphan*/  CommandId ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CacheInvalidateHeapTuple (TYPE_6__*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (TYPE_6__*,TYPE_8__*,scalar_t__) ; 
 scalar_t__ DoesMultiXactIdConflict (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_STATE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_9__* ExtractReplicaIdentity (TYPE_6__*,TYPE_8__*,int,int*) ; 
 scalar_t__ GetCurrentTransactionId () ; 
 int HEAP_KEYS_UPDATED ; 
 int HEAP_MOVED ; 
 int HEAP_XMAX_BITS ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 scalar_t__ HeapTupleHasExternal (TYPE_8__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderAdjustCmax (TYPE_7__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  HeapTupleHeaderClearHotUpdated (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetCmax (TYPE_7__*) ; 
 scalar_t__ HeapTupleHeaderGetRawXmax (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_7__*) ; 
 scalar_t__ HeapTupleHeaderIndicatesMovedPartitions (TYPE_7__*) ; 
 scalar_t__ HeapTupleHeaderIsOnlyLocked (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetCmax (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetMovedPartitions (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_7__*,scalar_t__) ; 
 scalar_t__ HeapTupleSatisfiesUpdate (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapTupleSatisfiesVisibility (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  InvalidCommandId ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockTupleExclusive ; 
 int /*<<< orphan*/  LockWaitBlock ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactIdSetOldestMember () ; 
 int /*<<< orphan*/  MultiXactIdWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiXactStatusUpdate ; 
 int /*<<< orphan*/  PageClearAllVisible (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsAllVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetPrunable (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ REPLICA_IDENTITY_FULL ; 
 int /*<<< orphan*/  RM_HEAP_ID ; 
 scalar_t__ ReadBuffer (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_6__*) ; 
 scalar_t__ RelationIsAccessibleInLogicalDecoding (TYPE_6__*) ; 
 scalar_t__ RelationNeedsWAL (TYPE_6__*) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int SizeOfHeapDelete ; 
 int SizeOfHeapHeader ; 
 int SizeofHeapTupleHeader ; 
 scalar_t__ TM_BeingModified ; 
 scalar_t__ TM_Deleted ; 
 scalar_t__ TM_Invisible ; 
 scalar_t__ TM_Ok ; 
 scalar_t__ TM_SelfModified ; 
 scalar_t__ TM_Updated ; 
 int /*<<< orphan*/  TransactionIdEquals (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdIsCurrentTransactionId (scalar_t__) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  UnlockTupleTuplock (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateXmaxHintBits (TYPE_7__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VISIBILITYMAP_VALID_BITS ; 
 int /*<<< orphan*/  XLH_DELETE_ALL_VISIBLE_CLEARED ; 
 int /*<<< orphan*/  XLH_DELETE_CONTAINS_OLD_KEY ; 
 int /*<<< orphan*/  XLH_DELETE_CONTAINS_OLD_TUPLE ; 
 int /*<<< orphan*/  XLH_DELETE_IS_PARTITION_MOVE ; 
 int /*<<< orphan*/  XLOG_HEAP_DELETE ; 
 int /*<<< orphan*/  XLOG_INCLUDE_ORIGIN ; 
 int /*<<< orphan*/  XLTW_Delete ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  XLogSetRecordFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactLockTableWait (scalar_t__,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_infobits (int,int) ; 
 int /*<<< orphan*/  compute_new_xmax_infomask (scalar_t__,int,int,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_acquire_tuplock (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_9__*) ; 
 int /*<<< orphan*/  heap_toast_delete (TYPE_6__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  log_heap_new_cid (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  pgstat_count_heap_delete (TYPE_6__*) ; 
 int /*<<< orphan*/  visibilitymap_clear (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visibilitymap_pin (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ xmax_infomask_changed (int,int) ; 

TM_Result
heap_delete(Relation relation, ItemPointer tid,
			CommandId cid, Snapshot crosscheck, bool wait,
			TM_FailureData *tmfd, bool changingPart)
{
	TM_Result	result;
	TransactionId xid = GetCurrentTransactionId();
	ItemId		lp;
	HeapTupleData tp;
	Page		page;
	BlockNumber block;
	Buffer		buffer;
	Buffer		vmbuffer = InvalidBuffer;
	TransactionId new_xmax;
	uint16		new_infomask,
				new_infomask2;
	bool		have_tuple_lock = false;
	bool		iscombo;
	bool		all_visible_cleared = false;
	HeapTuple	old_key_tuple = NULL;	/* replica identity of the tuple */
	bool		old_key_copied = false;

	Assert(ItemPointerIsValid(tid));

	/*
	 * Forbid this during a parallel operation, lest it allocate a combocid.
	 * Other workers might need that combocid for visibility checks, and we
	 * have no provision for broadcasting it to them.
	 */
	if (IsInParallelMode())
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_STATE),
				 errmsg("cannot delete tuples during a parallel operation")));

	block = ItemPointerGetBlockNumber(tid);
	buffer = ReadBuffer(relation, block);
	page = BufferGetPage(buffer);

	/*
	 * Before locking the buffer, pin the visibility map page if it appears to
	 * be necessary.  Since we haven't got the lock yet, someone else might be
	 * in the middle of changing this, so we'll need to recheck after we have
	 * the lock.
	 */
	if (PageIsAllVisible(page))
		visibilitymap_pin(relation, block, &vmbuffer);

	LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);

	/*
	 * If we didn't pin the visibility map page and the page has become all
	 * visible while we were busy locking the buffer, we'll have to unlock and
	 * re-lock, to avoid holding the buffer lock across an I/O.  That's a bit
	 * unfortunate, but hopefully shouldn't happen often.
	 */
	if (vmbuffer == InvalidBuffer && PageIsAllVisible(page))
	{
		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
		visibilitymap_pin(relation, block, &vmbuffer);
		LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);
	}

	lp = PageGetItemId(page, ItemPointerGetOffsetNumber(tid));
	Assert(ItemIdIsNormal(lp));

	tp.t_tableOid = RelationGetRelid(relation);
	tp.t_data = (HeapTupleHeader) PageGetItem(page, lp);
	tp.t_len = ItemIdGetLength(lp);
	tp.t_self = *tid;

l1:
	result = HeapTupleSatisfiesUpdate(&tp, cid, buffer);

	if (result == TM_Invisible)
	{
		UnlockReleaseBuffer(buffer);
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("attempted to delete invisible tuple")));
	}
	else if (result == TM_BeingModified && wait)
	{
		TransactionId xwait;
		uint16		infomask;

		/* must copy state data before unlocking buffer */
		xwait = HeapTupleHeaderGetRawXmax(tp.t_data);
		infomask = tp.t_data->t_infomask;

		/*
		 * Sleep until concurrent transaction ends -- except when there's a
		 * single locker and it's our own transaction.  Note we don't care
		 * which lock mode the locker has, because we need the strongest one.
		 *
		 * Before sleeping, we need to acquire tuple lock to establish our
		 * priority for the tuple (see heap_lock_tuple).  LockTuple will
		 * release us when we are next-in-line for the tuple.
		 *
		 * If we are forced to "start over" below, we keep the tuple lock;
		 * this arranges that we stay at the head of the line while rechecking
		 * tuple state.
		 */
		if (infomask & HEAP_XMAX_IS_MULTI)
		{
			bool		current_is_member = false;

			if (DoesMultiXactIdConflict((MultiXactId) xwait, infomask,
										LockTupleExclusive, &current_is_member))
			{
				LockBuffer(buffer, BUFFER_LOCK_UNLOCK);

				/*
				 * Acquire the lock, if necessary (but skip it when we're
				 * requesting a lock and already have one; avoids deadlock).
				 */
				if (!current_is_member)
					heap_acquire_tuplock(relation, &(tp.t_self), LockTupleExclusive,
										 LockWaitBlock, &have_tuple_lock);

				/* wait for multixact */
				MultiXactIdWait((MultiXactId) xwait, MultiXactStatusUpdate, infomask,
								relation, &(tp.t_self), XLTW_Delete,
								NULL);
				LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);

				/*
				 * If xwait had just locked the tuple then some other xact
				 * could update this tuple before we get to this point.  Check
				 * for xmax change, and start over if so.
				 */
				if (xmax_infomask_changed(tp.t_data->t_infomask, infomask) ||
					!TransactionIdEquals(HeapTupleHeaderGetRawXmax(tp.t_data),
										 xwait))
					goto l1;
			}

			/*
			 * You might think the multixact is necessarily done here, but not
			 * so: it could have surviving members, namely our own xact or
			 * other subxacts of this backend.  It is legal for us to delete
			 * the tuple in either case, however (the latter case is
			 * essentially a situation of upgrading our former shared lock to
			 * exclusive).  We don't bother changing the on-disk hint bits
			 * since we are about to overwrite the xmax altogether.
			 */
		}
		else if (!TransactionIdIsCurrentTransactionId(xwait))
		{
			/*
			 * Wait for regular transaction to end; but first, acquire tuple
			 * lock.
			 */
			LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
			heap_acquire_tuplock(relation, &(tp.t_self), LockTupleExclusive,
								 LockWaitBlock, &have_tuple_lock);
			XactLockTableWait(xwait, relation, &(tp.t_self), XLTW_Delete);
			LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);

			/*
			 * xwait is done, but if xwait had just locked the tuple then some
			 * other xact could update this tuple before we get to this point.
			 * Check for xmax change, and start over if so.
			 */
			if (xmax_infomask_changed(tp.t_data->t_infomask, infomask) ||
				!TransactionIdEquals(HeapTupleHeaderGetRawXmax(tp.t_data),
									 xwait))
				goto l1;

			/* Otherwise check if it committed or aborted */
			UpdateXmaxHintBits(tp.t_data, buffer, xwait);
		}

		/*
		 * We may overwrite if previous xmax aborted, or if it committed but
		 * only locked the tuple without updating it.
		 */
		if ((tp.t_data->t_infomask & HEAP_XMAX_INVALID) ||
			HEAP_XMAX_IS_LOCKED_ONLY(tp.t_data->t_infomask) ||
			HeapTupleHeaderIsOnlyLocked(tp.t_data))
			result = TM_Ok;
		else if (!ItemPointerEquals(&tp.t_self, &tp.t_data->t_ctid) ||
				 HeapTupleHeaderIndicatesMovedPartitions(tp.t_data))
			result = TM_Updated;
		else
			result = TM_Deleted;
	}

	if (crosscheck != InvalidSnapshot && result == TM_Ok)
	{
		/* Perform additional check for transaction-snapshot mode RI updates */
		if (!HeapTupleSatisfiesVisibility(&tp, crosscheck, buffer))
			result = TM_Updated;
	}

	if (result != TM_Ok)
	{
		Assert(result == TM_SelfModified ||
			   result == TM_Updated ||
			   result == TM_Deleted ||
			   result == TM_BeingModified);
		Assert(!(tp.t_data->t_infomask & HEAP_XMAX_INVALID));
		Assert(result != TM_Updated ||
			   !ItemPointerEquals(&tp.t_self, &tp.t_data->t_ctid));
		tmfd->ctid = tp.t_data->t_ctid;
		tmfd->xmax = HeapTupleHeaderGetUpdateXid(tp.t_data);
		if (result == TM_SelfModified)
			tmfd->cmax = HeapTupleHeaderGetCmax(tp.t_data);
		else
			tmfd->cmax = InvalidCommandId;
		UnlockReleaseBuffer(buffer);
		if (have_tuple_lock)
			UnlockTupleTuplock(relation, &(tp.t_self), LockTupleExclusive);
		if (vmbuffer != InvalidBuffer)
			ReleaseBuffer(vmbuffer);
		return result;
	}

	/*
	 * We're about to do the actual delete -- check for conflict first, to
	 * avoid possibly having to roll back work we've just done.
	 *
	 * This is safe without a recheck as long as there is no possibility of
	 * another process scanning the page between this check and the delete
	 * being visible to the scan (i.e., an exclusive buffer content lock is
	 * continuously held from this point until the tuple delete is visible).
	 */
	CheckForSerializableConflictIn(relation, &tp, buffer);

	/* replace cid with a combo cid if necessary */
	HeapTupleHeaderAdjustCmax(tp.t_data, &cid, &iscombo);

	/*
	 * Compute replica identity tuple before entering the critical section so
	 * we don't PANIC upon a memory allocation failure.
	 */
	old_key_tuple = ExtractReplicaIdentity(relation, &tp, true, &old_key_copied);

	/*
	 * If this is the first possibly-multixact-able operation in the current
	 * transaction, set my per-backend OldestMemberMXactId setting. We can be
	 * certain that the transaction will never become a member of any older
	 * MultiXactIds than that.  (We have to do this even if we end up just
	 * using our own TransactionId below, since some other backend could
	 * incorporate our XID into a MultiXact immediately afterwards.)
	 */
	MultiXactIdSetOldestMember();

	compute_new_xmax_infomask(HeapTupleHeaderGetRawXmax(tp.t_data),
							  tp.t_data->t_infomask, tp.t_data->t_infomask2,
							  xid, LockTupleExclusive, true,
							  &new_xmax, &new_infomask, &new_infomask2);

	START_CRIT_SECTION();

	/*
	 * If this transaction commits, the tuple will become DEAD sooner or
	 * later.  Set flag that this page is a candidate for pruning once our xid
	 * falls below the OldestXmin horizon.  If the transaction finally aborts,
	 * the subsequent page pruning will be a no-op and the hint will be
	 * cleared.
	 */
	PageSetPrunable(page, xid);

	if (PageIsAllVisible(page))
	{
		all_visible_cleared = true;
		PageClearAllVisible(page);
		visibilitymap_clear(relation, BufferGetBlockNumber(buffer),
							vmbuffer, VISIBILITYMAP_VALID_BITS);
	}

	/* store transaction information of xact deleting the tuple */
	tp.t_data->t_infomask &= ~(HEAP_XMAX_BITS | HEAP_MOVED);
	tp.t_data->t_infomask2 &= ~HEAP_KEYS_UPDATED;
	tp.t_data->t_infomask |= new_infomask;
	tp.t_data->t_infomask2 |= new_infomask2;
	HeapTupleHeaderClearHotUpdated(tp.t_data);
	HeapTupleHeaderSetXmax(tp.t_data, new_xmax);
	HeapTupleHeaderSetCmax(tp.t_data, cid, iscombo);
	/* Make sure there is no forward chain link in t_ctid */
	tp.t_data->t_ctid = tp.t_self;

	/* Signal that this is actually a move into another partition */
	if (changingPart)
		HeapTupleHeaderSetMovedPartitions(tp.t_data);

	MarkBufferDirty(buffer);

	/*
	 * XLOG stuff
	 *
	 * NB: heap_abort_speculative() uses the same xlog record and replay
	 * routines.
	 */
	if (RelationNeedsWAL(relation))
	{
		xl_heap_delete xlrec;
		xl_heap_header xlhdr;
		XLogRecPtr	recptr;

		/* For logical decode we need combocids to properly decode the catalog */
		if (RelationIsAccessibleInLogicalDecoding(relation))
			log_heap_new_cid(relation, &tp);

		xlrec.flags = 0;
		if (all_visible_cleared)
			xlrec.flags |= XLH_DELETE_ALL_VISIBLE_CLEARED;
		if (changingPart)
			xlrec.flags |= XLH_DELETE_IS_PARTITION_MOVE;
		xlrec.infobits_set = compute_infobits(tp.t_data->t_infomask,
											  tp.t_data->t_infomask2);
		xlrec.offnum = ItemPointerGetOffsetNumber(&tp.t_self);
		xlrec.xmax = new_xmax;

		if (old_key_tuple != NULL)
		{
			if (relation->rd_rel->relreplident == REPLICA_IDENTITY_FULL)
				xlrec.flags |= XLH_DELETE_CONTAINS_OLD_TUPLE;
			else
				xlrec.flags |= XLH_DELETE_CONTAINS_OLD_KEY;
		}

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfHeapDelete);

		XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);

		/*
		 * Log replica identity of the deleted tuple if there is one
		 */
		if (old_key_tuple != NULL)
		{
			xlhdr.t_infomask2 = old_key_tuple->t_data->t_infomask2;
			xlhdr.t_infomask = old_key_tuple->t_data->t_infomask;
			xlhdr.t_hoff = old_key_tuple->t_data->t_hoff;

			XLogRegisterData((char *) &xlhdr, SizeOfHeapHeader);
			XLogRegisterData((char *) old_key_tuple->t_data
							 + SizeofHeapTupleHeader,
							 old_key_tuple->t_len
							 - SizeofHeapTupleHeader);
		}

		/* filtering by origin on a row level is much more efficient */
		XLogSetRecordFlags(XLOG_INCLUDE_ORIGIN);

		recptr = XLogInsert(RM_HEAP_ID, XLOG_HEAP_DELETE);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	LockBuffer(buffer, BUFFER_LOCK_UNLOCK);

	if (vmbuffer != InvalidBuffer)
		ReleaseBuffer(vmbuffer);

	/*
	 * If the tuple has toasted out-of-line attributes, we need to delete
	 * those items too.  We have to do this before releasing the buffer
	 * because we need to look at the contents of the tuple, but it's OK to
	 * release the content lock on the buffer first.
	 */
	if (relation->rd_rel->relkind != RELKIND_RELATION &&
		relation->rd_rel->relkind != RELKIND_MATVIEW)
	{
		/* toast table entries should never be recursively toasted */
		Assert(!HeapTupleHasExternal(&tp));
	}
	else if (HeapTupleHasExternal(&tp))
		heap_toast_delete(relation, &tp, false);

	/*
	 * Mark tuple for invalidation from system caches at next command
	 * boundary. We have to do this before releasing the buffer because we
	 * need to look at the contents of the tuple.
	 */
	CacheInvalidateHeapTuple(relation, &tp, NULL);

	/* Now we can release the buffer */
	ReleaseBuffer(buffer);

	/*
	 * Release the lmgr tuple lock, if we had it.
	 */
	if (have_tuple_lock)
		UnlockTupleTuplock(relation, &(tp.t_self), LockTupleExclusive);

	pgstat_count_heap_delete(relation);

	if (old_key_tuple != NULL && old_key_copied)
		heap_freetuple(old_key_tuple);

	return TM_Ok;
}