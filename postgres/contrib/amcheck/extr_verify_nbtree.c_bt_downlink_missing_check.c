#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_14__ {int level; } ;
struct TYPE_16__ {TYPE_1__ btpo; int /*<<< orphan*/  btpo_prev; } ;
struct TYPE_15__ {scalar_t__ targetblock; int targetlsn; int /*<<< orphan*/  rel; int /*<<< orphan*/  target; int /*<<< orphan*/  downlinkfilter; scalar_t__ rightsplit; scalar_t__ readonly; scalar_t__ heapallindexed; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__ BtreeCheckState ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BTreeInnerTupleGetDownLink (scalar_t__) ; 
 scalar_t__ BTreeTupleGetTopParent (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERRCODE_NO_DATA ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  P_FIRSTDATAKEY (TYPE_3__*) ; 
 int /*<<< orphan*/  P_HIKEY ; 
 int /*<<< orphan*/  P_IGNORE (TYPE_3__*) ; 
 scalar_t__ P_ISDELETED (TYPE_3__*) ; 
 scalar_t__ P_ISHALFDEAD (TYPE_3__*) ; 
 scalar_t__ P_ISLEAF (TYPE_3__*) ; 
 scalar_t__ P_ISROOT (TYPE_3__*) ; 
 int /*<<< orphan*/  P_RIGHTMOST (TYPE_3__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemIdCareful (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bloom_lacks_element (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,scalar_t__,scalar_t__,int,...) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palloc_btree_page (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bt_downlink_missing_check(BtreeCheckState *state)
{
	BTPageOpaque topaque = (BTPageOpaque) PageGetSpecialPointer(state->target);
	ItemId		itemid;
	IndexTuple	itup;
	Page		child;
	BTPageOpaque copaque;
	uint32		level;
	BlockNumber childblk;

	Assert(state->heapallindexed && state->readonly);
	Assert(!P_IGNORE(topaque));

	/* No next level up with downlinks to fingerprint from the true root */
	if (P_ISROOT(topaque))
		return;

	/*
	 * Incomplete (interrupted) page splits can account for the lack of a
	 * downlink.  Some inserting transaction should eventually complete the
	 * page split in passing, when it notices that the left sibling page is
	 * P_INCOMPLETE_SPLIT().
	 *
	 * In general, VACUUM is not prepared for there to be no downlink to a
	 * page that it deletes.  This is the main reason why the lack of a
	 * downlink can be reported as corruption here.  It's not obvious that an
	 * invalid missing downlink can result in wrong answers to queries,
	 * though, since index scans that land on the child may end up
	 * consistently moving right. The handling of concurrent page splits (and
	 * page deletions) within _bt_moveright() cannot distinguish
	 * inconsistencies that last for a moment from inconsistencies that are
	 * permanent and irrecoverable.
	 *
	 * VACUUM isn't even prepared to delete pages that have no downlink due to
	 * an incomplete page split, but it can detect and reason about that case
	 * by design, so it shouldn't be taken to indicate corruption.  See
	 * _bt_pagedel() for full details.
	 */
	if (state->rightsplit)
	{
		ereport(DEBUG1,
				(errcode(ERRCODE_NO_DATA),
				 errmsg("harmless interrupted page split detected in index %s",
						RelationGetRelationName(state->rel)),
				 errdetail_internal("Block=%u level=%u left sibling=%u page lsn=%X/%X.",
									state->targetblock, topaque->btpo.level,
									topaque->btpo_prev,
									(uint32) (state->targetlsn >> 32),
									(uint32) state->targetlsn)));
		return;
	}

	/* Target's downlink is typically present in parent/fingerprinted */
	if (!bloom_lacks_element(state->downlinkfilter,
							 (unsigned char *) &state->targetblock,
							 sizeof(BlockNumber)))
		return;

	/*
	 * Target is probably the "top parent" of a multi-level page deletion.
	 * We'll need to descend the subtree to make sure that descendant pages
	 * are consistent with that, though.
	 *
	 * If the target page (which must be non-ignorable) is a leaf page, then
	 * clearly it can't be the top parent.  The lack of a downlink is probably
	 * a symptom of a broad problem that could just as easily cause
	 * inconsistencies anywhere else.
	 */
	if (P_ISLEAF(topaque))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("leaf index block lacks downlink in index \"%s\"",
						RelationGetRelationName(state->rel)),
				 errdetail_internal("Block=%u page lsn=%X/%X.",
									state->targetblock,
									(uint32) (state->targetlsn >> 32),
									(uint32) state->targetlsn)));

	/* Descend from the target page, which is an internal page */
	elog(DEBUG1, "checking for interrupted multi-level deletion due to missing downlink in index \"%s\"",
		 RelationGetRelationName(state->rel));

	level = topaque->btpo.level;
	itemid = PageGetItemIdCareful(state, state->targetblock, state->target,
								  P_FIRSTDATAKEY(topaque));
	itup = (IndexTuple) PageGetItem(state->target, itemid);
	childblk = BTreeInnerTupleGetDownLink(itup);
	for (;;)
	{
		CHECK_FOR_INTERRUPTS();

		child = palloc_btree_page(state, childblk);
		copaque = (BTPageOpaque) PageGetSpecialPointer(child);

		if (P_ISLEAF(copaque))
			break;

		/* Do an extra sanity check in passing on internal pages */
		if (copaque->btpo.level != level - 1)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg_internal("downlink points to block in index \"%s\" whose level is not one level down",
									 RelationGetRelationName(state->rel)),
					 errdetail_internal("Top parent/target block=%u block pointed to=%u expected level=%u level in pointed to block=%u.",
										state->targetblock, childblk,
										level - 1, copaque->btpo.level)));

		level = copaque->btpo.level;
		itemid = PageGetItemIdCareful(state, childblk, child,
									  P_FIRSTDATAKEY(copaque));
		itup = (IndexTuple) PageGetItem(child, itemid);
		childblk = BTreeInnerTupleGetDownLink(itup);
		/* Be slightly more pro-active in freeing this memory, just in case */
		pfree(child);
	}

	/*
	 * Since there cannot be a concurrent VACUUM operation in readonly mode,
	 * and since a page has no links within other pages (siblings and parent)
	 * once it is marked fully deleted, it should be impossible to land on a
	 * fully deleted page.  See bt_downlink_check() for further details.
	 *
	 * The bt_downlink_check() P_ISDELETED() check is repeated here because
	 * bt_downlink_check() does not visit pages reachable through negative
	 * infinity items.  Besides, bt_downlink_check() is unwilling to descend
	 * multiple levels.  (The similar bt_downlink_check() P_ISDELETED() check
	 * within bt_check_level_from_leftmost() won't reach the page either,
	 * since the leaf's live siblings should have their sibling links updated
	 * to bypass the deletion target page when it is marked fully dead.)
	 *
	 * If this error is raised, it might be due to a previous multi-level page
	 * deletion that failed to realize that it wasn't yet safe to mark the
	 * leaf page as fully dead.  A "dangling downlink" will still remain when
	 * this happens.  The fact that the dangling downlink's page (the leaf's
	 * parent/ancestor page) lacked a downlink is incidental.
	 */
	if (P_ISDELETED(copaque))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg_internal("downlink to deleted leaf page found in index \"%s\"",
								 RelationGetRelationName(state->rel)),
				 errdetail_internal("Top parent/target block=%u leaf block=%u top parent/target lsn=%X/%X.",
									state->targetblock, childblk,
									(uint32) (state->targetlsn >> 32),
									(uint32) state->targetlsn)));

	/*
	 * Iff leaf page is half-dead, its high key top parent link should point
	 * to what VACUUM considered to be the top parent page at the instant it
	 * was interrupted.  Provided the high key link actually points to the
	 * target page, the missing downlink we detected is consistent with there
	 * having been an interrupted multi-level page deletion.  This means that
	 * the subtree with the target page at its root (a page deletion chain) is
	 * in a consistent state, enabling VACUUM to resume deleting the entire
	 * chain the next time it encounters the half-dead leaf page.
	 */
	if (P_ISHALFDEAD(copaque) && !P_RIGHTMOST(copaque))
	{
		itemid = PageGetItemIdCareful(state, childblk, child, P_HIKEY);
		itup = (IndexTuple) PageGetItem(child, itemid);
		if (BTreeTupleGetTopParent(itup) == state->targetblock)
			return;
	}

	ereport(ERROR,
			(errcode(ERRCODE_INDEX_CORRUPTED),
			 errmsg("internal index block lacks downlink in index \"%s\"",
					RelationGetRelationName(state->rel)),
			 errdetail_internal("Block=%u level=%u page lsn=%X/%X.",
								state->targetblock, topaque->btpo.level,
								(uint32) (state->targetlsn >> 32),
								(uint32) state->targetlsn)));
}