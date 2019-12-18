#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  localTransactionId; int /*<<< orphan*/  backendId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_15__ {scalar_t__ pid; scalar_t__ databaseId; } ;
struct TYPE_14__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_13__ {int maxProcs; int numProcs; int* pgprocnos; } ;
typedef  TYPE_2__ ProcArrayStruct ;
typedef  TYPE_3__ PGXACT ;
typedef  TYPE_4__ PGPROC ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GET_VXID_FROM_PGPROC (TYPE_1__,TYPE_4__) ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  InvalidLocalTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  TransactionIdFollows (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ VirtualTransactionIdIsValid (TYPE_1__) ; 
 TYPE_3__* allPgXact ; 
 TYPE_4__* allProcs ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_2__* procArray ; 

VirtualTransactionId *
GetConflictingVirtualXIDs(TransactionId limitXmin, Oid dbOid)
{
	static VirtualTransactionId *vxids;
	ProcArrayStruct *arrayP = procArray;
	int			count = 0;
	int			index;

	/*
	 * If first time through, get workspace to remember main XIDs in. We
	 * malloc it permanently to avoid repeated palloc/pfree overhead. Allow
	 * result space, remembering room for a terminator.
	 */
	if (vxids == NULL)
	{
		vxids = (VirtualTransactionId *)
			malloc(sizeof(VirtualTransactionId) * (arrayP->maxProcs + 1));
		if (vxids == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
	}

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		PGPROC	   *proc = &allProcs[pgprocno];
		PGXACT	   *pgxact = &allPgXact[pgprocno];

		/* Exclude prepared transactions */
		if (proc->pid == 0)
			continue;

		if (!OidIsValid(dbOid) ||
			proc->databaseId == dbOid)
		{
			/* Fetch xmin just once - can't change on us, but good coding */
			TransactionId pxmin = UINT32_ACCESS_ONCE(pgxact->xmin);

			/*
			 * We ignore an invalid pxmin because this means that backend has
			 * no snapshot currently. We hold a Share lock to avoid contention
			 * with users taking snapshots.  That is not a problem because the
			 * current xmin is always at least one higher than the latest
			 * removed xid, so any new snapshot would never conflict with the
			 * test here.
			 */
			if (!TransactionIdIsValid(limitXmin) ||
				(TransactionIdIsValid(pxmin) && !TransactionIdFollows(pxmin, limitXmin)))
			{
				VirtualTransactionId vxid;

				GET_VXID_FROM_PGPROC(vxid, *proc);
				if (VirtualTransactionIdIsValid(vxid))
					vxids[count++] = vxid;
			}
		}
	}

	LWLockRelease(ProcArrayLock);

	/* add the terminator */
	vxids[count].backendId = InvalidBackendId;
	vxids[count].localTransactionId = InvalidLocalTransactionId;

	return vxids;
}