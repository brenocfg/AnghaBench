#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HEAPBLK_TO_MAPBLOCK (scalar_t__) ; 
 int HEAPBLK_TO_MAPBYTE (scalar_t__) ; 
 int HEAPBLK_TO_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 char* PageGetContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int VISIBILITYMAP_VALID_BITS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

bool
visibilitymap_clear(Relation rel, BlockNumber heapBlk, Buffer buf, uint8 flags)
{
	BlockNumber mapBlock = HEAPBLK_TO_MAPBLOCK(heapBlk);
	int			mapByte = HEAPBLK_TO_MAPBYTE(heapBlk);
	int			mapOffset = HEAPBLK_TO_OFFSET(heapBlk);
	uint8		mask = flags << mapOffset;
	char	   *map;
	bool		cleared = false;

	Assert(flags & VISIBILITYMAP_VALID_BITS);

#ifdef TRACE_VISIBILITYMAP
	elog(DEBUG1, "vm_clear %s %d", RelationGetRelationName(rel), heapBlk);
#endif

	if (!BufferIsValid(buf) || BufferGetBlockNumber(buf) != mapBlock)
		elog(ERROR, "wrong buffer passed to visibilitymap_clear");

	LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
	map = PageGetContents(BufferGetPage(buf));

	if (map[mapByte] & mask)
	{
		map[mapByte] &= ~mask;

		MarkBufferDirty(buf);
		cleared = true;
	}

	LockBuffer(buf, BUFFER_LOCK_UNLOCK);

	return cleared;
}