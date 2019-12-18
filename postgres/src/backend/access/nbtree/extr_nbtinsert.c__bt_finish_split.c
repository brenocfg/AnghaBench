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
struct TYPE_8__ {int /*<<< orphan*/  btm_root; } ;
struct TYPE_7__ {int /*<<< orphan*/  btpo_next; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  TYPE_1__* BTPageOpaque ;
typedef  TYPE_2__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* BTPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 int /*<<< orphan*/  BT_WRITE ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  P_INCOMPLETE_SPLIT (TYPE_1__*) ; 
 scalar_t__ P_LEFTMOST (TYPE_1__*) ; 
 scalar_t__ P_RIGHTMOST (TYPE_1__*) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_insert_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_bt_finish_split(Relation rel, Buffer lbuf, BTStack stack)
{
	Page		lpage = BufferGetPage(lbuf);
	BTPageOpaque lpageop = (BTPageOpaque) PageGetSpecialPointer(lpage);
	Buffer		rbuf;
	Page		rpage;
	BTPageOpaque rpageop;
	bool		was_root;
	bool		was_only;

	Assert(P_INCOMPLETE_SPLIT(lpageop));

	/* Lock right sibling, the one missing the downlink */
	rbuf = _bt_getbuf(rel, lpageop->btpo_next, BT_WRITE);
	rpage = BufferGetPage(rbuf);
	rpageop = (BTPageOpaque) PageGetSpecialPointer(rpage);

	/* Could this be a root split? */
	if (!stack)
	{
		Buffer		metabuf;
		Page		metapg;
		BTMetaPageData *metad;

		/* acquire lock on the metapage */
		metabuf = _bt_getbuf(rel, BTREE_METAPAGE, BT_WRITE);
		metapg = BufferGetPage(metabuf);
		metad = BTPageGetMeta(metapg);

		was_root = (metad->btm_root == BufferGetBlockNumber(lbuf));

		_bt_relbuf(rel, metabuf);
	}
	else
		was_root = false;

	/* Was this the only page on the level before split? */
	was_only = (P_LEFTMOST(lpageop) && P_RIGHTMOST(rpageop));

	elog(DEBUG1, "finishing incomplete split of %u/%u",
		 BufferGetBlockNumber(lbuf), BufferGetBlockNumber(rbuf));

	_bt_insert_parent(rel, lbuf, rbuf, stack, was_root, was_only);
}