#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* allProcs; } ;
struct TYPE_9__ {int numPrepXacts; TYPE_2__** prepXacts; } ;
struct TYPE_8__ {size_t pgprocno; scalar_t__ locking_backend; scalar_t__ owner; int /*<<< orphan*/  gid; int /*<<< orphan*/  valid; } ;
struct TYPE_7__ {scalar_t__ databaseId; } ;
typedef  TYPE_1__ PGPROC ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  AtProcExit_Twophase ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidBackendId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MyBackendId ; 
 scalar_t__ MyDatabaseId ; 
 TYPE_2__* MyLockedGxact ; 
 TYPE_4__* ProcGlobal ; 
 TYPE_3__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  before_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  superuser_arg (scalar_t__) ; 
 int twophaseExitRegistered ; 

__attribute__((used)) static GlobalTransaction
LockGXact(const char *gid, Oid user)
{
	int			i;

	/* on first call, register the exit hook */
	if (!twophaseExitRegistered)
	{
		before_shmem_exit(AtProcExit_Twophase, 0);
		twophaseExitRegistered = true;
	}

	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);

	for (i = 0; i < TwoPhaseState->numPrepXacts; i++)
	{
		GlobalTransaction gxact = TwoPhaseState->prepXacts[i];
		PGPROC	   *proc = &ProcGlobal->allProcs[gxact->pgprocno];

		/* Ignore not-yet-valid GIDs */
		if (!gxact->valid)
			continue;
		if (strcmp(gxact->gid, gid) != 0)
			continue;

		/* Found it, but has someone else got it locked? */
		if (gxact->locking_backend != InvalidBackendId)
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("prepared transaction with identifier \"%s\" is busy",
							gid)));

		if (user != gxact->owner && !superuser_arg(user))
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied to finish prepared transaction"),
					 errhint("Must be superuser or the user that prepared the transaction.")));

		/*
		 * Note: it probably would be possible to allow committing from
		 * another database; but at the moment NOTIFY is known not to work and
		 * there may be some other issues as well.  Hence disallow until
		 * someone gets motivated to make it work.
		 */
		if (MyDatabaseId != proc->databaseId)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("prepared transaction belongs to another database"),
					 errhint("Connect to the database where the transaction was prepared to finish it.")));

		/* OK for me to lock it */
		gxact->locking_backend = MyBackendId;
		MyLockedGxact = gxact;

		LWLockRelease(TwoPhaseStateLock);

		return gxact;
	}

	LWLockRelease(TwoPhaseStateLock);

	ereport(ERROR,
			(errcode(ERRCODE_UNDEFINED_OBJECT),
			 errmsg("prepared transaction with identifier \"%s\" does not exist",
					gid)));

	/* NOTREACHED */
	return NULL;
}