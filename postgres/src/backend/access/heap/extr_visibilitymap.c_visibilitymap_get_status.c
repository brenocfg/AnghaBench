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
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ HEAPBLK_TO_MAPBLOCK (scalar_t__) ; 
 size_t HEAPBLK_TO_MAPBYTE (scalar_t__) ; 
 int HEAPBLK_TO_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 char* PageGetContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 char VISIBILITYMAP_VALID_BITS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_readbuf (int /*<<< orphan*/ ,scalar_t__,int) ; 

uint8
visibilitymap_get_status(Relation rel, BlockNumber heapBlk, Buffer *buf)
{
	BlockNumber mapBlock = HEAPBLK_TO_MAPBLOCK(heapBlk);
	uint32		mapByte = HEAPBLK_TO_MAPBYTE(heapBlk);
	uint8		mapOffset = HEAPBLK_TO_OFFSET(heapBlk);
	char	   *map;
	uint8		result;

#ifdef TRACE_VISIBILITYMAP
	elog(DEBUG1, "vm_get_status %s %d", RelationGetRelationName(rel), heapBlk);
#endif

	/* Reuse the old pinned buffer if possible */
	if (BufferIsValid(*buf))
	{
		if (BufferGetBlockNumber(*buf) != mapBlock)
		{
			ReleaseBuffer(*buf);
			*buf = InvalidBuffer;
		}
	}

	if (!BufferIsValid(*buf))
	{
		*buf = vm_readbuf(rel, mapBlock, false);
		if (!BufferIsValid(*buf))
			return false;
	}

	map = PageGetContents(BufferGetPage(*buf));

	/*
	 * A single byte read is atomic.  There could be memory-ordering effects
	 * here, but for performance reasons we make it the caller's job to worry
	 * about that.
	 */
	result = ((map[mapByte] >> mapOffset) & VISIBILITYMAP_VALID_BITS);
	return result;
}