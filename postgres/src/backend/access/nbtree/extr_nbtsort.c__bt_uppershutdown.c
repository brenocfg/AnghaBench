#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_12__ {int /*<<< orphan*/  btpo_flags; } ;
struct TYPE_11__ {int /*<<< orphan*/ * btps_page; int /*<<< orphan*/  btps_blkno; int /*<<< orphan*/ * btps_lowkey; struct TYPE_11__* btps_next; int /*<<< orphan*/  btps_level; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/ * Page ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_1__ BTWriteState ;
typedef  TYPE_2__ BTPageState ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BTP_ROOT ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 int /*<<< orphan*/  BTreeInnerTupleSetDownLink (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BTreeTupleGetNAtts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 scalar_t__ P_LEFTMOST (TYPE_3__*) ; 
 int /*<<< orphan*/  P_NONE ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_blwritepage (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_buildadd (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_initmetapage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_slideleft (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_bt_uppershutdown(BTWriteState *wstate, BTPageState *state)
{
	BTPageState *s;
	BlockNumber rootblkno = P_NONE;
	uint32		rootlevel = 0;
	Page		metapage;

	/*
	 * Each iteration of this loop completes one more level of the tree.
	 */
	for (s = state; s != NULL; s = s->btps_next)
	{
		BlockNumber blkno;
		BTPageOpaque opaque;

		blkno = s->btps_blkno;
		opaque = (BTPageOpaque) PageGetSpecialPointer(s->btps_page);

		/*
		 * We have to link the last page on this level to somewhere.
		 *
		 * If we're at the top, it's the root, so attach it to the metapage.
		 * Otherwise, add an entry for it to its parent using its low key.
		 * This may cause the last page of the parent level to split, but
		 * that's not a problem -- we haven't gotten to it yet.
		 */
		if (s->btps_next == NULL)
		{
			opaque->btpo_flags |= BTP_ROOT;
			rootblkno = blkno;
			rootlevel = s->btps_level;
		}
		else
		{
			Assert((BTreeTupleGetNAtts(s->btps_lowkey, wstate->index) <=
					IndexRelationGetNumberOfKeyAttributes(wstate->index) &&
					BTreeTupleGetNAtts(s->btps_lowkey, wstate->index) > 0) ||
				   P_LEFTMOST(opaque));
			Assert(BTreeTupleGetNAtts(s->btps_lowkey, wstate->index) == 0 ||
				   !P_LEFTMOST(opaque));
			BTreeInnerTupleSetDownLink(s->btps_lowkey, blkno);
			_bt_buildadd(wstate, s->btps_next, s->btps_lowkey);
			pfree(s->btps_lowkey);
			s->btps_lowkey = NULL;
		}

		/*
		 * This is the rightmost page, so the ItemId array needs to be slid
		 * back one slot.  Then we can dump out the page.
		 */
		_bt_slideleft(s->btps_page);
		_bt_blwritepage(wstate, s->btps_page, s->btps_blkno);
		s->btps_page = NULL;	/* writepage freed the workspace */
	}

	/*
	 * As the last step in the process, construct the metapage and make it
	 * point to the new root (unless we had no data at all, in which case it's
	 * set to point to "P_NONE").  This changes the index to the "valid" state
	 * by filling in a valid magic number in the metapage.
	 */
	metapage = (Page) palloc(BLCKSZ);
	_bt_initmetapage(metapage, rootblkno, rootlevel);
	_bt_blwritepage(wstate, metapage, BTREE_METAPAGE);
}