#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_6__ {int /*<<< orphan*/  xid; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int FRM_INVALIDATE_XMAX ; 
 int FRM_MARK_COMMITTED ; 
 int FRM_NOOP ; 
 int FRM_RETURN_IS_MULTI ; 
 int FRM_RETURN_IS_XID ; 
 int GetMultiXactIdMembers (int /*<<< orphan*/ ,TYPE_1__**,int,scalar_t__) ; 
 scalar_t__ HEAP_LOCKED_UPGRADED (int) ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 scalar_t__ ISUPDATE_from_mxstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  MultiXactIdCreateFromMembers (int,TYPE_1__*) ; 
 int /*<<< orphan*/  MultiXactIdGetUpdateXid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MultiXactIdIsRunning (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MultiXactIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ MultiXactIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static TransactionId
FreezeMultiXactId(MultiXactId multi, uint16 t_infomask,
				  TransactionId relfrozenxid, TransactionId relminmxid,
				  TransactionId cutoff_xid, MultiXactId cutoff_multi,
				  uint16 *flags)
{
	TransactionId xid = InvalidTransactionId;
	int			i;
	MultiXactMember *members;
	int			nmembers;
	bool		need_replace;
	int			nnewmembers;
	MultiXactMember *newmembers;
	bool		has_lockers;
	TransactionId update_xid;
	bool		update_committed;

	*flags = 0;

	/* We should only be called in Multis */
	Assert(t_infomask & HEAP_XMAX_IS_MULTI);

	if (!MultiXactIdIsValid(multi) ||
		HEAP_LOCKED_UPGRADED(t_infomask))
	{
		/* Ensure infomask bits are appropriately set/reset */
		*flags |= FRM_INVALIDATE_XMAX;
		return InvalidTransactionId;
	}
	else if (MultiXactIdPrecedes(multi, relminmxid))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg_internal("found multixact %u from before relminmxid %u",
								 multi, relminmxid)));
	else if (MultiXactIdPrecedes(multi, cutoff_multi))
	{
		/*
		 * This old multi cannot possibly have members still running, but
		 * verify just in case.  If it was a locker only, it can be removed
		 * without any further consideration; but if it contained an update,
		 * we might need to preserve it.
		 */
		if (MultiXactIdIsRunning(multi,
								 HEAP_XMAX_IS_LOCKED_ONLY(t_infomask)))
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg_internal("multixact %u from before cutoff %u found to be still running",
									 multi, cutoff_multi)));

		if (HEAP_XMAX_IS_LOCKED_ONLY(t_infomask))
		{
			*flags |= FRM_INVALIDATE_XMAX;
			xid = InvalidTransactionId; /* not strictly necessary */
		}
		else
		{
			/* replace multi by update xid */
			xid = MultiXactIdGetUpdateXid(multi, t_infomask);

			/* wasn't only a lock, xid needs to be valid */
			Assert(TransactionIdIsValid(xid));

			if (TransactionIdPrecedes(xid, relfrozenxid))
				ereport(ERROR,
						(errcode(ERRCODE_DATA_CORRUPTED),
						 errmsg_internal("found update xid %u from before relfrozenxid %u",
										 xid, relfrozenxid)));

			/*
			 * If the xid is older than the cutoff, it has to have aborted,
			 * otherwise the tuple would have gotten pruned away.
			 */
			if (TransactionIdPrecedes(xid, cutoff_xid))
			{
				if (TransactionIdDidCommit(xid))
					ereport(ERROR,
							(errcode(ERRCODE_DATA_CORRUPTED),
							 errmsg_internal("cannot freeze committed update xid %u", xid)));
				*flags |= FRM_INVALIDATE_XMAX;
				xid = InvalidTransactionId; /* not strictly necessary */
			}
			else
			{
				*flags |= FRM_RETURN_IS_XID;
			}
		}

		return xid;
	}

	/*
	 * This multixact might have or might not have members still running, but
	 * we know it's valid and is newer than the cutoff point for multis.
	 * However, some member(s) of it may be below the cutoff for Xids, so we
	 * need to walk the whole members array to figure out what to do, if
	 * anything.
	 */

	nmembers =
		GetMultiXactIdMembers(multi, &members, false,
							  HEAP_XMAX_IS_LOCKED_ONLY(t_infomask));
	if (nmembers <= 0)
	{
		/* Nothing worth keeping */
		*flags |= FRM_INVALIDATE_XMAX;
		return InvalidTransactionId;
	}

	/* is there anything older than the cutoff? */
	need_replace = false;
	for (i = 0; i < nmembers; i++)
	{
		if (TransactionIdPrecedes(members[i].xid, cutoff_xid))
		{
			need_replace = true;
			break;
		}
	}

	/*
	 * In the simplest case, there is no member older than the cutoff; we can
	 * keep the existing MultiXactId as is.
	 */
	if (!need_replace)
	{
		*flags |= FRM_NOOP;
		pfree(members);
		return InvalidTransactionId;
	}

	/*
	 * If the multi needs to be updated, figure out which members do we need
	 * to keep.
	 */
	nnewmembers = 0;
	newmembers = palloc(sizeof(MultiXactMember) * nmembers);
	has_lockers = false;
	update_xid = InvalidTransactionId;
	update_committed = false;

	for (i = 0; i < nmembers; i++)
	{
		/*
		 * Determine whether to keep this member or ignore it.
		 */
		if (ISUPDATE_from_mxstatus(members[i].status))
		{
			TransactionId xid = members[i].xid;

			Assert(TransactionIdIsValid(xid));
			if (TransactionIdPrecedes(xid, relfrozenxid))
				ereport(ERROR,
						(errcode(ERRCODE_DATA_CORRUPTED),
						 errmsg_internal("found update xid %u from before relfrozenxid %u",
										 xid, relfrozenxid)));

			/*
			 * It's an update; should we keep it?  If the transaction is known
			 * aborted or crashed then it's okay to ignore it, otherwise not.
			 * Note that an updater older than cutoff_xid cannot possibly be
			 * committed, because HeapTupleSatisfiesVacuum would have returned
			 * HEAPTUPLE_DEAD and we would not be trying to freeze the tuple.
			 *
			 * As with all tuple visibility routines, it's critical to test
			 * TransactionIdIsInProgress before TransactionIdDidCommit,
			 * because of race conditions explained in detail in
			 * heapam_visibility.c.
			 */
			if (TransactionIdIsCurrentTransactionId(xid) ||
				TransactionIdIsInProgress(xid))
			{
				Assert(!TransactionIdIsValid(update_xid));
				update_xid = xid;
			}
			else if (TransactionIdDidCommit(xid))
			{
				/*
				 * The transaction committed, so we can tell caller to set
				 * HEAP_XMAX_COMMITTED.  (We can only do this because we know
				 * the transaction is not running.)
				 */
				Assert(!TransactionIdIsValid(update_xid));
				update_committed = true;
				update_xid = xid;
			}
			else
			{
				/*
				 * Not in progress, not committed -- must be aborted or
				 * crashed; we can ignore it.
				 */
			}

			/*
			 * Since the tuple wasn't marked HEAPTUPLE_DEAD by vacuum, the
			 * update Xid cannot possibly be older than the xid cutoff. The
			 * presence of such a tuple would cause corruption, so be paranoid
			 * and check.
			 */
			if (TransactionIdIsValid(update_xid) &&
				TransactionIdPrecedes(update_xid, cutoff_xid))
				ereport(ERROR,
						(errcode(ERRCODE_DATA_CORRUPTED),
						 errmsg_internal("found update xid %u from before xid cutoff %u",
										 update_xid, cutoff_xid)));

			/*
			 * If we determined that it's an Xid corresponding to an update
			 * that must be retained, additionally add it to the list of
			 * members of the new Multi, in case we end up using that.  (We
			 * might still decide to use only an update Xid and not a multi,
			 * but it's easier to maintain the list as we walk the old members
			 * list.)
			 */
			if (TransactionIdIsValid(update_xid))
				newmembers[nnewmembers++] = members[i];
		}
		else
		{
			/* We only keep lockers if they are still running */
			if (TransactionIdIsCurrentTransactionId(members[i].xid) ||
				TransactionIdIsInProgress(members[i].xid))
			{
				/* running locker cannot possibly be older than the cutoff */
				Assert(!TransactionIdPrecedes(members[i].xid, cutoff_xid));
				newmembers[nnewmembers++] = members[i];
				has_lockers = true;
			}
		}
	}

	pfree(members);

	if (nnewmembers == 0)
	{
		/* nothing worth keeping!? Tell caller to remove the whole thing */
		*flags |= FRM_INVALIDATE_XMAX;
		xid = InvalidTransactionId;
	}
	else if (TransactionIdIsValid(update_xid) && !has_lockers)
	{
		/*
		 * If there's a single member and it's an update, pass it back alone
		 * without creating a new Multi.  (XXX we could do this when there's a
		 * single remaining locker, too, but that would complicate the API too
		 * much; moreover, the case with the single updater is more
		 * interesting, because those are longer-lived.)
		 */
		Assert(nnewmembers == 1);
		*flags |= FRM_RETURN_IS_XID;
		if (update_committed)
			*flags |= FRM_MARK_COMMITTED;
		xid = update_xid;
	}
	else
	{
		/*
		 * Create a new multixact with the surviving members of the previous
		 * one, to set as new Xmax in the tuple.
		 */
		xid = MultiXactIdCreateFromMembers(nnewmembers, newmembers);
		*flags |= FRM_RETURN_IS_MULTI;
	}

	pfree(newmembers);

	return xid;
}