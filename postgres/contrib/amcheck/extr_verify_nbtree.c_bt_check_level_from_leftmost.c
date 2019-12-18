#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ level; } ;
struct TYPE_22__ {scalar_t__ btpo_prev; scalar_t__ btpo_next; TYPE_1__ btpo; } ;
struct TYPE_21__ {int /*<<< orphan*/  targetcontext; int /*<<< orphan*/  rightsplit; int /*<<< orphan*/  rel; scalar_t__ readonly; int /*<<< orphan*/  target; scalar_t__ targetblock; int /*<<< orphan*/  targetlsn; } ;
struct TYPE_20__ {scalar_t__ leftmost; scalar_t__ level; int istruerootlevel; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__ BtreeLevel ;
typedef  TYPE_3__ BtreeCheckState ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_4__* BTPageOpaque ;

/* Variables and functions */
 scalar_t__ BTreeInnerTupleGetDownLink (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERRCODE_NO_DATA ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidBlockNumber ; 
 void* InvalidBtreeLevel ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_FIRSTDATAKEY (TYPE_4__*) ; 
 scalar_t__ P_IGNORE (TYPE_4__*) ; 
 int /*<<< orphan*/  P_INCOMPLETE_SPLIT (TYPE_4__*) ; 
 scalar_t__ P_ISDELETED (TYPE_4__*) ; 
 int /*<<< orphan*/  P_ISLEAF (TYPE_4__*) ; 
 int /*<<< orphan*/  P_ISROOT (TYPE_4__*) ; 
 int /*<<< orphan*/  P_LEFTMOST (TYPE_4__*) ; 
 scalar_t__ P_NONE ; 
 scalar_t__ P_RIGHTMOST (TYPE_4__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemIdCareful (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetLSN (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_target_page_check (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  palloc_btree_page (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static BtreeLevel
bt_check_level_from_leftmost(BtreeCheckState *state, BtreeLevel level)
{
	/* State to establish early, concerning entire level */
	BTPageOpaque opaque;
	MemoryContext oldcontext;
	BtreeLevel	nextleveldown;

	/* Variables for iterating across level using right links */
	BlockNumber leftcurrent = P_NONE;
	BlockNumber current = level.leftmost;

	/* Initialize return state */
	nextleveldown.leftmost = InvalidBlockNumber;
	nextleveldown.level = InvalidBtreeLevel;
	nextleveldown.istruerootlevel = false;

	/* Use page-level context for duration of this call */
	oldcontext = MemoryContextSwitchTo(state->targetcontext);

	elog(DEBUG2, "verifying level %u%s", level.level,
		 level.istruerootlevel ?
		 " (true root level)" : level.level == 0 ? " (leaf level)" : "");

	do
	{
		/* Don't rely on CHECK_FOR_INTERRUPTS() calls at lower level */
		CHECK_FOR_INTERRUPTS();

		/* Initialize state for this iteration */
		state->targetblock = current;
		state->target = palloc_btree_page(state, state->targetblock);
		state->targetlsn = PageGetLSN(state->target);

		opaque = (BTPageOpaque) PageGetSpecialPointer(state->target);

		if (P_IGNORE(opaque))
		{
			/*
			 * Since there cannot be a concurrent VACUUM operation in readonly
			 * mode, and since a page has no links within other pages
			 * (siblings and parent) once it is marked fully deleted, it
			 * should be impossible to land on a fully deleted page in
			 * readonly mode. See bt_downlink_check() for further details.
			 *
			 * The bt_downlink_check() P_ISDELETED() check is repeated here so
			 * that pages that are only reachable through sibling links get
			 * checked.
			 */
			if (state->readonly && P_ISDELETED(opaque))
				ereport(ERROR,
						(errcode(ERRCODE_INDEX_CORRUPTED),
						 errmsg("downlink or sibling link points to deleted block in index \"%s\"",
								RelationGetRelationName(state->rel)),
						 errdetail_internal("Block=%u left block=%u left link from block=%u.",
											current, leftcurrent, opaque->btpo_prev)));

			if (P_RIGHTMOST(opaque))
				ereport(ERROR,
						(errcode(ERRCODE_INDEX_CORRUPTED),
						 errmsg("block %u fell off the end of index \"%s\"",
								current, RelationGetRelationName(state->rel))));
			else
				ereport(DEBUG1,
						(errcode(ERRCODE_NO_DATA),
						 errmsg("block %u of index \"%s\" ignored",
								current, RelationGetRelationName(state->rel))));
			goto nextpage;
		}
		else if (nextleveldown.leftmost == InvalidBlockNumber)
		{
			/*
			 * A concurrent page split could make the caller supplied leftmost
			 * block no longer contain the leftmost page, or no longer be the
			 * true root, but where that isn't possible due to heavyweight
			 * locking, check that the first valid page meets caller's
			 * expectations.
			 */
			if (state->readonly)
			{
				if (!P_LEFTMOST(opaque))
					ereport(ERROR,
							(errcode(ERRCODE_INDEX_CORRUPTED),
							 errmsg("block %u is not leftmost in index \"%s\"",
									current, RelationGetRelationName(state->rel))));

				if (level.istruerootlevel && !P_ISROOT(opaque))
					ereport(ERROR,
							(errcode(ERRCODE_INDEX_CORRUPTED),
							 errmsg("block %u is not true root in index \"%s\"",
									current, RelationGetRelationName(state->rel))));
			}

			/*
			 * Before beginning any non-trivial examination of level, prepare
			 * state for next bt_check_level_from_leftmost() invocation for
			 * the next level for the next level down (if any).
			 *
			 * There should be at least one non-ignorable page per level,
			 * unless this is the leaf level, which is assumed by caller to be
			 * final level.
			 */
			if (!P_ISLEAF(opaque))
			{
				IndexTuple	itup;
				ItemId		itemid;

				/* Internal page -- downlink gets leftmost on next level */
				itemid = PageGetItemIdCareful(state, state->targetblock,
											  state->target,
											  P_FIRSTDATAKEY(opaque));
				itup = (IndexTuple) PageGetItem(state->target, itemid);
				nextleveldown.leftmost = BTreeInnerTupleGetDownLink(itup);
				nextleveldown.level = opaque->btpo.level - 1;
			}
			else
			{
				/*
				 * Leaf page -- final level caller must process.
				 *
				 * Note that this could also be the root page, if there has
				 * been no root page split yet.
				 */
				nextleveldown.leftmost = P_NONE;
				nextleveldown.level = InvalidBtreeLevel;
			}

			/*
			 * Finished setting up state for this call/level.  Control will
			 * never end up back here in any future loop iteration for this
			 * level.
			 */
		}

		/*
		 * readonly mode can only ever land on live pages and half-dead pages,
		 * so sibling pointers should always be in mutual agreement
		 */
		if (state->readonly && opaque->btpo_prev != leftcurrent)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("left link/right link pair in index \"%s\" not in agreement",
							RelationGetRelationName(state->rel)),
					 errdetail_internal("Block=%u left block=%u left link from block=%u.",
										current, leftcurrent, opaque->btpo_prev)));

		/* Check level, which must be valid for non-ignorable page */
		if (level.level != opaque->btpo.level)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("leftmost down link for level points to block in index \"%s\" whose level is not one level down",
							RelationGetRelationName(state->rel)),
					 errdetail_internal("Block pointed to=%u expected level=%u level in pointed to block=%u.",
										current, level.level, opaque->btpo.level)));

		/* Verify invariants for page */
		bt_target_page_check(state);

nextpage:

		/* Try to detect circular links */
		if (current == leftcurrent || current == opaque->btpo_prev)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("circular link chain found in block %u of index \"%s\"",
							current, RelationGetRelationName(state->rel))));

		/*
		 * Record if page that is about to become target is the right half of
		 * an incomplete page split.  This can go stale immediately in
		 * !readonly case.
		 */
		state->rightsplit = P_INCOMPLETE_SPLIT(opaque);

		leftcurrent = current;
		current = opaque->btpo_next;

		/* Free page and associated memory for this iteration */
		MemoryContextReset(state->targetcontext);
	}
	while (current != P_NONE);

	/* Don't change context for caller */
	MemoryContextSwitchTo(oldcontext);

	return nextleveldown;
}