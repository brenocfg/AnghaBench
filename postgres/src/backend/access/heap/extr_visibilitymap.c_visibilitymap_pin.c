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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ HEAPBLK_TO_MAPBLOCK (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_readbuf (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
visibilitymap_pin(Relation rel, BlockNumber heapBlk, Buffer *buf)
{
	BlockNumber mapBlock = HEAPBLK_TO_MAPBLOCK(heapBlk);

	/* Reuse the old pinned buffer if possible */
	if (BufferIsValid(*buf))
	{
		if (BufferGetBlockNumber(*buf) == mapBlock)
			return;

		ReleaseBuffer(*buf);
	}
	*buf = vm_readbuf(rel, mapBlock, true);
}