#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_10__ {scalar_t__ level; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ FSMAddress ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ FSM_BOTTOM_LEVEL ; 
 TYPE_1__ FSM_ROOT_ADDRESS ; 
 scalar_t__ FSM_ROOT_LEVEL ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 TYPE_1__ fsm_get_child (TYPE_1__,int) ; 
 int /*<<< orphan*/  fsm_get_heap_blk (TYPE_1__,int) ; 
 int /*<<< orphan*/  fsm_get_max_avail (int /*<<< orphan*/ ) ; 
 TYPE_1__ fsm_get_parent (TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_readbuf (int /*<<< orphan*/ ,TYPE_1__,int) ; 
 int fsm_search_avail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fsm_set_and_search (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BlockNumber
fsm_search(Relation rel, uint8 min_cat)
{
	int			restarts = 0;
	FSMAddress	addr = FSM_ROOT_ADDRESS;

	for (;;)
	{
		int			slot;
		Buffer		buf;
		uint8		max_avail = 0;

		/* Read the FSM page. */
		buf = fsm_readbuf(rel, addr, false);

		/* Search within the page */
		if (BufferIsValid(buf))
		{
			LockBuffer(buf, BUFFER_LOCK_SHARE);
			slot = fsm_search_avail(buf, min_cat,
									(addr.level == FSM_BOTTOM_LEVEL),
									false);
			if (slot == -1)
				max_avail = fsm_get_max_avail(BufferGetPage(buf));
			UnlockReleaseBuffer(buf);
		}
		else
			slot = -1;

		if (slot != -1)
		{
			/*
			 * Descend the tree, or return the found block if we're at the
			 * bottom.
			 */
			if (addr.level == FSM_BOTTOM_LEVEL)
				return fsm_get_heap_blk(addr, slot);

			addr = fsm_get_child(addr, slot);
		}
		else if (addr.level == FSM_ROOT_LEVEL)
		{
			/*
			 * At the root, failure means there's no page with enough free
			 * space in the FSM. Give up.
			 */
			return InvalidBlockNumber;
		}
		else
		{
			uint16		parentslot;
			FSMAddress	parent;

			/*
			 * At lower level, failure can happen if the value in the upper-
			 * level node didn't reflect the value on the lower page. Update
			 * the upper node, to avoid falling into the same trap again, and
			 * start over.
			 *
			 * There's a race condition here, if another backend updates this
			 * page right after we release it, and gets the lock on the parent
			 * page before us. We'll then update the parent page with the now
			 * stale information we had. It's OK, because it should happen
			 * rarely, and will be fixed by the next vacuum.
			 */
			parent = fsm_get_parent(addr, &parentslot);
			fsm_set_and_search(rel, parent, parentslot, max_avail, 0);

			/*
			 * If the upper pages are badly out of date, we might need to loop
			 * quite a few times, updating them as we go. Any inconsistencies
			 * should eventually be corrected and the loop should end. Looping
			 * indefinitely is nevertheless scary, so provide an emergency
			 * valve.
			 */
			if (restarts++ > 10000)
				return InvalidBlockNumber;

			/* Start search all over from the root */
			addr = FSM_ROOT_ADDRESS;
		}
	}
}