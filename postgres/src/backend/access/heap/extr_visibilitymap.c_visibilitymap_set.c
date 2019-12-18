#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HEAPBLK_TO_MAPBLOCK (scalar_t__) ; 
 size_t HEAPBLK_TO_MAPBYTE (scalar_t__) ; 
 int HEAPBLK_TO_OFFSET (scalar_t__) ; 
 scalar_t__ InRecovery ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetContents (int /*<<< orphan*/ ) ; 
 int PageIsAllVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 scalar_t__ RelationNeedsWAL (TYPE_1__*) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int VISIBILITYMAP_VALID_BITS ; 
 scalar_t__ XLogHintBitIsNeeded () ; 
 scalar_t__ XLogRecPtrIsInvalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  log_heap_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
visibilitymap_set(Relation rel, BlockNumber heapBlk, Buffer heapBuf,
				  XLogRecPtr recptr, Buffer vmBuf, TransactionId cutoff_xid,
				  uint8 flags)
{
	BlockNumber mapBlock = HEAPBLK_TO_MAPBLOCK(heapBlk);
	uint32		mapByte = HEAPBLK_TO_MAPBYTE(heapBlk);
	uint8		mapOffset = HEAPBLK_TO_OFFSET(heapBlk);
	Page		page;
	uint8	   *map;

#ifdef TRACE_VISIBILITYMAP
	elog(DEBUG1, "vm_set %s %d", RelationGetRelationName(rel), heapBlk);
#endif

	Assert(InRecovery || XLogRecPtrIsInvalid(recptr));
	Assert(InRecovery || BufferIsValid(heapBuf));
	Assert(flags & VISIBILITYMAP_VALID_BITS);

	/* Check that we have the right heap page pinned, if present */
	if (BufferIsValid(heapBuf) && BufferGetBlockNumber(heapBuf) != heapBlk)
		elog(ERROR, "wrong heap buffer passed to visibilitymap_set");

	/* Check that we have the right VM page pinned */
	if (!BufferIsValid(vmBuf) || BufferGetBlockNumber(vmBuf) != mapBlock)
		elog(ERROR, "wrong VM buffer passed to visibilitymap_set");

	page = BufferGetPage(vmBuf);
	map = (uint8 *) PageGetContents(page);
	LockBuffer(vmBuf, BUFFER_LOCK_EXCLUSIVE);

	if (flags != (map[mapByte] >> mapOffset & VISIBILITYMAP_VALID_BITS))
	{
		START_CRIT_SECTION();

		map[mapByte] |= (flags << mapOffset);
		MarkBufferDirty(vmBuf);

		if (RelationNeedsWAL(rel))
		{
			if (XLogRecPtrIsInvalid(recptr))
			{
				Assert(!InRecovery);
				recptr = log_heap_visible(rel->rd_node, heapBuf, vmBuf,
										  cutoff_xid, flags);

				/*
				 * If data checksums are enabled (or wal_log_hints=on), we
				 * need to protect the heap page from being torn.
				 */
				if (XLogHintBitIsNeeded())
				{
					Page		heapPage = BufferGetPage(heapBuf);

					/* caller is expected to set PD_ALL_VISIBLE first */
					Assert(PageIsAllVisible(heapPage));
					PageSetLSN(heapPage, recptr);
				}
			}
			PageSetLSN(page, recptr);
		}

		END_CRIT_SECTION();
	}

	LockBuffer(vmBuf, BUFFER_LOCK_UNLOCK);
}