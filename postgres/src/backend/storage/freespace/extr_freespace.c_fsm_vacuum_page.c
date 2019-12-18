#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16 ;
struct TYPE_11__ {scalar_t__ level; scalar_t__ logpageno; } ;
struct TYPE_10__ {scalar_t__ fp_next_slot; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__* FSMPage ;
typedef  TYPE_2__ FSMAddress ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ FSM_BOTTOM_LEVEL ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PageGetContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int SlotsPerFSMPage ; 
 int fsm_get_avail (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ fsm_get_child (TYPE_2__,int) ; 
 TYPE_2__ fsm_get_location (int /*<<< orphan*/ ,int*) ; 
 int fsm_get_max_avail (int /*<<< orphan*/ ) ; 
 TYPE_2__ fsm_get_parent (TYPE_2__,int*) ; 
 int /*<<< orphan*/  fsm_readbuf (int /*<<< orphan*/ ,TYPE_2__,int) ; 
 int /*<<< orphan*/  fsm_set_avail (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint8
fsm_vacuum_page(Relation rel, FSMAddress addr,
				BlockNumber start, BlockNumber end,
				bool *eof_p)
{
	Buffer		buf;
	Page		page;
	uint8		max_avail;

	/* Read the page if it exists, or return EOF */
	buf = fsm_readbuf(rel, addr, false);
	if (!BufferIsValid(buf))
	{
		*eof_p = true;
		return 0;
	}
	else
		*eof_p = false;

	page = BufferGetPage(buf);

	/*
	 * If we're above the bottom level, recurse into children, and fix the
	 * information stored about them at this level.
	 */
	if (addr.level > FSM_BOTTOM_LEVEL)
	{
		FSMAddress	fsm_start,
					fsm_end;
		uint16		fsm_start_slot,
					fsm_end_slot;
		int			slot,
					start_slot,
					end_slot;
		bool		eof = false;

		/*
		 * Compute the range of slots we need to update on this page, given
		 * the requested range of heap blocks to consider.  The first slot to
		 * update is the one covering the "start" block, and the last slot is
		 * the one covering "end - 1".  (Some of this work will be duplicated
		 * in each recursive call, but it's cheap enough to not worry about.)
		 */
		fsm_start = fsm_get_location(start, &fsm_start_slot);
		fsm_end = fsm_get_location(end - 1, &fsm_end_slot);

		while (fsm_start.level < addr.level)
		{
			fsm_start = fsm_get_parent(fsm_start, &fsm_start_slot);
			fsm_end = fsm_get_parent(fsm_end, &fsm_end_slot);
		}
		Assert(fsm_start.level == addr.level);

		if (fsm_start.logpageno == addr.logpageno)
			start_slot = fsm_start_slot;
		else if (fsm_start.logpageno > addr.logpageno)
			start_slot = SlotsPerFSMPage;	/* shouldn't get here... */
		else
			start_slot = 0;

		if (fsm_end.logpageno == addr.logpageno)
			end_slot = fsm_end_slot;
		else if (fsm_end.logpageno > addr.logpageno)
			end_slot = SlotsPerFSMPage - 1;
		else
			end_slot = -1;		/* shouldn't get here... */

		for (slot = start_slot; slot <= end_slot; slot++)
		{
			int			child_avail;

			CHECK_FOR_INTERRUPTS();

			/* After we hit end-of-file, just clear the rest of the slots */
			if (!eof)
				child_avail = fsm_vacuum_page(rel, fsm_get_child(addr, slot),
											  start, end,
											  &eof);
			else
				child_avail = 0;

			/* Update information about the child */
			if (fsm_get_avail(page, slot) != child_avail)
			{
				LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
				fsm_set_avail(page, slot, child_avail);
				MarkBufferDirtyHint(buf, false);
				LockBuffer(buf, BUFFER_LOCK_UNLOCK);
			}
		}
	}

	/* Now get the maximum value on the page, to return to caller */
	max_avail = fsm_get_max_avail(page);

	/*
	 * Reset the next slot pointer. This encourages the use of low-numbered
	 * pages, increasing the chances that a later vacuum can truncate the
	 * relation.  We don't bother with a lock here, nor with marking the page
	 * dirty if it wasn't already, since this is just a hint.
	 */
	((FSMPage) PageGetContents(page))->fp_next_slot = 0;

	ReleaseBuffer(buf);

	return max_avail;
}