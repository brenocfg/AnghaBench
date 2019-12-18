#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xlrec ;
struct TYPE_4__ {int force; scalar_t__ node_id; scalar_t__ remote_lsn; } ;
typedef  TYPE_1__ xl_replorigin_set ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_5__ {scalar_t__ roident; scalar_t__ acquired_by; scalar_t__ remote_lsn; scalar_t__ local_lsn; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ ReplicationState ;
typedef  scalar_t__ RepOriginId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DoNotReplicateId ; 
 int /*<<< orphan*/  ERRCODE_CONFIGURATION_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidRepOriginId ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  RM_REPLORIGIN_ID ; 
 int /*<<< orphan*/ * ReplicationOriginLock ; 
 int /*<<< orphan*/  XLOG_REPLORIGIN_SET ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,...) ; 
 int max_replication_slots ; 
 TYPE_2__* replication_states ; 

void
replorigin_advance(RepOriginId node,
				   XLogRecPtr remote_commit, XLogRecPtr local_commit,
				   bool go_backward, bool wal_log)
{
	int			i;
	ReplicationState *replication_state = NULL;
	ReplicationState *free_state = NULL;

	Assert(node != InvalidRepOriginId);

	/* we don't track DoNotReplicateId */
	if (node == DoNotReplicateId)
		return;

	/*
	 * XXX: For the case where this is called by WAL replay, it'd be more
	 * efficient to restore into a backend local hashtable and only dump into
	 * shmem after recovery is finished. Let's wait with implementing that
	 * till it's shown to be a measurable expense
	 */

	/* Lock exclusively, as we may have to create a new table entry. */
	LWLockAcquire(ReplicationOriginLock, LW_EXCLUSIVE);

	/*
	 * Search for either an existing slot for the origin, or a free one we can
	 * use.
	 */
	for (i = 0; i < max_replication_slots; i++)
	{
		ReplicationState *curstate = &replication_states[i];

		/* remember where to insert if necessary */
		if (curstate->roident == InvalidRepOriginId &&
			free_state == NULL)
		{
			free_state = curstate;
			continue;
		}

		/* not our slot */
		if (curstate->roident != node)
		{
			continue;
		}

		/* ok, found slot */
		replication_state = curstate;

		LWLockAcquire(&replication_state->lock, LW_EXCLUSIVE);

		/* Make sure it's not used by somebody else */
		if (replication_state->acquired_by != 0)
		{
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_IN_USE),
					 errmsg("replication origin with OID %d is already active for PID %d",
							replication_state->roident,
							replication_state->acquired_by)));
		}

		break;
	}

	if (replication_state == NULL && free_state == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_CONFIGURATION_LIMIT_EXCEEDED),
				 errmsg("could not find free replication state slot for replication origin with OID %u",
						node),
				 errhint("Increase max_replication_slots and try again.")));

	if (replication_state == NULL)
	{
		/* initialize new slot */
		LWLockAcquire(&free_state->lock, LW_EXCLUSIVE);
		replication_state = free_state;
		Assert(replication_state->remote_lsn == InvalidXLogRecPtr);
		Assert(replication_state->local_lsn == InvalidXLogRecPtr);
		replication_state->roident = node;
	}

	Assert(replication_state->roident != InvalidRepOriginId);

	/*
	 * If somebody "forcefully" sets this slot, WAL log it, so it's durable
	 * and the standby gets the message. Primarily this will be called during
	 * WAL replay (of commit records) where no WAL logging is necessary.
	 */
	if (wal_log)
	{
		xl_replorigin_set xlrec;

		xlrec.remote_lsn = remote_commit;
		xlrec.node_id = node;
		xlrec.force = go_backward;

		XLogBeginInsert();
		XLogRegisterData((char *) (&xlrec), sizeof(xlrec));

		XLogInsert(RM_REPLORIGIN_ID, XLOG_REPLORIGIN_SET);
	}

	/*
	 * Due to - harmless - race conditions during a checkpoint we could see
	 * values here that are older than the ones we already have in memory.
	 * Don't overwrite those.
	 */
	if (go_backward || replication_state->remote_lsn < remote_commit)
		replication_state->remote_lsn = remote_commit;
	if (local_commit != InvalidXLogRecPtr &&
		(go_backward || replication_state->local_lsn < local_commit))
		replication_state->local_lsn = local_commit;
	LWLockRelease(&replication_state->lock);

	/*
	 * Release *after* changing the LSNs, slot isn't acquired and thus could
	 * otherwise be dropped anytime.
	 */
	LWLockRelease(ReplicationOriginLock);
}