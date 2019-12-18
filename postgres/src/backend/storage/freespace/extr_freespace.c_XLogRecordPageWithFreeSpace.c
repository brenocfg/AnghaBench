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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  FSMAddress ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSM_FORKNUM ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PageInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_ZERO_ON_ERROR ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_get_location (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_logical_to_physical (int /*<<< orphan*/ ) ; 
 scalar_t__ fsm_set_avail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int fsm_space_avail_to_cat (int /*<<< orphan*/ ) ; 

void
XLogRecordPageWithFreeSpace(RelFileNode rnode, BlockNumber heapBlk,
							Size spaceAvail)
{
	int			new_cat = fsm_space_avail_to_cat(spaceAvail);
	FSMAddress	addr;
	uint16		slot;
	BlockNumber blkno;
	Buffer		buf;
	Page		page;

	/* Get the location of the FSM byte representing the heap block */
	addr = fsm_get_location(heapBlk, &slot);
	blkno = fsm_logical_to_physical(addr);

	/* If the page doesn't exist already, extend */
	buf = XLogReadBufferExtended(rnode, FSM_FORKNUM, blkno, RBM_ZERO_ON_ERROR);
	LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

	page = BufferGetPage(buf);
	if (PageIsNew(page))
		PageInit(page, BLCKSZ, 0);

	if (fsm_set_avail(page, slot, new_cat))
		MarkBufferDirtyHint(buf, false);
	UnlockReleaseBuffer(buf);
}