#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ LastSxactCommitSeqNo; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; scalar_t__ prepareSeqNo; int /*<<< orphan*/  inConflicts; } ;
struct TYPE_10__ {int /*<<< orphan*/  inLink; TYPE_2__* sxactOut; } ;
typedef  TYPE_1__* RWConflict ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* InvalidSerializableXact ; 
 int IsolationIsSerializable () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_2__* MySerializableXact ; 
 TYPE_7__* PredXact ; 
 int /*<<< orphan*/  RWConflictData ; 
 scalar_t__ SHMQueueNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SXACT_FLAG_DOOMED ; 
 int /*<<< orphan*/  SXACT_FLAG_PREPARED ; 
 int /*<<< orphan*/  SerializableXactHashLock ; 
 int /*<<< orphan*/  SxactIsCommitted (TYPE_2__*) ; 
 scalar_t__ SxactIsDoomed (TYPE_2__*) ; 
 int /*<<< orphan*/  SxactIsPartiallyReleased (TYPE_2__*) ; 
 scalar_t__ SxactIsPrepared (TYPE_2__*) ; 
 int /*<<< orphan*/  SxactIsReadOnly (TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  inLink ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PreCommit_CheckForSerializationFailure(void)
{
	RWConflict	nearConflict;

	if (MySerializableXact == InvalidSerializableXact)
		return;

	Assert(IsolationIsSerializable());

	LWLockAcquire(SerializableXactHashLock, LW_EXCLUSIVE);

	/* Check if someone else has already decided that we need to die */
	if (SxactIsDoomed(MySerializableXact))
	{
		Assert(!SxactIsPartiallyReleased(MySerializableXact));
		LWLockRelease(SerializableXactHashLock);
		ereport(ERROR,
				(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
				 errmsg("could not serialize access due to read/write dependencies among transactions"),
				 errdetail_internal("Reason code: Canceled on identification as a pivot, during commit attempt."),
				 errhint("The transaction might succeed if retried.")));
	}

	nearConflict = (RWConflict)
		SHMQueueNext(&MySerializableXact->inConflicts,
					 &MySerializableXact->inConflicts,
					 offsetof(RWConflictData, inLink));
	while (nearConflict)
	{
		if (!SxactIsCommitted(nearConflict->sxactOut)
			&& !SxactIsDoomed(nearConflict->sxactOut))
		{
			RWConflict	farConflict;

			farConflict = (RWConflict)
				SHMQueueNext(&nearConflict->sxactOut->inConflicts,
							 &nearConflict->sxactOut->inConflicts,
							 offsetof(RWConflictData, inLink));
			while (farConflict)
			{
				if (farConflict->sxactOut == MySerializableXact
					|| (!SxactIsCommitted(farConflict->sxactOut)
						&& !SxactIsReadOnly(farConflict->sxactOut)
						&& !SxactIsDoomed(farConflict->sxactOut)))
				{
					/*
					 * Normally, we kill the pivot transaction to make sure we
					 * make progress if the failing transaction is retried.
					 * However, we can't kill it if it's already prepared, so
					 * in that case we commit suicide instead.
					 */
					if (SxactIsPrepared(nearConflict->sxactOut))
					{
						LWLockRelease(SerializableXactHashLock);
						ereport(ERROR,
								(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
								 errmsg("could not serialize access due to read/write dependencies among transactions"),
								 errdetail_internal("Reason code: Canceled on commit attempt with conflict in from prepared pivot."),
								 errhint("The transaction might succeed if retried.")));
					}
					nearConflict->sxactOut->flags |= SXACT_FLAG_DOOMED;
					break;
				}
				farConflict = (RWConflict)
					SHMQueueNext(&nearConflict->sxactOut->inConflicts,
								 &farConflict->inLink,
								 offsetof(RWConflictData, inLink));
			}
		}

		nearConflict = (RWConflict)
			SHMQueueNext(&MySerializableXact->inConflicts,
						 &nearConflict->inLink,
						 offsetof(RWConflictData, inLink));
	}

	MySerializableXact->prepareSeqNo = ++(PredXact->LastSxactCommitSeqNo);
	MySerializableXact->flags |= SXACT_FLAG_PREPARED;

	LWLockRelease(SerializableXactHashLock);
}