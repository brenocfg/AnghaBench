#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  rd_smgr; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ HEAPBLK_TO_MAPBLOCK (scalar_t__) ; 
 scalar_t__ HEAPBLK_TO_MAPBYTE (scalar_t__) ; 
 scalar_t__ HEAPBLK_TO_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  InRecovery ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAPSIZE ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* PageGetContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 scalar_t__ RelationNeedsWAL (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VISIBILITYMAP_FORKNUM ; 
 scalar_t__ XLogHintBitIsNeeded () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_newpage_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smgrexists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smgrnblocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_readbuf (TYPE_1__*,scalar_t__,int) ; 

BlockNumber
visibilitymap_prepare_truncate(Relation rel, BlockNumber nheapblocks)
{
	BlockNumber newnblocks;

	/* last remaining block, byte, and bit */
	BlockNumber truncBlock = HEAPBLK_TO_MAPBLOCK(nheapblocks);
	uint32		truncByte = HEAPBLK_TO_MAPBYTE(nheapblocks);
	uint8		truncOffset = HEAPBLK_TO_OFFSET(nheapblocks);

#ifdef TRACE_VISIBILITYMAP
	elog(DEBUG1, "vm_truncate %s %d", RelationGetRelationName(rel), nheapblocks);
#endif

	RelationOpenSmgr(rel);

	/*
	 * If no visibility map has been created yet for this relation, there's
	 * nothing to truncate.
	 */
	if (!smgrexists(rel->rd_smgr, VISIBILITYMAP_FORKNUM))
		return InvalidBlockNumber;

	/*
	 * Unless the new size is exactly at a visibility map page boundary, the
	 * tail bits in the last remaining map page, representing truncated heap
	 * blocks, need to be cleared. This is not only tidy, but also necessary
	 * because we don't get a chance to clear the bits if the heap is extended
	 * again.
	 */
	if (truncByte != 0 || truncOffset != 0)
	{
		Buffer		mapBuffer;
		Page		page;
		char	   *map;

		newnblocks = truncBlock + 1;

		mapBuffer = vm_readbuf(rel, truncBlock, false);
		if (!BufferIsValid(mapBuffer))
		{
			/* nothing to do, the file was already smaller */
			return InvalidBlockNumber;
		}

		page = BufferGetPage(mapBuffer);
		map = PageGetContents(page);

		LockBuffer(mapBuffer, BUFFER_LOCK_EXCLUSIVE);

		/* NO EREPORT(ERROR) from here till changes are logged */
		START_CRIT_SECTION();

		/* Clear out the unwanted bytes. */
		MemSet(&map[truncByte + 1], 0, MAPSIZE - (truncByte + 1));

		/*----
		 * Mask out the unwanted bits of the last remaining byte.
		 *
		 * ((1 << 0) - 1) = 00000000
		 * ((1 << 1) - 1) = 00000001
		 * ...
		 * ((1 << 6) - 1) = 00111111
		 * ((1 << 7) - 1) = 01111111
		 *----
		 */
		map[truncByte] &= (1 << truncOffset) - 1;

		/*
		 * Truncation of a relation is WAL-logged at a higher-level, and we
		 * will be called at WAL replay. But if checksums are enabled, we need
		 * to still write a WAL record to protect against a torn page, if the
		 * page is flushed to disk before the truncation WAL record. We cannot
		 * use MarkBufferDirtyHint here, because that will not dirty the page
		 * during recovery.
		 */
		MarkBufferDirty(mapBuffer);
		if (!InRecovery && RelationNeedsWAL(rel) && XLogHintBitIsNeeded())
			log_newpage_buffer(mapBuffer, false);

		END_CRIT_SECTION();

		UnlockReleaseBuffer(mapBuffer);
	}
	else
		newnblocks = truncBlock;

	if (smgrnblocks(rel->rd_smgr, VISIBILITYMAP_FORKNUM) <= newnblocks)
	{
		/* nothing to do, the file was already smaller than requested size */
		return InvalidBlockNumber;
	}

	return newnblocks;
}