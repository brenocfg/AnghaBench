#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pg_crc32c ;
struct TYPE_9__ {scalar_t__ magic; scalar_t__ total_len; scalar_t__ origin_timestamp; scalar_t__ origin_lsn; } ;
typedef  TYPE_1__ TwoPhaseFileHeader ;
struct TYPE_13__ {int delayChkpt; } ;
struct TYPE_12__ {scalar_t__ total_len; scalar_t__ num_chunks; TYPE_2__* head; int /*<<< orphan*/  tail; } ;
struct TYPE_11__ {int /*<<< orphan*/  prepare_end_lsn; int /*<<< orphan*/  prepare_start_lsn; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; scalar_t__ data; struct TYPE_10__* next; } ;
typedef  TYPE_2__ StateFileChunk ;
typedef  TYPE_3__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DoNotReplicateId ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidRepOriginId ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  MarkAsPrepared (TYPE_3__*,int) ; 
 scalar_t__ MaxAllocSize ; 
 TYPE_3__* MyLockedGxact ; 
 TYPE_5__* MyPgXact ; 
 int /*<<< orphan*/  ProcLastRecPtr ; 
 int /*<<< orphan*/  RM_XACT_ID ; 
 int /*<<< orphan*/  RegisterTwoPhaseRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SyncRepWaitForLSN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TWOPHASE_MAGIC ; 
 int /*<<< orphan*/  TWOPHASE_RM_END_ID ; 
 int /*<<< orphan*/  XLOG_INCLUDE_ORIGIN ; 
 int /*<<< orphan*/  XLOG_XACT_PREPARE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogEnsureRecordSpace (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogSetRecordFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_4__ records ; 
 int /*<<< orphan*/  replorigin_session_advance (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ replorigin_session_origin ; 
 scalar_t__ replorigin_session_origin_lsn ; 
 scalar_t__ replorigin_session_origin_timestamp ; 

void
EndPrepare(GlobalTransaction gxact)
{
	TwoPhaseFileHeader *hdr;
	StateFileChunk *record;
	bool		replorigin;

	/* Add the end sentinel to the list of 2PC records */
	RegisterTwoPhaseRecord(TWOPHASE_RM_END_ID, 0,
						   NULL, 0);

	/* Go back and fill in total_len in the file header record */
	hdr = (TwoPhaseFileHeader *) records.head->data;
	Assert(hdr->magic == TWOPHASE_MAGIC);
	hdr->total_len = records.total_len + sizeof(pg_crc32c);

	replorigin = (replorigin_session_origin != InvalidRepOriginId &&
				  replorigin_session_origin != DoNotReplicateId);

	if (replorigin)
	{
		Assert(replorigin_session_origin_lsn != InvalidXLogRecPtr);
		hdr->origin_lsn = replorigin_session_origin_lsn;
		hdr->origin_timestamp = replorigin_session_origin_timestamp;
	}
	else
	{
		hdr->origin_lsn = InvalidXLogRecPtr;
		hdr->origin_timestamp = 0;
	}

	/*
	 * If the data size exceeds MaxAllocSize, we won't be able to read it in
	 * ReadTwoPhaseFile. Check for that now, rather than fail in the case
	 * where we write data to file and then re-read at commit time.
	 */
	if (hdr->total_len > MaxAllocSize)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("two-phase state file maximum length exceeded")));

	/*
	 * Now writing 2PC state data to WAL. We let the WAL's CRC protection
	 * cover us, so no need to calculate a separate CRC.
	 *
	 * We have to set delayChkpt here, too; otherwise a checkpoint starting
	 * immediately after the WAL record is inserted could complete without
	 * fsync'ing our state file.  (This is essentially the same kind of race
	 * condition as the COMMIT-to-clog-write case that RecordTransactionCommit
	 * uses delayChkpt for; see notes there.)
	 *
	 * We save the PREPARE record's location in the gxact for later use by
	 * CheckPointTwoPhase.
	 */
	XLogEnsureRecordSpace(0, records.num_chunks);

	START_CRIT_SECTION();

	MyPgXact->delayChkpt = true;

	XLogBeginInsert();
	for (record = records.head; record != NULL; record = record->next)
		XLogRegisterData(record->data, record->len);

	XLogSetRecordFlags(XLOG_INCLUDE_ORIGIN);

	gxact->prepare_end_lsn = XLogInsert(RM_XACT_ID, XLOG_XACT_PREPARE);

	if (replorigin)
	{
		/* Move LSNs forward for this replication origin */
		replorigin_session_advance(replorigin_session_origin_lsn,
								   gxact->prepare_end_lsn);
	}

	XLogFlush(gxact->prepare_end_lsn);

	/* If we crash now, we have prepared: WAL replay will fix things */

	/* Store record's start location to read that later on Commit */
	gxact->prepare_start_lsn = ProcLastRecPtr;

	/*
	 * Mark the prepared transaction as valid.  As soon as xact.c marks
	 * MyPgXact as not running our XID (which it will do immediately after
	 * this function returns), others can commit/rollback the xact.
	 *
	 * NB: a side effect of this is to make a dummy ProcArray entry for the
	 * prepared XID.  This must happen before we clear the XID from MyPgXact,
	 * else there is a window where the XID is not running according to
	 * TransactionIdIsInProgress, and onlookers would be entitled to assume
	 * the xact crashed.  Instead we have a window where the same XID appears
	 * twice in ProcArray, which is OK.
	 */
	MarkAsPrepared(gxact, false);

	/*
	 * Now we can mark ourselves as out of the commit critical section: a
	 * checkpoint starting after this will certainly see the gxact as a
	 * candidate for fsyncing.
	 */
	MyPgXact->delayChkpt = false;

	/*
	 * Remember that we have this GlobalTransaction entry locked for us.  If
	 * we crash after this point, it's too late to abort, but we must unlock
	 * it so that the prepared transaction can be committed or rolled back.
	 */
	MyLockedGxact = gxact;

	END_CRIT_SECTION();

	/*
	 * Wait for synchronous replication, if required.
	 *
	 * Note that at this stage we have marked the prepare, but still show as
	 * running in the procarray (twice!) and continue to hold locks.
	 */
	SyncRepWaitForLSN(gxact->prepare_end_lsn, false);

	records.tail = records.head = NULL;
	records.num_chunks = 0;
}