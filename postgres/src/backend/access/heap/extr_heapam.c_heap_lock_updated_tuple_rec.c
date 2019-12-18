#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  infobits_set; int /*<<< orphan*/  xmax; int /*<<< orphan*/  offnum; } ;
typedef  TYPE_1__ xl_heap_lock_updated ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_17__ {int t_infomask; int t_infomask2; int /*<<< orphan*/  t_ctid; } ;
struct TYPE_16__ {TYPE_7__* t_data; int /*<<< orphan*/  t_self; } ;
struct TYPE_15__ {int /*<<< orphan*/  xid; int /*<<< orphan*/  status; } ;
typedef  scalar_t__ TM_Result ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  MultiXactStatus ;
typedef  TYPE_2__ MultiXactMember ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_3__ HeapTupleData ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int GetMultiXactIdMembers (int /*<<< orphan*/ ,TYPE_2__**,int,scalar_t__) ; 
 int HEAP_KEYS_UPDATED ; 
 int /*<<< orphan*/  HEAP_LOCKED_UPGRADED (int) ; 
 int HEAP_XMAX_BITS ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_EXCL_LOCKED (int) ; 
 scalar_t__ HEAP_XMAX_IS_KEYSHR_LOCKED (int) ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 scalar_t__ HEAP_XMAX_IS_SHR_LOCKED (int) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmax (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (TYPE_7__*) ; 
 scalar_t__ HeapTupleHeaderIndicatesMovedPartitions (TYPE_7__*) ; 
 scalar_t__ HeapTupleHeaderIsOnlyLocked (TYPE_7__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemPointerCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactStatusForKeyShare ; 
 int /*<<< orphan*/  MultiXactStatusForNoKeyUpdate ; 
 int /*<<< orphan*/  MultiXactStatusForShare ; 
 int /*<<< orphan*/  MultiXactStatusForUpdate ; 
 int /*<<< orphan*/  MultiXactStatusNoKeyUpdate ; 
 int /*<<< orphan*/  MultiXactStatusUpdate ; 
 scalar_t__ PageIsAllVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_HEAP2_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfHeapLockUpdated ; 
 int /*<<< orphan*/  SnapshotAny ; 
 scalar_t__ TM_Ok ; 
 scalar_t__ TM_SelfModified ; 
 scalar_t__ TransactionIdDidAbort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  VISIBILITYMAP_ALL_FROZEN ; 
 int /*<<< orphan*/  XLH_LOCK_ALL_FROZEN_CLEARED ; 
 int /*<<< orphan*/  XLOG_HEAP2_LOCK_UPDATED ; 
 int /*<<< orphan*/  XLTW_LockUpdated ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactLockTableWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_infobits (int,int) ; 
 int /*<<< orphan*/  compute_new_xmax_infomask (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 scalar_t__ test_lockmode_for_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int*) ; 
 scalar_t__ visibilitymap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visibilitymap_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static TM_Result
heap_lock_updated_tuple_rec(Relation rel, ItemPointer tid, TransactionId xid,
							LockTupleMode mode)
{
	TM_Result	result;
	ItemPointerData tupid;
	HeapTupleData mytup;
	Buffer		buf;
	uint16		new_infomask,
				new_infomask2,
				old_infomask,
				old_infomask2;
	TransactionId xmax,
				new_xmax;
	TransactionId priorXmax = InvalidTransactionId;
	bool		cleared_all_frozen = false;
	bool		pinned_desired_page;
	Buffer		vmbuffer = InvalidBuffer;
	BlockNumber block;

	ItemPointerCopy(tid, &tupid);

	for (;;)
	{
		new_infomask = 0;
		new_xmax = InvalidTransactionId;
		block = ItemPointerGetBlockNumber(&tupid);
		ItemPointerCopy(&tupid, &(mytup.t_self));

		if (!heap_fetch(rel, SnapshotAny, &mytup, &buf))
		{
			/*
			 * if we fail to find the updated version of the tuple, it's
			 * because it was vacuumed/pruned away after its creator
			 * transaction aborted.  So behave as if we got to the end of the
			 * chain, and there's no further tuple to lock: return success to
			 * caller.
			 */
			result = TM_Ok;
			goto out_unlocked;
		}

l4:
		CHECK_FOR_INTERRUPTS();

		/*
		 * Before locking the buffer, pin the visibility map page if it
		 * appears to be necessary.  Since we haven't got the lock yet,
		 * someone else might be in the middle of changing this, so we'll need
		 * to recheck after we have the lock.
		 */
		if (PageIsAllVisible(BufferGetPage(buf)))
		{
			visibilitymap_pin(rel, block, &vmbuffer);
			pinned_desired_page = true;
		}
		else
			pinned_desired_page = false;

		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

		/*
		 * If we didn't pin the visibility map page and the page has become
		 * all visible while we were busy locking the buffer, we'll have to
		 * unlock and re-lock, to avoid holding the buffer lock across I/O.
		 * That's a bit unfortunate, but hopefully shouldn't happen often.
		 *
		 * Note: in some paths through this function, we will reach here
		 * holding a pin on a vm page that may or may not be the one matching
		 * this page.  If this page isn't all-visible, we won't use the vm
		 * page, but we hold onto such a pin till the end of the function.
		 */
		if (!pinned_desired_page && PageIsAllVisible(BufferGetPage(buf)))
		{
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);
			visibilitymap_pin(rel, block, &vmbuffer);
			LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
		}

		/*
		 * Check the tuple XMIN against prior XMAX, if any.  If we reached the
		 * end of the chain, we're done, so return success.
		 */
		if (TransactionIdIsValid(priorXmax) &&
			!TransactionIdEquals(HeapTupleHeaderGetXmin(mytup.t_data),
								 priorXmax))
		{
			result = TM_Ok;
			goto out_locked;
		}

		/*
		 * Also check Xmin: if this tuple was created by an aborted
		 * (sub)transaction, then we already locked the last live one in the
		 * chain, thus we're done, so return success.
		 */
		if (TransactionIdDidAbort(HeapTupleHeaderGetXmin(mytup.t_data)))
		{
			result = TM_Ok;
			goto out_locked;
		}

		old_infomask = mytup.t_data->t_infomask;
		old_infomask2 = mytup.t_data->t_infomask2;
		xmax = HeapTupleHeaderGetRawXmax(mytup.t_data);

		/*
		 * If this tuple version has been updated or locked by some concurrent
		 * transaction(s), what we do depends on whether our lock mode
		 * conflicts with what those other transactions hold, and also on the
		 * status of them.
		 */
		if (!(old_infomask & HEAP_XMAX_INVALID))
		{
			TransactionId rawxmax;
			bool		needwait;

			rawxmax = HeapTupleHeaderGetRawXmax(mytup.t_data);
			if (old_infomask & HEAP_XMAX_IS_MULTI)
			{
				int			nmembers;
				int			i;
				MultiXactMember *members;

				/*
				 * We don't need a test for pg_upgrade'd tuples: this is only
				 * applied to tuples after the first in an update chain.  Said
				 * first tuple in the chain may well be locked-in-9.2-and-
				 * pg_upgraded, but that one was already locked by our caller,
				 * not us; and any subsequent ones cannot be because our
				 * caller must necessarily have obtained a snapshot later than
				 * the pg_upgrade itself.
				 */
				Assert(!HEAP_LOCKED_UPGRADED(mytup.t_data->t_infomask));

				nmembers = GetMultiXactIdMembers(rawxmax, &members, false,
												 HEAP_XMAX_IS_LOCKED_ONLY(old_infomask));
				for (i = 0; i < nmembers; i++)
				{
					result = test_lockmode_for_conflict(members[i].status,
														members[i].xid,
														mode,
														&mytup,
														&needwait);

					/*
					 * If the tuple was already locked by ourselves in a
					 * previous iteration of this (say heap_lock_tuple was
					 * forced to restart the locking loop because of a change
					 * in xmax), then we hold the lock already on this tuple
					 * version and we don't need to do anything; and this is
					 * not an error condition either.  We just need to skip
					 * this tuple and continue locking the next version in the
					 * update chain.
					 */
					if (result == TM_SelfModified)
					{
						pfree(members);
						goto next;
					}

					if (needwait)
					{
						LockBuffer(buf, BUFFER_LOCK_UNLOCK);
						XactLockTableWait(members[i].xid, rel,
										  &mytup.t_self,
										  XLTW_LockUpdated);
						pfree(members);
						goto l4;
					}
					if (result != TM_Ok)
					{
						pfree(members);
						goto out_locked;
					}
				}
				if (members)
					pfree(members);
			}
			else
			{
				MultiXactStatus status;

				/*
				 * For a non-multi Xmax, we first need to compute the
				 * corresponding MultiXactStatus by using the infomask bits.
				 */
				if (HEAP_XMAX_IS_LOCKED_ONLY(old_infomask))
				{
					if (HEAP_XMAX_IS_KEYSHR_LOCKED(old_infomask))
						status = MultiXactStatusForKeyShare;
					else if (HEAP_XMAX_IS_SHR_LOCKED(old_infomask))
						status = MultiXactStatusForShare;
					else if (HEAP_XMAX_IS_EXCL_LOCKED(old_infomask))
					{
						if (old_infomask2 & HEAP_KEYS_UPDATED)
							status = MultiXactStatusForUpdate;
						else
							status = MultiXactStatusForNoKeyUpdate;
					}
					else
					{
						/*
						 * LOCK_ONLY present alone (a pg_upgraded tuple marked
						 * as share-locked in the old cluster) shouldn't be
						 * seen in the middle of an update chain.
						 */
						elog(ERROR, "invalid lock status in tuple");
					}
				}
				else
				{
					/* it's an update, but which kind? */
					if (old_infomask2 & HEAP_KEYS_UPDATED)
						status = MultiXactStatusUpdate;
					else
						status = MultiXactStatusNoKeyUpdate;
				}

				result = test_lockmode_for_conflict(status, rawxmax, mode,
													&mytup, &needwait);

				/*
				 * If the tuple was already locked by ourselves in a previous
				 * iteration of this (say heap_lock_tuple was forced to
				 * restart the locking loop because of a change in xmax), then
				 * we hold the lock already on this tuple version and we don't
				 * need to do anything; and this is not an error condition
				 * either.  We just need to skip this tuple and continue
				 * locking the next version in the update chain.
				 */
				if (result == TM_SelfModified)
					goto next;

				if (needwait)
				{
					LockBuffer(buf, BUFFER_LOCK_UNLOCK);
					XactLockTableWait(rawxmax, rel, &mytup.t_self,
									  XLTW_LockUpdated);
					goto l4;
				}
				if (result != TM_Ok)
				{
					goto out_locked;
				}
			}
		}

		/* compute the new Xmax and infomask values for the tuple ... */
		compute_new_xmax_infomask(xmax, old_infomask, mytup.t_data->t_infomask2,
								  xid, mode, false,
								  &new_xmax, &new_infomask, &new_infomask2);

		if (PageIsAllVisible(BufferGetPage(buf)) &&
			visibilitymap_clear(rel, block, vmbuffer,
								VISIBILITYMAP_ALL_FROZEN))
			cleared_all_frozen = true;

		START_CRIT_SECTION();

		/* ... and set them */
		HeapTupleHeaderSetXmax(mytup.t_data, new_xmax);
		mytup.t_data->t_infomask &= ~HEAP_XMAX_BITS;
		mytup.t_data->t_infomask2 &= ~HEAP_KEYS_UPDATED;
		mytup.t_data->t_infomask |= new_infomask;
		mytup.t_data->t_infomask2 |= new_infomask2;

		MarkBufferDirty(buf);

		/* XLOG stuff */
		if (RelationNeedsWAL(rel))
		{
			xl_heap_lock_updated xlrec;
			XLogRecPtr	recptr;
			Page		page = BufferGetPage(buf);

			XLogBeginInsert();
			XLogRegisterBuffer(0, buf, REGBUF_STANDARD);

			xlrec.offnum = ItemPointerGetOffsetNumber(&mytup.t_self);
			xlrec.xmax = new_xmax;
			xlrec.infobits_set = compute_infobits(new_infomask, new_infomask2);
			xlrec.flags =
				cleared_all_frozen ? XLH_LOCK_ALL_FROZEN_CLEARED : 0;

			XLogRegisterData((char *) &xlrec, SizeOfHeapLockUpdated);

			recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_LOCK_UPDATED);

			PageSetLSN(page, recptr);
		}

		END_CRIT_SECTION();

next:
		/* if we find the end of update chain, we're done. */
		if (mytup.t_data->t_infomask & HEAP_XMAX_INVALID ||
			HeapTupleHeaderIndicatesMovedPartitions(mytup.t_data) ||
			ItemPointerEquals(&mytup.t_self, &mytup.t_data->t_ctid) ||
			HeapTupleHeaderIsOnlyLocked(mytup.t_data))
		{
			result = TM_Ok;
			goto out_locked;
		}

		/* tail recursion */
		priorXmax = HeapTupleHeaderGetUpdateXid(mytup.t_data);
		ItemPointerCopy(&(mytup.t_data->t_ctid), &tupid);
		UnlockReleaseBuffer(buf);
	}

	result = TM_Ok;

out_locked:
	UnlockReleaseBuffer(buf);

out_unlocked:
	if (vmbuffer != InvalidBuffer)
		ReleaseBuffer(vmbuffer);

	return result;
}