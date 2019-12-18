#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_23__ {int /*<<< orphan*/  tts_tableOid; } ;
typedef  TYPE_2__ TupleTableSlot ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_26__ {int /*<<< orphan*/  t_tableOid; TYPE_15__* t_data; void* t_self; } ;
struct TYPE_22__ {TYPE_5__ tupdata; } ;
struct TYPE_27__ {TYPE_1__ base; } ;
struct TYPE_25__ {int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
struct TYPE_24__ {int traversed; scalar_t__ cmax; int /*<<< orphan*/  xmax; void* ctid; } ;
struct TYPE_21__ {void* t_ctid; } ;
typedef  scalar_t__ TM_Result ;
typedef  TYPE_3__ TM_FailureData ;
typedef  TYPE_4__ SnapshotData ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  LockWaitPolicy ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  void** ItemPointer ;
typedef  TYPE_5__* HeapTuple ;
typedef  scalar_t__ CommandId ;
typedef  TYPE_6__ BufferHeapTupleTableSlot ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionalXactLockTableWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERRCODE_LOCK_NOT_AVAILABLE ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecStorePinnedBufferHeapTuple (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleHeaderGetCmin (TYPE_15__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_15__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (TYPE_15__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderIsSpeculative (TYPE_15__*) ; 
 int /*<<< orphan*/  InitDirtySnapshot (TYPE_4__) ; 
 scalar_t__ ItemPointerEquals (void**,void**) ; 
 scalar_t__ ItemPointerIndicatesMovedPartitions (void**) ; 
#define  LockWaitBlock 130 
#define  LockWaitError 129 
#define  LockWaitSkip 128 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ TM_Deleted ; 
 scalar_t__ TM_SelfModified ; 
 scalar_t__ TM_Updated ; 
 scalar_t__ TM_WouldBlock ; 
 int TTS_IS_BUFFERTUPLE (TYPE_2__*) ; 
 int TUPLE_LOCK_FLAG_FIND_LAST_VERSION ; 
 int TUPLE_LOCK_FLAG_LOCK_UPDATE_IN_PROGRESS ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLTW_FetchUpdated ; 
 int /*<<< orphan*/  XactLockTableWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 scalar_t__ heap_fetch (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ heap_lock_tuple (int /*<<< orphan*/ ,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static TM_Result
heapam_tuple_lock(Relation relation, ItemPointer tid, Snapshot snapshot,
				  TupleTableSlot *slot, CommandId cid, LockTupleMode mode,
				  LockWaitPolicy wait_policy, uint8 flags,
				  TM_FailureData *tmfd)
{
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;
	TM_Result	result;
	Buffer		buffer;
	HeapTuple	tuple = &bslot->base.tupdata;
	bool		follow_updates;

	follow_updates = (flags & TUPLE_LOCK_FLAG_LOCK_UPDATE_IN_PROGRESS) != 0;
	tmfd->traversed = false;

	Assert(TTS_IS_BUFFERTUPLE(slot));

tuple_lock_retry:
	tuple->t_self = *tid;
	result = heap_lock_tuple(relation, tuple, cid, mode, wait_policy,
							 follow_updates, &buffer, tmfd);

	if (result == TM_Updated &&
		(flags & TUPLE_LOCK_FLAG_FIND_LAST_VERSION))
	{
		ReleaseBuffer(buffer);
		/* Should not encounter speculative tuple on recheck */
		Assert(!HeapTupleHeaderIsSpeculative(tuple->t_data));

		if (!ItemPointerEquals(&tmfd->ctid, &tuple->t_self))
		{
			SnapshotData SnapshotDirty;
			TransactionId priorXmax;

			/* it was updated, so look at the updated version */
			*tid = tmfd->ctid;
			/* updated row should have xmin matching this xmax */
			priorXmax = tmfd->xmax;

			/* signal that a tuple later in the chain is getting locked */
			tmfd->traversed = true;

			/*
			 * fetch target tuple
			 *
			 * Loop here to deal with updated or busy tuples
			 */
			InitDirtySnapshot(SnapshotDirty);
			for (;;)
			{
				if (ItemPointerIndicatesMovedPartitions(tid))
					ereport(ERROR,
							(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
							 errmsg("tuple to be locked was already moved to another partition due to concurrent update")));

				tuple->t_self = *tid;
				if (heap_fetch(relation, &SnapshotDirty, tuple, &buffer))
				{
					/*
					 * If xmin isn't what we're expecting, the slot must have
					 * been recycled and reused for an unrelated tuple.  This
					 * implies that the latest version of the row was deleted,
					 * so we need do nothing.  (Should be safe to examine xmin
					 * without getting buffer's content lock.  We assume
					 * reading a TransactionId to be atomic, and Xmin never
					 * changes in an existing tuple, except to invalid or
					 * frozen, and neither of those can match priorXmax.)
					 */
					if (!TransactionIdEquals(HeapTupleHeaderGetXmin(tuple->t_data),
											 priorXmax))
					{
						ReleaseBuffer(buffer);
						return TM_Deleted;
					}

					/* otherwise xmin should not be dirty... */
					if (TransactionIdIsValid(SnapshotDirty.xmin))
						ereport(ERROR,
								(errcode(ERRCODE_DATA_CORRUPTED),
								 errmsg_internal("t_xmin is uncommitted in tuple to be updated")));

					/*
					 * If tuple is being updated by other transaction then we
					 * have to wait for its commit/abort, or die trying.
					 */
					if (TransactionIdIsValid(SnapshotDirty.xmax))
					{
						ReleaseBuffer(buffer);
						switch (wait_policy)
						{
							case LockWaitBlock:
								XactLockTableWait(SnapshotDirty.xmax,
												  relation, &tuple->t_self,
												  XLTW_FetchUpdated);
								break;
							case LockWaitSkip:
								if (!ConditionalXactLockTableWait(SnapshotDirty.xmax))
									/* skip instead of waiting */
									return TM_WouldBlock;
								break;
							case LockWaitError:
								if (!ConditionalXactLockTableWait(SnapshotDirty.xmax))
									ereport(ERROR,
											(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
											 errmsg("could not obtain lock on row in relation \"%s\"",
													RelationGetRelationName(relation))));
								break;
						}
						continue;	/* loop back to repeat heap_fetch */
					}

					/*
					 * If tuple was inserted by our own transaction, we have
					 * to check cmin against cid: cmin >= current CID means
					 * our command cannot see the tuple, so we should ignore
					 * it. Otherwise heap_lock_tuple() will throw an error,
					 * and so would any later attempt to update or delete the
					 * tuple.  (We need not check cmax because
					 * HeapTupleSatisfiesDirty will consider a tuple deleted
					 * by our transaction dead, regardless of cmax.)  We just
					 * checked that priorXmax == xmin, so we can test that
					 * variable instead of doing HeapTupleHeaderGetXmin again.
					 */
					if (TransactionIdIsCurrentTransactionId(priorXmax) &&
						HeapTupleHeaderGetCmin(tuple->t_data) >= cid)
					{
						tmfd->xmax = priorXmax;

						/*
						 * Cmin is the problematic value, so store that. See
						 * above.
						 */
						tmfd->cmax = HeapTupleHeaderGetCmin(tuple->t_data);
						ReleaseBuffer(buffer);
						return TM_SelfModified;
					}

					/*
					 * This is a live tuple, so try to lock it again.
					 */
					ReleaseBuffer(buffer);
					goto tuple_lock_retry;
				}

				/*
				 * If the referenced slot was actually empty, the latest
				 * version of the row must have been deleted, so we need do
				 * nothing.
				 */
				if (tuple->t_data == NULL)
				{
					return TM_Deleted;
				}

				/*
				 * As above, if xmin isn't what we're expecting, do nothing.
				 */
				if (!TransactionIdEquals(HeapTupleHeaderGetXmin(tuple->t_data),
										 priorXmax))
				{
					if (BufferIsValid(buffer))
						ReleaseBuffer(buffer);
					return TM_Deleted;
				}

				/*
				 * If we get here, the tuple was found but failed
				 * SnapshotDirty. Assuming the xmin is either a committed xact
				 * or our own xact (as it certainly should be if we're trying
				 * to modify the tuple), this must mean that the row was
				 * updated or deleted by either a committed xact or our own
				 * xact.  If it was deleted, we can ignore it; if it was
				 * updated then chain up to the next version and repeat the
				 * whole process.
				 *
				 * As above, it should be safe to examine xmax and t_ctid
				 * without the buffer content lock, because they can't be
				 * changing.
				 */
				if (ItemPointerEquals(&tuple->t_self, &tuple->t_data->t_ctid))
				{
					/* deleted, so forget about it */
					if (BufferIsValid(buffer))
						ReleaseBuffer(buffer);
					return TM_Deleted;
				}

				/* updated, so look at the updated row */
				*tid = tuple->t_data->t_ctid;
				/* updated row should have xmin matching this xmax */
				priorXmax = HeapTupleHeaderGetUpdateXid(tuple->t_data);
				if (BufferIsValid(buffer))
					ReleaseBuffer(buffer);
				/* loop back to fetch next in chain */
			}
		}
		else
		{
			/* tuple was deleted, so give up */
			return TM_Deleted;
		}
	}

	slot->tts_tableOid = RelationGetRelid(relation);
	tuple->t_tableOid = slot->tts_tableOid;

	/* store in slot, transferring existing pin */
	ExecStorePinnedBufferHeapTuple(tuple, slot, buffer);

	return result;
}