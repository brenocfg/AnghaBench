#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {scalar_t__ level; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ FSMAddress ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ FSM_BOTTOM_LEVEL ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_readbuf (int /*<<< orphan*/ ,TYPE_1__,int) ; 
 int fsm_search_avail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ fsm_set_avail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fsm_set_and_search(Relation rel, FSMAddress addr, uint16 slot,
				   uint8 newValue, uint8 minValue)
{
	Buffer		buf;
	Page		page;
	int			newslot = -1;

	buf = fsm_readbuf(rel, addr, true);
	LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);

	page = BufferGetPage(buf);

	if (fsm_set_avail(page, slot, newValue))
		MarkBufferDirtyHint(buf, false);

	if (minValue != 0)
	{
		/* Search while we still hold the lock */
		newslot = fsm_search_avail(buf, minValue,
								   addr.level == FSM_BOTTOM_LEVEL,
								   true);
	}

	UnlockReleaseBuffer(buf);

	return newslot;
}