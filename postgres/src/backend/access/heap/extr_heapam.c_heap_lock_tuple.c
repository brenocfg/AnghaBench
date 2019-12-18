#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  infobits_set; scalar_t__ locking_xid; int /*<<< orphan*/  offnum; } ;
typedef  TYPE_1__ xl_heap_lock ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_24__ {TYPE_4__* t_data; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_len; } ;
struct TYPE_23__ {int t_infomask; int t_infomask2; int /*<<< orphan*/  t_ctid; } ;
struct TYPE_22__ {int /*<<< orphan*/  status; scalar_t__ xid; } ;
struct TYPE_21__ {int /*<<< orphan*/  cmax; int /*<<< orphan*/  xmax; int /*<<< orphan*/  ctid; } ;
typedef  scalar_t__ TM_Result ;
typedef  TYPE_2__ TM_FailureData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ MultiXactStatus ;
typedef  TYPE_3__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int /*<<< orphan*/  LockWaitPolicy ;
typedef  int const LockTupleMode ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_4__* HeapTupleHeader ;
typedef  TYPE_5__* HeapTuple ;
typedef  int /*<<< orphan*/  CommandId ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 scalar_t__ BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/  ConditionalMultiXactIdWait (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConditionalXactLockTableWait (scalar_t__) ; 
 int /*<<< orphan*/  DoesMultiXactIdConflict (int /*<<< orphan*/ ,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_LOCK_NOT_AVAILABLE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTransactionId () ; 
 int GetMultiXactIdMembers (scalar_t__,TYPE_3__**,int,int) ; 
 int HEAP_KEYS_UPDATED ; 
 int HEAP_XMAX_BITS ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_EXCL_LOCKED (int) ; 
 scalar_t__ HEAP_XMAX_IS_KEYSHR_LOCKED (int) ; 
 int HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 int /*<<< orphan*/  HEAP_XMAX_IS_SHR_LOCKED (int) ; 
 int /*<<< orphan*/  HeapTupleHeaderClearHotUpdated (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetCmax (TYPE_4__*) ; 
 scalar_t__ HeapTupleHeaderGetRawXmax (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_4__*) ; 
 scalar_t__ HeapTupleHeaderIndicatesMovedPartitions (TYPE_4__*) ; 
 scalar_t__ HeapTupleHeaderIsOnlyLocked (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_4__*,scalar_t__) ; 
 scalar_t__ HeapTupleSatisfiesUpdate (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  InvalidCommandId ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
#define  LockTupleExclusive 134 
#define  LockTupleKeyShare 133 
#define  LockTupleNoKeyExclusive 132 
#define  LockTupleShare 131 
#define  LockWaitBlock 130 
#define  LockWaitError 129 
#define  LockWaitSkip 128 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactIdSetOldestMember () ; 
 int /*<<< orphan*/  MultiXactIdWait (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MultiXactStatusNoKeyUpdate ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsAllVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP_ID ; 
 scalar_t__ ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHeapLock ; 
 scalar_t__ TM_BeingModified ; 
 scalar_t__ TM_Deleted ; 
 scalar_t__ TM_Invisible ; 
 scalar_t__ TM_Ok ; 
 scalar_t__ TM_SelfModified ; 
 scalar_t__ TM_Updated ; 
 scalar_t__ TM_WouldBlock ; 
 int const TUPLOCK_from_mxstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdEquals (scalar_t__,scalar_t__) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (scalar_t__) ; 
 int /*<<< orphan*/  UnlockTupleTuplock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  UpdateXmaxHintBits (TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VISIBILITYMAP_ALL_FROZEN ; 
 int /*<<< orphan*/  XLH_LOCK_ALL_FROZEN_CLEARED ; 
 int /*<<< orphan*/  XLOG_HEAP_LOCK ; 
 int /*<<< orphan*/  XLTW_Lock ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactLockTableWait (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_infobits (int,int) ; 
 int /*<<< orphan*/  compute_new_xmax_infomask (scalar_t__,int,int,int /*<<< orphan*/ ,int const,int,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_mxact_status_for_lock (int const,int) ; 
 int /*<<< orphan*/  heap_acquire_tuplock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ heap_lock_updated_tuple (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 scalar_t__ visibilitymap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visibilitymap_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ xmax_infomask_changed (int,int) ; 

TM_Result
heap_lock_tuple(Relation relation, HeapTuple tuple,
				CommandId cid, LockTupleMode mode, LockWaitPolicy wait_policy,
				bool follow_updates,
				Buffer *buffer, TM_FailureData *tmfd)
{
	TM_Result	result;
	ItemPointer tid = &(tuple->t_self);
	ItemId		lp;
	Page		page;
	Buffer		vmbuffer = InvalidBuffer;
	BlockNumber block;
	TransactionId xid,
				xmax;
	uint16		old_infomask,
				new_infomask,
				new_infomask2;
	bool		first_time = true;
	bool		skip_tuple_lock = false;
	bool		have_tuple_lock = false;
	bool		cleared_all_frozen = false;

	*buffer = ReadBuffer(relation, ItemPointerGetBlockNumber(tid));
	block = ItemPointerGetBlockNumber(tid);

	/*
	 * Before locking the buffer, pin the visibility map page if it appears to
	 * be necessary.  Since we haven't got the lock yet, someone else might be
	 * in the middle of changing this, so we'll need to recheck after we have
	 * the lock.
	 */
	if (PageIsAllVisible(BufferGetPage(*buffer)))
		visibilitymap_pin(relation, block, &vmbuffer);

	LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);

	page = BufferGetPage(*buffer);
	lp = PageGetItemId(page, ItemPointerGetOffsetNumber(tid));
	Assert(ItemIdIsNormal(lp));

	tuple->t_data = (HeapTupleHeader) PageGetItem(page, lp);
	tuple->t_len = ItemIdGetLength(lp);
	tuple->t_tableOid = RelationGetRelid(relation);

l3:
	result = HeapTupleSatisfiesUpdate(tuple, cid, *buffer);

	if (result == TM_Invisible)
	{
		/*
		 * This is possible, but only when locking a tuple for ON CONFLICT
		 * UPDATE.  We return this value here rather than throwing an error in
		 * order to give that case the opportunity to throw a more specific
		 * error.
		 */
		result = TM_Invisible;
		goto out_locked;
	}
	else if (result == TM_BeingModified ||
			 result == TM_Updated ||
			 result == TM_Deleted)
	{
		TransactionId xwait;
		uint16		infomask;
		uint16		infomask2;
		bool		require_sleep;
		ItemPointerData t_ctid;

		/* must copy state data before unlocking buffer */
		xwait = HeapTupleHeaderGetRawXmax(tuple->t_data);
		infomask = tuple->t_data->t_infomask;
		infomask2 = tuple->t_data->t_infomask2;
		ItemPointerCopy(&tuple->t_data->t_ctid, &t_ctid);

		LockBuffer(*buffer, BUFFER_LOCK_UNLOCK);

		/*
		 * If any subtransaction of the current top transaction already holds
		 * a lock as strong as or stronger than what we're requesting, we
		 * effectively hold the desired lock already.  We *must* succeed
		 * without trying to take the tuple lock, else we will deadlock
		 * against anyone wanting to acquire a stronger lock.
		 *
		 * Note we only do this the first time we loop on the HTSU result;
		 * there is no point in testing in subsequent passes, because
		 * evidently our own transaction cannot have acquired a new lock after
		 * the first time we checked.
		 */
		if (first_time)
		{
			first_time = false;

			if (infomask & HEAP_XMAX_IS_MULTI)
			{
				int			i;
				int			nmembers;
				MultiXactMember *members;

				/*
				 * We don't need to allow old multixacts here; if that had
				 * been the case, HeapTupleSatisfiesUpdate would have returned
				 * MayBeUpdated and we wouldn't be here.
				 */
				nmembers =
					GetMultiXactIdMembers(xwait, &members, false,
										  HEAP_XMAX_IS_LOCKED_ONLY(infomask));

				for (i = 0; i < nmembers; i++)
				{
					/* only consider members of our own transaction */
					if (!TransactionIdIsCurrentTransactionId(members[i].xid))
						continue;

					if (TUPLOCK_from_mxstatus(members[i].status) >= mode)
					{
						pfree(members);
						result = TM_Ok;
						goto out_unlocked;
					}
					else
					{
						/*
						 * Disable acquisition of the heavyweight tuple lock.
						 * Otherwise, when promoting a weaker lock, we might
						 * deadlock with another locker that has acquired the
						 * heavyweight tuple lock and is waiting for our
						 * transaction to finish.
						 *
						 * Note that in this case we still need to wait for
						 * the multixact if required, to avoid acquiring
						 * conflicting locks.
						 */
						skip_tuple_lock = true;
					}
				}

				if (members)
					pfree(members);
			}
			else if (TransactionIdIsCurrentTransactionId(xwait))
			{
				switch (mode)
				{
					case LockTupleKeyShare:
						Assert(HEAP_XMAX_IS_KEYSHR_LOCKED(infomask) ||
							   HEAP_XMAX_IS_SHR_LOCKED(infomask) ||
							   HEAP_XMAX_IS_EXCL_LOCKED(infomask));
						result = TM_Ok;
						goto out_unlocked;
					case LockTupleShare:
						if (HEAP_XMAX_IS_SHR_LOCKED(infomask) ||
							HEAP_XMAX_IS_EXCL_LOCKED(infomask))
						{
							result = TM_Ok;
							goto out_unlocked;
						}
						break;
					case LockTupleNoKeyExclusive:
						if (HEAP_XMAX_IS_EXCL_LOCKED(infomask))
						{
							result = TM_Ok;
							goto out_unlocked;
						}
						break;
					case LockTupleExclusive:
						if (HEAP_XMAX_IS_EXCL_LOCKED(infomask) &&
							infomask2 & HEAP_KEYS_UPDATED)
						{
							result = TM_Ok;
							goto out_unlocked;
						}
						break;
				}
			}
		}

		/*
		 * Initially assume that we will have to wait for the locking
		 * transaction(s) to finish.  We check various cases below in which
		 * this can be turned off.
		 */
		require_sleep = true;
		if (mode == LockTupleKeyShare)
		{
			/*
			 * If we're requesting KeyShare, and there's no update present, we
			 * don't need to wait.  Even if there is an update, we can still
			 * continue if the key hasn't been modified.
			 *
			 * However, if there are updates, we need to walk the update chain
			 * to mark future versions of the row as locked, too.  That way,
			 * if somebody deletes that future version, we're protected
			 * against the key going away.  This locking of future versions
			 * could block momentarily, if a concurrent transaction is
			 * deleting a key; or it could return a value to the effect that
			 * the transaction deleting the key has already committed.  So we
			 * do this before re-locking the buffer; otherwise this would be
			 * prone to deadlocks.
			 *
			 * Note that the TID we're locking was grabbed before we unlocked
			 * the buffer.  For it to change while we're not looking, the
			 * other properties we're testing for below after re-locking the
			 * buffer would also change, in which case we would restart this
			 * loop above.
			 */
			if (!(infomask2 & HEAP_KEYS_UPDATED))
			{
				bool		updated;

				updated = !HEAP_XMAX_IS_LOCKED_ONLY(infomask);

				/*
				 * If there are updates, follow the update chain; bail out if
				 * that cannot be done.
				 */
				if (follow_updates && updated)
				{
					TM_Result	res;

					res = heap_lock_updated_tuple(relation, tuple, &t_ctid,
												  GetCurrentTransactionId(),
												  mode);
					if (res != TM_Ok)
					{
						result = res;
						/* recovery code expects to have buffer lock held */
						LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
						goto failed;
					}
				}

				LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);

				/*
				 * Make sure it's still an appropriate lock, else start over.
				 * Also, if it wasn't updated before we released the lock, but
				 * is updated now, we start over too; the reason is that we
				 * now need to follow the update chain to lock the new
				 * versions.
				 */
				if (!HeapTupleHeaderIsOnlyLocked(tuple->t_data) &&
					((tuple->t_data->t_infomask2 & HEAP_KEYS_UPDATED) ||
					 !updated))
					goto l3;

				/* Things look okay, so we can skip sleeping */
				require_sleep = false;

				/*
				 * Note we allow Xmax to change here; other updaters/lockers
				 * could have modified it before we grabbed the buffer lock.
				 * However, this is not a problem, because with the recheck we
				 * just did we ensure that they still don't conflict with the
				 * lock we want.
				 */
			}
		}
		else if (mode == LockTupleShare)
		{
			/*
			 * If we're requesting Share, we can similarly avoid sleeping if
			 * there's no update and no exclusive lock present.
			 */
			if (HEAP_XMAX_IS_LOCKED_ONLY(infomask) &&
				!HEAP_XMAX_IS_EXCL_LOCKED(infomask))
			{
				LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);

				/*
				 * Make sure it's still an appropriate lock, else start over.
				 * See above about allowing xmax to change.
				 */
				if (!HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_data->t_infomask) ||
					HEAP_XMAX_IS_EXCL_LOCKED(tuple->t_data->t_infomask))
					goto l3;
				require_sleep = false;
			}
		}
		else if (mode == LockTupleNoKeyExclusive)
		{
			/*
			 * If we're requesting NoKeyExclusive, we might also be able to
			 * avoid sleeping; just ensure that there no conflicting lock
			 * already acquired.
			 */
			if (infomask & HEAP_XMAX_IS_MULTI)
			{
				if (!DoesMultiXactIdConflict((MultiXactId) xwait, infomask,
											 mode, NULL))
				{
					/*
					 * No conflict, but if the xmax changed under us in the
					 * meantime, start over.
					 */
					LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
					if (xmax_infomask_changed(tuple->t_data->t_infomask, infomask) ||
						!TransactionIdEquals(HeapTupleHeaderGetRawXmax(tuple->t_data),
											 xwait))
						goto l3;

					/* otherwise, we're good */
					require_sleep = false;
				}
			}
			else if (HEAP_XMAX_IS_KEYSHR_LOCKED(infomask))
			{
				LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);

				/* if the xmax changed in the meantime, start over */
				if (xmax_infomask_changed(tuple->t_data->t_infomask, infomask) ||
					!TransactionIdEquals(
										 HeapTupleHeaderGetRawXmax(tuple->t_data),
										 xwait))
					goto l3;
				/* otherwise, we're good */
				require_sleep = false;
			}
		}

		/*
		 * As a check independent from those above, we can also avoid sleeping
		 * if the current transaction is the sole locker of the tuple.  Note
		 * that the strength of the lock already held is irrelevant; this is
		 * not about recording the lock in Xmax (which will be done regardless
		 * of this optimization, below).  Also, note that the cases where we
		 * hold a lock stronger than we are requesting are already handled
		 * above by not doing anything.
		 *
		 * Note we only deal with the non-multixact case here; MultiXactIdWait
		 * is well equipped to deal with this situation on its own.
		 */
		if (require_sleep && !(infomask & HEAP_XMAX_IS_MULTI) &&
			TransactionIdIsCurrentTransactionId(xwait))
		{
			/* ... but if the xmax changed in the meantime, start over */
			LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
			if (xmax_infomask_changed(tuple->t_data->t_infomask, infomask) ||
				!TransactionIdEquals(HeapTupleHeaderGetRawXmax(tuple->t_data),
									 xwait))
				goto l3;
			Assert(HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_data->t_infomask));
			require_sleep = false;
		}

		/*
		 * Time to sleep on the other transaction/multixact, if necessary.
		 *
		 * If the other transaction is an update/delete that's already
		 * committed, then sleeping cannot possibly do any good: if we're
		 * required to sleep, get out to raise an error instead.
		 *
		 * By here, we either have already acquired the buffer exclusive lock,
		 * or we must wait for the locking transaction or multixact; so below
		 * we ensure that we grab buffer lock after the sleep.
		 */
		if (require_sleep && (result == TM_Updated || result == TM_Deleted))
		{
			LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
			goto failed;
		}
		else if (require_sleep)
		{
			/*
			 * Acquire tuple lock to establish our priority for the tuple, or
			 * die trying.  LockTuple will release us when we are next-in-line
			 * for the tuple.  We must do this even if we are share-locking,
			 * but not if we already have a weaker lock on the tuple.
			 *
			 * If we are forced to "start over" below, we keep the tuple lock;
			 * this arranges that we stay at the head of the line while
			 * rechecking tuple state.
			 */
			if (!skip_tuple_lock &&
				!heap_acquire_tuplock(relation, tid, mode, wait_policy,
									  &have_tuple_lock))
			{
				/*
				 * This can only happen if wait_policy is Skip and the lock
				 * couldn't be obtained.
				 */
				result = TM_WouldBlock;
				/* recovery code expects to have buffer lock held */
				LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
				goto failed;
			}

			if (infomask & HEAP_XMAX_IS_MULTI)
			{
				MultiXactStatus status = get_mxact_status_for_lock(mode, false);

				/* We only ever lock tuples, never update them */
				if (status >= MultiXactStatusNoKeyUpdate)
					elog(ERROR, "invalid lock mode in heap_lock_tuple");

				/* wait for multixact to end, or die trying  */
				switch (wait_policy)
				{
					case LockWaitBlock:
						MultiXactIdWait((MultiXactId) xwait, status, infomask,
										relation, &tuple->t_self, XLTW_Lock, NULL);
						break;
					case LockWaitSkip:
						if (!ConditionalMultiXactIdWait((MultiXactId) xwait,
														status, infomask, relation,
														NULL))
						{
							result = TM_WouldBlock;
							/* recovery code expects to have buffer lock held */
							LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
							goto failed;
						}
						break;
					case LockWaitError:
						if (!ConditionalMultiXactIdWait((MultiXactId) xwait,
														status, infomask, relation,
														NULL))
							ereport(ERROR,
									(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
									 errmsg("could not obtain lock on row in relation \"%s\"",
											RelationGetRelationName(relation))));

						break;
				}

				/*
				 * Of course, the multixact might not be done here: if we're
				 * requesting a light lock mode, other transactions with light
				 * locks could still be alive, as well as locks owned by our
				 * own xact or other subxacts of this backend.  We need to
				 * preserve the surviving MultiXact members.  Note that it
				 * isn't absolutely necessary in the latter case, but doing so
				 * is simpler.
				 */
			}
			else
			{
				/* wait for regular transaction to end, or die trying */
				switch (wait_policy)
				{
					case LockWaitBlock:
						XactLockTableWait(xwait, relation, &tuple->t_self,
										  XLTW_Lock);
						break;
					case LockWaitSkip:
						if (!ConditionalXactLockTableWait(xwait))
						{
							result = TM_WouldBlock;
							/* recovery code expects to have buffer lock held */
							LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
							goto failed;
						}
						break;
					case LockWaitError:
						if (!ConditionalXactLockTableWait(xwait))
							ereport(ERROR,
									(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
									 errmsg("could not obtain lock on row in relation \"%s\"",
											RelationGetRelationName(relation))));
						break;
				}
			}

			/* if there are updates, follow the update chain */
			if (follow_updates && !HEAP_XMAX_IS_LOCKED_ONLY(infomask))
			{
				TM_Result	res;

				res = heap_lock_updated_tuple(relation, tuple, &t_ctid,
											  GetCurrentTransactionId(),
											  mode);
				if (res != TM_Ok)
				{
					result = res;
					/* recovery code expects to have buffer lock held */
					LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
					goto failed;
				}
			}

			LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);

			/*
			 * xwait is done, but if xwait had just locked the tuple then some
			 * other xact could update this tuple before we get to this point.
			 * Check for xmax change, and start over if so.
			 */
			if (xmax_infomask_changed(tuple->t_data->t_infomask, infomask) ||
				!TransactionIdEquals(HeapTupleHeaderGetRawXmax(tuple->t_data),
									 xwait))
				goto l3;

			if (!(infomask & HEAP_XMAX_IS_MULTI))
			{
				/*
				 * Otherwise check if it committed or aborted.  Note we cannot
				 * be here if the tuple was only locked by somebody who didn't
				 * conflict with us; that would have been handled above.  So
				 * that transaction must necessarily be gone by now.  But
				 * don't check for this in the multixact case, because some
				 * locker transactions might still be running.
				 */
				UpdateXmaxHintBits(tuple->t_data, *buffer, xwait);
			}
		}

		/* By here, we're certain that we hold buffer exclusive lock again */

		/*
		 * We may lock if previous xmax aborted, or if it committed but only
		 * locked the tuple without updating it; or if we didn't have to wait
		 * at all for whatever reason.
		 */
		if (!require_sleep ||
			(tuple->t_data->t_infomask & HEAP_XMAX_INVALID) ||
			HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_data->t_infomask) ||
			HeapTupleHeaderIsOnlyLocked(tuple->t_data))
			result = TM_Ok;
		else if (!ItemPointerEquals(&tuple->t_self, &tuple->t_data->t_ctid) ||
				 HeapTupleHeaderIndicatesMovedPartitions(tuple->t_data))
			result = TM_Updated;
		else
			result = TM_Deleted;
	}

failed:
	if (result != TM_Ok)
	{
		Assert(result == TM_SelfModified || result == TM_Updated ||
			   result == TM_Deleted || result == TM_WouldBlock);
		Assert(!(tuple->t_data->t_infomask & HEAP_XMAX_INVALID));
		Assert(result != TM_Updated ||
			   !ItemPointerEquals(&tuple->t_self, &tuple->t_data->t_ctid));
		tmfd->ctid = tuple->t_data->t_ctid;
		tmfd->xmax = HeapTupleHeaderGetUpdateXid(tuple->t_data);
		if (result == TM_SelfModified)
			tmfd->cmax = HeapTupleHeaderGetCmax(tuple->t_data);
		else
			tmfd->cmax = InvalidCommandId;
		goto out_locked;
	}

	/*
	 * If we didn't pin the visibility map page and the page has become all
	 * visible while we were busy locking the buffer, or during some
	 * subsequent window during which we had it unlocked, we'll have to unlock
	 * and re-lock, to avoid holding the buffer lock across I/O.  That's a bit
	 * unfortunate, especially since we'll now have to recheck whether the
	 * tuple has been locked or updated under us, but hopefully it won't
	 * happen very often.
	 */
	if (vmbuffer == InvalidBuffer && PageIsAllVisible(page))
	{
		LockBuffer(*buffer, BUFFER_LOCK_UNLOCK);
		visibilitymap_pin(relation, block, &vmbuffer);
		LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
		goto l3;
	}

	xmax = HeapTupleHeaderGetRawXmax(tuple->t_data);
	old_infomask = tuple->t_data->t_infomask;

	/*
	 * If this is the first possibly-multixact-able operation in the current
	 * transaction, set my per-backend OldestMemberMXactId setting. We can be
	 * certain that the transaction will never become a member of any older
	 * MultiXactIds than that.  (We have to do this even if we end up just
	 * using our own TransactionId below, since some other backend could
	 * incorporate our XID into a MultiXact immediately afterwards.)
	 */
	MultiXactIdSetOldestMember();

	/*
	 * Compute the new xmax and infomask to store into the tuple.  Note we do
	 * not modify the tuple just yet, because that would leave it in the wrong
	 * state if multixact.c elogs.
	 */
	compute_new_xmax_infomask(xmax, old_infomask, tuple->t_data->t_infomask2,
							  GetCurrentTransactionId(), mode, false,
							  &xid, &new_infomask, &new_infomask2);

	START_CRIT_SECTION();

	/*
	 * Store transaction information of xact locking the tuple.
	 *
	 * Note: Cmax is meaningless in this context, so don't set it; this avoids
	 * possibly generating a useless combo CID.  Moreover, if we're locking a
	 * previously updated tuple, it's important to preserve the Cmax.
	 *
	 * Also reset the HOT UPDATE bit, but only if there's no update; otherwise
	 * we would break the HOT chain.
	 */
	tuple->t_data->t_infomask &= ~HEAP_XMAX_BITS;
	tuple->t_data->t_infomask2 &= ~HEAP_KEYS_UPDATED;
	tuple->t_data->t_infomask |= new_infomask;
	tuple->t_data->t_infomask2 |= new_infomask2;
	if (HEAP_XMAX_IS_LOCKED_ONLY(new_infomask))
		HeapTupleHeaderClearHotUpdated(tuple->t_data);
	HeapTupleHeaderSetXmax(tuple->t_data, xid);

	/*
	 * Make sure there is no forward chain link in t_ctid.  Note that in the
	 * cases where the tuple has been updated, we must not overwrite t_ctid,
	 * because it was set by the updater.  Moreover, if the tuple has been
	 * updated, we need to follow the update chain to lock the new versions of
	 * the tuple as well.
	 */
	if (HEAP_XMAX_IS_LOCKED_ONLY(new_infomask))
		tuple->t_data->t_ctid = *tid;

	/* Clear only the all-frozen bit on visibility map if needed */
	if (PageIsAllVisible(page) &&
		visibilitymap_clear(relation, block, vmbuffer,
							VISIBILITYMAP_ALL_FROZEN))
		cleared_all_frozen = true;


	MarkBufferDirty(*buffer);

	/*
	 * XLOG stuff.  You might think that we don't need an XLOG record because
	 * there is no state change worth restoring after a crash.  You would be
	 * wrong however: we have just written either a TransactionId or a
	 * MultiXactId that may never have been seen on disk before, and we need
	 * to make sure that there are XLOG entries covering those ID numbers.
	 * Else the same IDs might be re-used after a crash, which would be
	 * disastrous if this page made it to disk before the crash.  Essentially
	 * we have to enforce the WAL log-before-data rule even in this case.
	 * (Also, in a PITR log-shipping or 2PC environment, we have to have XLOG
	 * entries for everything anyway.)
	 */
	if (RelationNeedsWAL(relation))
	{
		xl_heap_lock xlrec;
		XLogRecPtr	recptr;

		XLogBeginInsert();
		XLogRegisterBuffer(0, *buffer, REGBUF_STANDARD);

		xlrec.offnum = ItemPointerGetOffsetNumber(&tuple->t_self);
		xlrec.locking_xid = xid;
		xlrec.infobits_set = compute_infobits(new_infomask,
											  tuple->t_data->t_infomask2);
		xlrec.flags = cleared_all_frozen ? XLH_LOCK_ALL_FROZEN_CLEARED : 0;
		XLogRegisterData((char *) &xlrec, SizeOfHeapLock);

		/* we don't decode row locks atm, so no need to log the origin */

		recptr = XLogInsert(RM_HEAP_ID, XLOG_HEAP_LOCK);

		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	result = TM_Ok;

out_locked:
	LockBuffer(*buffer, BUFFER_LOCK_UNLOCK);

out_unlocked:
	if (BufferIsValid(vmbuffer))
		ReleaseBuffer(vmbuffer);

	/*
	 * Don't update the visibility map here. Locking a tuple doesn't change
	 * visibility info.
	 */

	/*
	 * Now that we have successfully marked the tuple as locked, we can
	 * release the lmgr tuple lock, if we had it.
	 */
	if (have_tuple_lock)
		UnlockTupleTuplock(relation, tid, mode);

	return result;
}