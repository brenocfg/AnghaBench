#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xlrec ;
struct TYPE_8__ {scalar_t__ node_id; } ;
typedef  TYPE_1__ xl_replorigin_drop ;
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_9__ {scalar_t__ roident; scalar_t__ acquired_by; void* local_lsn; void* remote_lsn; int /*<<< orphan*/  origin_cv; } ;
typedef  TYPE_2__ ReplicationState ;
typedef  scalar_t__ RepOriginId ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_3__* HeapTuple ;
typedef  int /*<<< orphan*/  ConditionVariable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  ConditionVariableSleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ InvalidRepOriginId ; 
 void* InvalidXLogRecPtr ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  REPLORIGIDENT ; 
 int /*<<< orphan*/  RM_REPLORIGIN_ID ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_3__*) ; 
 int /*<<< orphan*/  ReplicationOriginLock ; 
 int /*<<< orphan*/  ReplicationOriginRelationId ; 
 TYPE_3__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_REPLICATION_ORIGIN_DROP ; 
 int /*<<< orphan*/  XLOG_REPLORIGIN_DROP ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,scalar_t__) ; 
 int max_replication_slots ; 
 TYPE_2__* replication_states ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
replorigin_drop(RepOriginId roident, bool nowait)
{
	HeapTuple	tuple;
	Relation	rel;
	int			i;

	Assert(IsTransactionState());

	/*
	 * To interlock against concurrent drops, we hold ExclusiveLock on
	 * pg_replication_origin throughout this function.
	 */
	rel = table_open(ReplicationOriginRelationId, ExclusiveLock);

	/*
	 * First, clean up the slot state info, if there is any matching slot.
	 */
restart:
	tuple = NULL;
	LWLockAcquire(ReplicationOriginLock, LW_EXCLUSIVE);

	for (i = 0; i < max_replication_slots; i++)
	{
		ReplicationState *state = &replication_states[i];

		if (state->roident == roident)
		{
			/* found our slot, is it busy? */
			if (state->acquired_by != 0)
			{
				ConditionVariable *cv;

				if (nowait)
					ereport(ERROR,
							(errcode(ERRCODE_OBJECT_IN_USE),
							 errmsg("could not drop replication origin with OID %d, in use by PID %d",
									state->roident,
									state->acquired_by)));

				/*
				 * We must wait and then retry.  Since we don't know which CV
				 * to wait on until here, we can't readily use
				 * ConditionVariablePrepareToSleep (calling it here would be
				 * wrong, since we could miss the signal if we did so); just
				 * use ConditionVariableSleep directly.
				 */
				cv = &state->origin_cv;

				LWLockRelease(ReplicationOriginLock);

				ConditionVariableSleep(cv, WAIT_EVENT_REPLICATION_ORIGIN_DROP);
				goto restart;
			}

			/* first make a WAL log entry */
			{
				xl_replorigin_drop xlrec;

				xlrec.node_id = roident;
				XLogBeginInsert();
				XLogRegisterData((char *) (&xlrec), sizeof(xlrec));
				XLogInsert(RM_REPLORIGIN_ID, XLOG_REPLORIGIN_DROP);
			}

			/* then clear the in-memory slot */
			state->roident = InvalidRepOriginId;
			state->remote_lsn = InvalidXLogRecPtr;
			state->local_lsn = InvalidXLogRecPtr;
			break;
		}
	}
	LWLockRelease(ReplicationOriginLock);
	ConditionVariableCancelSleep();

	/*
	 * Now, we can delete the catalog entry.
	 */
	tuple = SearchSysCache1(REPLORIGIDENT, ObjectIdGetDatum(roident));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for replication origin with oid %u",
			 roident);

	CatalogTupleDelete(rel, &tuple->t_self);
	ReleaseSysCache(tuple);

	CommandCounterIncrement();

	/* now release lock again */
	table_close(rel, ExclusiveLock);
}