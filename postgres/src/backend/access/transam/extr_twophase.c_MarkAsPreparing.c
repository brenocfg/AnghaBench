#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_6__ {int numPrepXacts; TYPE_1__** prepXacts; TYPE_1__* freeGXacts; } ;
struct TYPE_5__ {int ondisk; struct TYPE_5__* next; int /*<<< orphan*/  gid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AtProcExit_Twophase ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GIDSIZE ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MarkAsPreparingGuts (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  before_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int max_prepared_xacts ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int twophaseExitRegistered ; 

GlobalTransaction
MarkAsPreparing(TransactionId xid, const char *gid,
				TimestampTz prepared_at, Oid owner, Oid databaseid)
{
	GlobalTransaction gxact;
	int			i;

	if (strlen(gid) >= GIDSIZE)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("transaction identifier \"%s\" is too long",
						gid)));

	/* fail immediately if feature is disabled */
	if (max_prepared_xacts == 0)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("prepared transactions are disabled"),
				 errhint("Set max_prepared_transactions to a nonzero value.")));

	/* on first call, register the exit hook */
	if (!twophaseExitRegistered)
	{
		before_shmem_exit(AtProcExit_Twophase, 0);
		twophaseExitRegistered = true;
	}

	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);

	/* Check for conflicting GID */
	for (i = 0; i < TwoPhaseState->numPrepXacts; i++)
	{
		gxact = TwoPhaseState->prepXacts[i];
		if (strcmp(gxact->gid, gid) == 0)
		{
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("transaction identifier \"%s\" is already in use",
							gid)));
		}
	}

	/* Get a free gxact from the freelist */
	if (TwoPhaseState->freeGXacts == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("maximum number of prepared transactions reached"),
				 errhint("Increase max_prepared_transactions (currently %d).",
						 max_prepared_xacts)));
	gxact = TwoPhaseState->freeGXacts;
	TwoPhaseState->freeGXacts = gxact->next;

	MarkAsPreparingGuts(gxact, xid, gid, prepared_at, owner, databaseid);

	gxact->ondisk = false;

	/* And insert it into the active array */
	Assert(TwoPhaseState->numPrepXacts < max_prepared_xacts);
	TwoPhaseState->prepXacts[TwoPhaseState->numPrepXacts++] = gxact;

	LWLockRelease(TwoPhaseStateLock);

	return gxact;
}