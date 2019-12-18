#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
struct TYPE_6__ {int /*<<< orphan*/  rd_smgr; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  FSMAddress ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  FSM_FORKNUM ; 
 int /*<<< orphan*/  InRecovery ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogHintBitIsNeeded () ; 
 int /*<<< orphan*/  fsm_get_location (scalar_t__,scalar_t__*) ; 
 scalar_t__ fsm_logical_to_physical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_readbuf (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsm_truncate_avail (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_newpage_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smgrexists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smgrnblocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BlockNumber
FreeSpaceMapPrepareTruncateRel(Relation rel, BlockNumber nblocks)
{
	BlockNumber new_nfsmblocks;
	FSMAddress	first_removed_address;
	uint16		first_removed_slot;
	Buffer		buf;

	RelationOpenSmgr(rel);

	/*
	 * If no FSM has been created yet for this relation, there's nothing to
	 * truncate.
	 */
	if (!smgrexists(rel->rd_smgr, FSM_FORKNUM))
		return InvalidBlockNumber;

	/* Get the location in the FSM of the first removed heap block */
	first_removed_address = fsm_get_location(nblocks, &first_removed_slot);

	/*
	 * Zero out the tail of the last remaining FSM page. If the slot
	 * representing the first removed heap block is at a page boundary, as the
	 * first slot on the FSM page that first_removed_address points to, we can
	 * just truncate that page altogether.
	 */
	if (first_removed_slot > 0)
	{
		buf = fsm_readbuf(rel, first_removed_address, false);
		if (!BufferIsValid(buf))
			return InvalidBlockNumber;	/* nothing to do; the FSM was already smaller */
		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

		/* NO EREPORT(ERROR) from here till changes are logged */
		START_CRIT_SECTION();

		fsm_truncate_avail(BufferGetPage(buf), first_removed_slot);

		/*
		 * Truncation of a relation is WAL-logged at a higher-level, and we
		 * will be called at WAL replay. But if checksums are enabled, we need
		 * to still write a WAL record to protect against a torn page, if the
		 * page is flushed to disk before the truncation WAL record. We cannot
		 * use MarkBufferDirtyHint here, because that will not dirty the page
		 * during recovery.
		 */
		MarkBufferDirty(buf);
		if (!InRecovery && RelationNeedsWAL(rel) && XLogHintBitIsNeeded())
			log_newpage_buffer(buf, false);

		END_CRIT_SECTION();

		UnlockReleaseBuffer(buf);

		new_nfsmblocks = fsm_logical_to_physical(first_removed_address) + 1;
	}
	else
	{
		new_nfsmblocks = fsm_logical_to_physical(first_removed_address);
		if (smgrnblocks(rel->rd_smgr, FSM_FORKNUM) <= new_nfsmblocks)
			return InvalidBlockNumber;	/* nothing to do; the FSM was already smaller */
	}

	return new_nfsmblocks;
}