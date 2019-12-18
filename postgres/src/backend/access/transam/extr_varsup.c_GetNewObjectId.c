#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nextOid; scalar_t__ oidCount; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstBootstrapObjectId ; 
 void* FirstNormalObjectId ; 
 scalar_t__ IsPostmasterEnvironment ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  OidGenLock ; 
 scalar_t__ RecoveryInProgress () ; 
 TYPE_1__* ShmemVariableCache ; 
 scalar_t__ VAR_OID_PREFETCH ; 
 int /*<<< orphan*/  XLogPutNextOid (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

Oid
GetNewObjectId(void)
{
	Oid			result;

	/* safety check, we should never get this far in a HS standby */
	if (RecoveryInProgress())
		elog(ERROR, "cannot assign OIDs during recovery");

	LWLockAcquire(OidGenLock, LW_EXCLUSIVE);

	/*
	 * Check for wraparound of the OID counter.  We *must* not return 0
	 * (InvalidOid), and in normal operation we mustn't return anything below
	 * FirstNormalObjectId since that range is reserved for initdb (see
	 * IsCatalogRelationOid()).  Note we are relying on unsigned comparison.
	 *
	 * During initdb, we start the OID generator at FirstBootstrapObjectId, so
	 * we only wrap if before that point when in bootstrap or standalone mode.
	 * The first time through this routine after normal postmaster start, the
	 * counter will be forced up to FirstNormalObjectId.  This mechanism
	 * leaves the OIDs between FirstBootstrapObjectId and FirstNormalObjectId
	 * available for automatic assignment during initdb, while ensuring they
	 * will never conflict with user-assigned OIDs.
	 */
	if (ShmemVariableCache->nextOid < ((Oid) FirstNormalObjectId))
	{
		if (IsPostmasterEnvironment)
		{
			/* wraparound, or first post-initdb assignment, in normal mode */
			ShmemVariableCache->nextOid = FirstNormalObjectId;
			ShmemVariableCache->oidCount = 0;
		}
		else
		{
			/* we may be bootstrapping, so don't enforce the full range */
			if (ShmemVariableCache->nextOid < ((Oid) FirstBootstrapObjectId))
			{
				/* wraparound in standalone mode (unlikely but possible) */
				ShmemVariableCache->nextOid = FirstNormalObjectId;
				ShmemVariableCache->oidCount = 0;
			}
		}
	}

	/* If we run out of logged for use oids then we must log more */
	if (ShmemVariableCache->oidCount == 0)
	{
		XLogPutNextOid(ShmemVariableCache->nextOid + VAR_OID_PREFETCH);
		ShmemVariableCache->oidCount = VAR_OID_PREFETCH;
	}

	result = ShmemVariableCache->nextOid;

	(ShmemVariableCache->nextOid)++;
	(ShmemVariableCache->oidCount)--;

	LWLockRelease(OidGenLock);

	return result;
}