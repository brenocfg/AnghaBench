#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* XLogRecPtr ;
struct TYPE_4__ {int /*<<< orphan*/  origin_lsn; int /*<<< orphan*/  owner; int /*<<< orphan*/  xid; int /*<<< orphan*/  prepared_at; } ;
typedef  TYPE_1__ TwoPhaseFileHeader ;
struct TYPE_6__ {scalar_t__ numPrepXacts; TYPE_2__** prepXacts; TYPE_2__* freeGXacts; } ;
struct TYPE_5__ {int valid; int inredo; int /*<<< orphan*/  xid; int /*<<< orphan*/  gid; int /*<<< orphan*/  ondisk; int /*<<< orphan*/  locking_backend; int /*<<< orphan*/  owner; void* prepare_end_lsn; void* prepare_start_lsn; int /*<<< orphan*/  prepared_at; struct TYPE_5__* next; } ;
typedef  scalar_t__ RepOriginId ;
typedef  TYPE_2__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 scalar_t__ InvalidRepOriginId ; 
 int LWLockHeldByMeInMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXALIGN (int) ; 
 int RecoveryInProgress () ; 
 TYPE_3__* TwoPhaseState ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  XLogRecPtrIsInvalid (void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,scalar_t__) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ max_prepared_xacts ; 
 int /*<<< orphan*/  replorigin_advance (scalar_t__,int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

void
PrepareRedoAdd(char *buf, XLogRecPtr start_lsn,
			   XLogRecPtr end_lsn, RepOriginId origin_id)
{
	TwoPhaseFileHeader *hdr = (TwoPhaseFileHeader *) buf;
	char	   *bufptr;
	const char *gid;
	GlobalTransaction gxact;

	Assert(LWLockHeldByMeInMode(TwoPhaseStateLock, LW_EXCLUSIVE));
	Assert(RecoveryInProgress());

	bufptr = buf + MAXALIGN(sizeof(TwoPhaseFileHeader));
	gid = (const char *) bufptr;

	/*
	 * Reserve the GID for the given transaction in the redo code path.
	 *
	 * This creates a gxact struct and puts it into the active array.
	 *
	 * In redo, this struct is mainly used to track PREPARE/COMMIT entries in
	 * shared memory. Hence, we only fill up the bare minimum contents here.
	 * The gxact also gets marked with gxact->inredo set to true to indicate
	 * that it got added in the redo phase
	 */

	/* Get a free gxact from the freelist */
	if (TwoPhaseState->freeGXacts == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("maximum number of prepared transactions reached"),
				 errhint("Increase max_prepared_transactions (currently %d).",
						 max_prepared_xacts)));
	gxact = TwoPhaseState->freeGXacts;
	TwoPhaseState->freeGXacts = gxact->next;

	gxact->prepared_at = hdr->prepared_at;
	gxact->prepare_start_lsn = start_lsn;
	gxact->prepare_end_lsn = end_lsn;
	gxact->xid = hdr->xid;
	gxact->owner = hdr->owner;
	gxact->locking_backend = InvalidBackendId;
	gxact->valid = false;
	gxact->ondisk = XLogRecPtrIsInvalid(start_lsn);
	gxact->inredo = true;		/* yes, added in redo */
	strcpy(gxact->gid, gid);

	/* And insert it into the active array */
	Assert(TwoPhaseState->numPrepXacts < max_prepared_xacts);
	TwoPhaseState->prepXacts[TwoPhaseState->numPrepXacts++] = gxact;

	if (origin_id != InvalidRepOriginId)
	{
		/* recover apply progress */
		replorigin_advance(origin_id, hdr->origin_lsn, end_lsn,
						   false /* backward */ , false /* WAL */ );
	}

	elog(DEBUG2, "added 2PC data in shared memory for transaction %u", gxact->xid);
}