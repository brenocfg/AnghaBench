#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bounds_valid; int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  btpo_next; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  TYPE_1__* BTPageOpaque ;
typedef  TYPE_2__* BTInsertState ;

/* Variables and functions */
 int /*<<< orphan*/  BT_WRITE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  P_IGNORE (TYPE_1__*) ; 
 scalar_t__ P_INCOMPLETE_SPLIT (TYPE_1__*) ; 
 scalar_t__ P_RIGHTMOST (TYPE_1__*) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_finish_split (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relandgetbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_bt_stepright(Relation rel, BTInsertState insertstate, BTStack stack)
{
	Page		page;
	BTPageOpaque lpageop;
	Buffer		rbuf;
	BlockNumber rblkno;

	page = BufferGetPage(insertstate->buf);
	lpageop = (BTPageOpaque) PageGetSpecialPointer(page);

	rbuf = InvalidBuffer;
	rblkno = lpageop->btpo_next;
	for (;;)
	{
		rbuf = _bt_relandgetbuf(rel, rbuf, rblkno, BT_WRITE);
		page = BufferGetPage(rbuf);
		lpageop = (BTPageOpaque) PageGetSpecialPointer(page);

		/*
		 * If this page was incompletely split, finish the split now.  We do
		 * this while holding a lock on the left sibling, which is not good
		 * because finishing the split could be a fairly lengthy operation.
		 * But this should happen very seldom.
		 */
		if (P_INCOMPLETE_SPLIT(lpageop))
		{
			_bt_finish_split(rel, rbuf, stack);
			rbuf = InvalidBuffer;
			continue;
		}

		if (!P_IGNORE(lpageop))
			break;
		if (P_RIGHTMOST(lpageop))
			elog(ERROR, "fell off the end of index \"%s\"",
				 RelationGetRelationName(rel));

		rblkno = lpageop->btpo_next;
	}
	/* rbuf locked; unlock buf, update state for caller */
	_bt_relbuf(rel, insertstate->buf);
	insertstate->buf = rbuf;
	insertstate->bounds_valid = false;
}