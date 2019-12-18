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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  FSMAddress ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  fsm_get_heap_blk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsm_get_location (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_search (int /*<<< orphan*/ ,int) ; 
 int fsm_set_and_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int fsm_space_avail_to_cat (int /*<<< orphan*/ ) ; 
 int fsm_space_needed_to_cat (int /*<<< orphan*/ ) ; 

BlockNumber
RecordAndGetPageWithFreeSpace(Relation rel, BlockNumber oldPage,
							  Size oldSpaceAvail, Size spaceNeeded)
{
	int			old_cat = fsm_space_avail_to_cat(oldSpaceAvail);
	int			search_cat = fsm_space_needed_to_cat(spaceNeeded);
	FSMAddress	addr;
	uint16		slot;
	int			search_slot;

	/* Get the location of the FSM byte representing the heap block */
	addr = fsm_get_location(oldPage, &slot);

	search_slot = fsm_set_and_search(rel, addr, slot, old_cat, search_cat);

	/*
	 * If fsm_set_and_search found a suitable new block, return that.
	 * Otherwise, search as usual.
	 */
	if (search_slot != -1)
		return fsm_get_heap_blk(addr, search_slot);
	else
		return fsm_search(rel, search_cat);
}