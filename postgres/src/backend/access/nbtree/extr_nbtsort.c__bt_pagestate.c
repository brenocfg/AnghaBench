#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_6__ {int btps_full; int /*<<< orphan*/ * btps_next; scalar_t__ btps_level; int /*<<< orphan*/  btps_lastoff; int /*<<< orphan*/ * btps_lowkey; scalar_t__ btps_blkno; int /*<<< orphan*/  btps_page; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; int /*<<< orphan*/  btws_pages_alloced; } ;
typedef  TYPE_1__ BTWriteState ;
typedef  TYPE_2__ BTPageState ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  BTREE_DEFAULT_FILLFACTOR ; 
 int BTREE_NONLEAF_FILLFACTOR ; 
 int /*<<< orphan*/  P_HIKEY ; 
 int RelationGetTargetPageFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_blnewpage (scalar_t__) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static BTPageState *
_bt_pagestate(BTWriteState *wstate, uint32 level)
{
	BTPageState *state = (BTPageState *) palloc0(sizeof(BTPageState));

	/* create initial page for level */
	state->btps_page = _bt_blnewpage(level);

	/* and assign it a page position */
	state->btps_blkno = wstate->btws_pages_alloced++;

	state->btps_lowkey = NULL;
	/* initialize lastoff so first item goes into P_FIRSTKEY */
	state->btps_lastoff = P_HIKEY;
	state->btps_level = level;
	/* set "full" threshold based on level.  See notes at head of file. */
	if (level > 0)
		state->btps_full = (BLCKSZ * (100 - BTREE_NONLEAF_FILLFACTOR) / 100);
	else
		state->btps_full = RelationGetTargetPageFreeSpace(wstate->index,
														  BTREE_DEFAULT_FILLFACTOR);
	/* no parent level, yet */
	state->btps_next = NULL;

	return state;
}