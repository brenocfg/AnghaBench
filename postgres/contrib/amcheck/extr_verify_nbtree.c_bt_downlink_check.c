#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_5__ {int targetlsn; int /*<<< orphan*/  targetblock; int /*<<< orphan*/  rel; int /*<<< orphan*/  readonly; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_1__ BtreeCheckState ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BTScanInsert ;
typedef  scalar_t__ BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ P_FIRSTDATAKEY (scalar_t__) ; 
 scalar_t__ P_ISDELETED (scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invariant_l_nontarget_offset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ offset_is_negative_infinity (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  palloc_btree_page (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bt_downlink_check(BtreeCheckState *state, BTScanInsert targetkey,
				  BlockNumber childblock)
{
	OffsetNumber offset;
	OffsetNumber maxoffset;
	Page		child;
	BTPageOpaque copaque;

	/*
	 * Caller must have ShareLock on target relation, because of
	 * considerations around page deletion by VACUUM.
	 *
	 * NB: In general, page deletion deletes the right sibling's downlink, not
	 * the downlink of the page being deleted; the deleted page's downlink is
	 * reused for its sibling.  The key space is thereby consolidated between
	 * the deleted page and its right sibling.  (We cannot delete a parent
	 * page's rightmost child unless it is the last child page, and we intend
	 * to also delete the parent itself.)
	 *
	 * If this verification happened without a ShareLock, the following race
	 * condition could cause false positives:
	 *
	 * In general, concurrent page deletion might occur, including deletion of
	 * the left sibling of the child page that is examined here.  If such a
	 * page deletion were to occur, closely followed by an insertion into the
	 * newly expanded key space of the child, a window for the false positive
	 * opens up: the stale parent/target downlink originally followed to get
	 * to the child legitimately ceases to be a lower bound on all items in
	 * the page, since the key space was concurrently expanded "left".
	 * (Insertion followed the "new" downlink for the child, not our now-stale
	 * downlink, which was concurrently physically removed in target/parent as
	 * part of deletion's first phase.)
	 *
	 * Note that while the cross-page-same-level last item check uses a trick
	 * that allows it to perform verification for !readonly callers, a similar
	 * trick seems difficult here.  The trick that that other check uses is,
	 * in essence, to lock down race conditions to those that occur due to
	 * concurrent page deletion of the target; that's a race that can be
	 * reliably detected before actually reporting corruption.
	 *
	 * On the other hand, we'd need to lock down race conditions involving
	 * deletion of child's left page, for long enough to read the child page
	 * into memory (in other words, a scheme with concurrently held buffer
	 * locks on both child and left-of-child pages).  That's unacceptable for
	 * amcheck functions on general principle, though.
	 */
	Assert(state->readonly);

	/*
	 * Verify child page has the downlink key from target page (its parent) as
	 * a lower bound; downlink must be strictly less than all keys on the
	 * page.
	 *
	 * Check all items, rather than checking just the first and trusting that
	 * the operator class obeys the transitive law.
	 */
	child = palloc_btree_page(state, childblock);
	copaque = (BTPageOpaque) PageGetSpecialPointer(child);
	maxoffset = PageGetMaxOffsetNumber(child);

	/*
	 * Since there cannot be a concurrent VACUUM operation in readonly mode,
	 * and since a page has no links within other pages (siblings and parent)
	 * once it is marked fully deleted, it should be impossible to land on a
	 * fully deleted page.
	 *
	 * It does not quite make sense to enforce that the page cannot even be
	 * half-dead, despite the fact the downlink is modified at the same stage
	 * that the child leaf page is marked half-dead.  That's incorrect because
	 * there may occasionally be multiple downlinks from a chain of pages
	 * undergoing deletion, where multiple successive calls are made to
	 * _bt_unlink_halfdead_page() by VACUUM before it can finally safely mark
	 * the leaf page as fully dead.  While _bt_mark_page_halfdead() usually
	 * removes the downlink to the leaf page that is marked half-dead, that's
	 * not guaranteed, so it's possible we'll land on a half-dead page with a
	 * downlink due to an interrupted multi-level page deletion.
	 *
	 * We go ahead with our checks if the child page is half-dead.  It's safe
	 * to do so because we do not test the child's high key, so it does not
	 * matter that the original high key will have been replaced by a dummy
	 * truncated high key within _bt_mark_page_halfdead().  All other page
	 * items are left intact on a half-dead page, so there is still something
	 * to test.
	 */
	if (P_ISDELETED(copaque))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("downlink to deleted page found in index \"%s\"",
						RelationGetRelationName(state->rel)),
				 errdetail_internal("Parent block=%u child block=%u parent page lsn=%X/%X.",
									state->targetblock, childblock,
									(uint32) (state->targetlsn >> 32),
									(uint32) state->targetlsn)));

	for (offset = P_FIRSTDATAKEY(copaque);
		 offset <= maxoffset;
		 offset = OffsetNumberNext(offset))
	{
		/*
		 * Skip comparison of target page key against "negative infinity"
		 * item, if any.  Checking it would indicate that it's not a strict
		 * lower bound, but that's only because of the hard-coding for
		 * negative infinity items within _bt_compare().
		 *
		 * If nbtree didn't truncate negative infinity tuples during internal
		 * page splits then we'd expect child's negative infinity key to be
		 * equal to the scankey/downlink from target/parent (it would be a
		 * "low key" in this hypothetical scenario, and so it would still need
		 * to be treated as a special case here).
		 *
		 * Negative infinity items can be thought of as a strict lower bound
		 * that works transitively, with the last non-negative-infinity pivot
		 * followed during a descent from the root as its "true" strict lower
		 * bound.  Only a small number of negative infinity items are truly
		 * negative infinity; those that are the first items of leftmost
		 * internal pages.  In more general terms, a negative infinity item is
		 * only negative infinity with respect to the subtree that the page is
		 * at the root of.
		 *
		 * See also: bt_rootdescend(), which can even detect transitive
		 * inconsistencies on cousin leaf pages.
		 */
		if (offset_is_negative_infinity(copaque, offset))
			continue;

		if (!invariant_l_nontarget_offset(state, targetkey, childblock, child,
										  offset))
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg("down-link lower bound invariant violated for index \"%s\"",
							RelationGetRelationName(state->rel)),
					 errdetail_internal("Parent block=%u child index tid=(%u,%u) parent page lsn=%X/%X.",
										state->targetblock, childblock, offset,
										(uint32) (state->targetlsn >> 32),
										(uint32) state->targetlsn)));
	}

	pfree(child);
}