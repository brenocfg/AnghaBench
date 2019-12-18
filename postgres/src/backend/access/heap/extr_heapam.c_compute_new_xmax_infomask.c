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
typedef  int uint16 ;
typedef  scalar_t__ TransactionId ;
typedef  int /*<<< orphan*/  MultiXactStatus ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int LockTupleMode ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetMultiXactIdHintBits (scalar_t__,int*,int*) ; 
 int HEAP_KEYS_UPDATED ; 
 scalar_t__ HEAP_LOCKED_UPGRADED (int) ; 
 int HEAP_XMAX_COMMITTED ; 
 int HEAP_XMAX_EXCL_LOCK ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_EXCL_LOCKED (int) ; 
 scalar_t__ HEAP_XMAX_IS_KEYSHR_LOCKED (int) ; 
 int HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 scalar_t__ HEAP_XMAX_IS_SHR_LOCKED (int) ; 
 int HEAP_XMAX_KEYSHR_LOCK ; 
 int HEAP_XMAX_LOCK_ONLY ; 
 int HEAP_XMAX_SHR_LOCK ; 
 scalar_t__ InvalidTransactionId ; 
#define  LockTupleExclusive 131 
#define  LockTupleKeyShare 130 
#define  LockTupleNoKeyExclusive 129 
#define  LockTupleShare 128 
 scalar_t__ MultiXactIdCreate (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MultiXactIdExpand (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MultiXactIdGetUpdateXid (scalar_t__,int) ; 
 int /*<<< orphan*/  MultiXactIdIsRunning (scalar_t__,int) ; 
 int /*<<< orphan*/  MultiXactStatusForKeyShare ; 
 int /*<<< orphan*/  MultiXactStatusForNoKeyUpdate ; 
 int /*<<< orphan*/  MultiXactStatusForShare ; 
 int /*<<< orphan*/  MultiXactStatusForUpdate ; 
 int /*<<< orphan*/  MultiXactStatusNoKeyUpdate ; 
 int /*<<< orphan*/  MultiXactStatusUpdate ; 
 int TUPLOCK_from_mxstatus (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidCommit (scalar_t__) ; 
 int TransactionIdIsCurrentTransactionId (scalar_t__) ; 
 scalar_t__ TransactionIdIsInProgress (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_mxact_status_for_lock (int,int) ; 

__attribute__((used)) static void
compute_new_xmax_infomask(TransactionId xmax, uint16 old_infomask,
						  uint16 old_infomask2, TransactionId add_to_xmax,
						  LockTupleMode mode, bool is_update,
						  TransactionId *result_xmax, uint16 *result_infomask,
						  uint16 *result_infomask2)
{
	TransactionId new_xmax;
	uint16		new_infomask,
				new_infomask2;

	Assert(TransactionIdIsCurrentTransactionId(add_to_xmax));

l5:
	new_infomask = 0;
	new_infomask2 = 0;
	if (old_infomask & HEAP_XMAX_INVALID)
	{
		/*
		 * No previous locker; we just insert our own TransactionId.
		 *
		 * Note that it's critical that this case be the first one checked,
		 * because there are several blocks below that come back to this one
		 * to implement certain optimizations; old_infomask might contain
		 * other dirty bits in those cases, but we don't really care.
		 */
		if (is_update)
		{
			new_xmax = add_to_xmax;
			if (mode == LockTupleExclusive)
				new_infomask2 |= HEAP_KEYS_UPDATED;
		}
		else
		{
			new_infomask |= HEAP_XMAX_LOCK_ONLY;
			switch (mode)
			{
				case LockTupleKeyShare:
					new_xmax = add_to_xmax;
					new_infomask |= HEAP_XMAX_KEYSHR_LOCK;
					break;
				case LockTupleShare:
					new_xmax = add_to_xmax;
					new_infomask |= HEAP_XMAX_SHR_LOCK;
					break;
				case LockTupleNoKeyExclusive:
					new_xmax = add_to_xmax;
					new_infomask |= HEAP_XMAX_EXCL_LOCK;
					break;
				case LockTupleExclusive:
					new_xmax = add_to_xmax;
					new_infomask |= HEAP_XMAX_EXCL_LOCK;
					new_infomask2 |= HEAP_KEYS_UPDATED;
					break;
				default:
					new_xmax = InvalidTransactionId;	/* silence compiler */
					elog(ERROR, "invalid lock mode");
			}
		}
	}
	else if (old_infomask & HEAP_XMAX_IS_MULTI)
	{
		MultiXactStatus new_status;

		/*
		 * Currently we don't allow XMAX_COMMITTED to be set for multis, so
		 * cross-check.
		 */
		Assert(!(old_infomask & HEAP_XMAX_COMMITTED));

		/*
		 * A multixact together with LOCK_ONLY set but neither lock bit set
		 * (i.e. a pg_upgraded share locked tuple) cannot possibly be running
		 * anymore.  This check is critical for databases upgraded by
		 * pg_upgrade; both MultiXactIdIsRunning and MultiXactIdExpand assume
		 * that such multis are never passed.
		 */
		if (HEAP_LOCKED_UPGRADED(old_infomask))
		{
			old_infomask &= ~HEAP_XMAX_IS_MULTI;
			old_infomask |= HEAP_XMAX_INVALID;
			goto l5;
		}

		/*
		 * If the XMAX is already a MultiXactId, then we need to expand it to
		 * include add_to_xmax; but if all the members were lockers and are
		 * all gone, we can do away with the IS_MULTI bit and just set
		 * add_to_xmax as the only locker/updater.  If all lockers are gone
		 * and we have an updater that aborted, we can also do without a
		 * multi.
		 *
		 * The cost of doing GetMultiXactIdMembers would be paid by
		 * MultiXactIdExpand if we weren't to do this, so this check is not
		 * incurring extra work anyhow.
		 */
		if (!MultiXactIdIsRunning(xmax, HEAP_XMAX_IS_LOCKED_ONLY(old_infomask)))
		{
			if (HEAP_XMAX_IS_LOCKED_ONLY(old_infomask) ||
				!TransactionIdDidCommit(MultiXactIdGetUpdateXid(xmax,
																old_infomask)))
			{
				/*
				 * Reset these bits and restart; otherwise fall through to
				 * create a new multi below.
				 */
				old_infomask &= ~HEAP_XMAX_IS_MULTI;
				old_infomask |= HEAP_XMAX_INVALID;
				goto l5;
			}
		}

		new_status = get_mxact_status_for_lock(mode, is_update);

		new_xmax = MultiXactIdExpand((MultiXactId) xmax, add_to_xmax,
									 new_status);
		GetMultiXactIdHintBits(new_xmax, &new_infomask, &new_infomask2);
	}
	else if (old_infomask & HEAP_XMAX_COMMITTED)
	{
		/*
		 * It's a committed update, so we need to preserve him as updater of
		 * the tuple.
		 */
		MultiXactStatus status;
		MultiXactStatus new_status;

		if (old_infomask2 & HEAP_KEYS_UPDATED)
			status = MultiXactStatusUpdate;
		else
			status = MultiXactStatusNoKeyUpdate;

		new_status = get_mxact_status_for_lock(mode, is_update);

		/*
		 * since it's not running, it's obviously impossible for the old
		 * updater to be identical to the current one, so we need not check
		 * for that case as we do in the block above.
		 */
		new_xmax = MultiXactIdCreate(xmax, status, add_to_xmax, new_status);
		GetMultiXactIdHintBits(new_xmax, &new_infomask, &new_infomask2);
	}
	else if (TransactionIdIsInProgress(xmax))
	{
		/*
		 * If the XMAX is a valid, in-progress TransactionId, then we need to
		 * create a new MultiXactId that includes both the old locker or
		 * updater and our own TransactionId.
		 */
		MultiXactStatus new_status;
		MultiXactStatus old_status;
		LockTupleMode old_mode;

		if (HEAP_XMAX_IS_LOCKED_ONLY(old_infomask))
		{
			if (HEAP_XMAX_IS_KEYSHR_LOCKED(old_infomask))
				old_status = MultiXactStatusForKeyShare;
			else if (HEAP_XMAX_IS_SHR_LOCKED(old_infomask))
				old_status = MultiXactStatusForShare;
			else if (HEAP_XMAX_IS_EXCL_LOCKED(old_infomask))
			{
				if (old_infomask2 & HEAP_KEYS_UPDATED)
					old_status = MultiXactStatusForUpdate;
				else
					old_status = MultiXactStatusForNoKeyUpdate;
			}
			else
			{
				/*
				 * LOCK_ONLY can be present alone only when a page has been
				 * upgraded by pg_upgrade.  But in that case,
				 * TransactionIdIsInProgress() should have returned false.  We
				 * assume it's no longer locked in this case.
				 */
				elog(WARNING, "LOCK_ONLY found for Xid in progress %u", xmax);
				old_infomask |= HEAP_XMAX_INVALID;
				old_infomask &= ~HEAP_XMAX_LOCK_ONLY;
				goto l5;
			}
		}
		else
		{
			/* it's an update, but which kind? */
			if (old_infomask2 & HEAP_KEYS_UPDATED)
				old_status = MultiXactStatusUpdate;
			else
				old_status = MultiXactStatusNoKeyUpdate;
		}

		old_mode = TUPLOCK_from_mxstatus(old_status);

		/*
		 * If the lock to be acquired is for the same TransactionId as the
		 * existing lock, there's an optimization possible: consider only the
		 * strongest of both locks as the only one present, and restart.
		 */
		if (xmax == add_to_xmax)
		{
			/*
			 * Note that it's not possible for the original tuple to be
			 * updated: we wouldn't be here because the tuple would have been
			 * invisible and we wouldn't try to update it.  As a subtlety,
			 * this code can also run when traversing an update chain to lock
			 * future versions of a tuple.  But we wouldn't be here either,
			 * because the add_to_xmax would be different from the original
			 * updater.
			 */
			Assert(HEAP_XMAX_IS_LOCKED_ONLY(old_infomask));

			/* acquire the strongest of both */
			if (mode < old_mode)
				mode = old_mode;
			/* mustn't touch is_update */

			old_infomask |= HEAP_XMAX_INVALID;
			goto l5;
		}

		/* otherwise, just fall back to creating a new multixact */
		new_status = get_mxact_status_for_lock(mode, is_update);
		new_xmax = MultiXactIdCreate(xmax, old_status,
									 add_to_xmax, new_status);
		GetMultiXactIdHintBits(new_xmax, &new_infomask, &new_infomask2);
	}
	else if (!HEAP_XMAX_IS_LOCKED_ONLY(old_infomask) &&
			 TransactionIdDidCommit(xmax))
	{
		/*
		 * It's a committed update, so we gotta preserve him as updater of the
		 * tuple.
		 */
		MultiXactStatus status;
		MultiXactStatus new_status;

		if (old_infomask2 & HEAP_KEYS_UPDATED)
			status = MultiXactStatusUpdate;
		else
			status = MultiXactStatusNoKeyUpdate;

		new_status = get_mxact_status_for_lock(mode, is_update);

		/*
		 * since it's not running, it's obviously impossible for the old
		 * updater to be identical to the current one, so we need not check
		 * for that case as we do in the block above.
		 */
		new_xmax = MultiXactIdCreate(xmax, status, add_to_xmax, new_status);
		GetMultiXactIdHintBits(new_xmax, &new_infomask, &new_infomask2);
	}
	else
	{
		/*
		 * Can get here iff the locking/updating transaction was running when
		 * the infomask was extracted from the tuple, but finished before
		 * TransactionIdIsInProgress got to run.  Deal with it as if there was
		 * no locker at all in the first place.
		 */
		old_infomask |= HEAP_XMAX_INVALID;
		goto l5;
	}

	*result_infomask = new_infomask;
	*result_infomask2 = new_infomask2;
	*result_xmax = new_xmax;
}