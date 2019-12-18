#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int int16 ;
struct TYPE_8__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_7__ {int newitemoff; int newitemsz; int minfirstrightsz; int olddataitemstotal; TYPE_4__* newitem; int /*<<< orphan*/  rel; int /*<<< orphan*/  page; int /*<<< orphan*/  is_rightmost; scalar_t__ is_leaf; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_tid; } ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__ FindSplitData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int OffsetNumberPrev (int) ; 
 int P_FIRSTKEY ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _bt_adjacenthtid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _bt_keep_natts_fast (int /*<<< orphan*/ ,TYPE_1__*,TYPE_4__*) ; 

__attribute__((used)) static bool
_bt_afternewitemoff(FindSplitData *state, OffsetNumber maxoff,
					int leaffillfactor, bool *usemult)
{
	int16		nkeyatts;
	ItemId		itemid;
	IndexTuple	tup;
	int			keepnatts;

	Assert(state->is_leaf && !state->is_rightmost);

	nkeyatts = IndexRelationGetNumberOfKeyAttributes(state->rel);

	/* Single key indexes not considered here */
	if (nkeyatts == 1)
		return false;

	/* Ascending insertion pattern never inferred when new item is first */
	if (state->newitemoff == P_FIRSTKEY)
		return false;

	/*
	 * Only apply optimization on pages with equisized tuples, since ordinal
	 * keys are likely to be fixed-width.  Testing if the new tuple is
	 * variable width directly might also work, but that fails to apply the
	 * optimization to indexes with a numeric_ops attribute.
	 *
	 * Conclude that page has equisized tuples when the new item is the same
	 * width as the smallest item observed during pass over page, and other
	 * non-pivot tuples must be the same width as well.  (Note that the
	 * possibly-truncated existing high key isn't counted in
	 * olddataitemstotal, and must be subtracted from maxoff.)
	 */
	if (state->newitemsz != state->minfirstrightsz)
		return false;
	if (state->newitemsz * (maxoff - 1) != state->olddataitemstotal)
		return false;

	/*
	 * Avoid applying optimization when tuples are wider than a tuple
	 * consisting of two non-NULL int8/int64 attributes (or four non-NULL
	 * int4/int32 attributes)
	 */
	if (state->newitemsz >
		MAXALIGN(sizeof(IndexTupleData) + sizeof(int64) * 2) +
		sizeof(ItemIdData))
		return false;

	/*
	 * At least the first attribute's value must be equal to the corresponding
	 * value in previous tuple to apply optimization.  New item cannot be a
	 * duplicate, either.
	 *
	 * Handle case where new item is to the right of all items on the existing
	 * page.  This is suggestive of monotonically increasing insertions in
	 * itself, so the "heap TID adjacency" test is not applied here.
	 */
	if (state->newitemoff > maxoff)
	{
		itemid = PageGetItemId(state->page, maxoff);
		tup = (IndexTuple) PageGetItem(state->page, itemid);
		keepnatts = _bt_keep_natts_fast(state->rel, tup, state->newitem);

		if (keepnatts > 1 && keepnatts <= nkeyatts)
		{
			*usemult = true;
			return true;
		}

		return false;
	}

	/*
	 * "Low cardinality leading column, high cardinality suffix column"
	 * indexes with a random insertion pattern (e.g., an index with a boolean
	 * column, such as an index on '(book_is_in_print, book_isbn)') present us
	 * with a risk of consistently misapplying the optimization.  We're
	 * willing to accept very occasional misapplication of the optimization,
	 * provided the cases where we get it wrong are rare and self-limiting.
	 *
	 * Heap TID adjacency strongly suggests that the item just to the left was
	 * inserted very recently, which limits overapplication of the
	 * optimization.  Besides, all inappropriate cases triggered here will
	 * still split in the middle of the page on average.
	 */
	itemid = PageGetItemId(state->page, OffsetNumberPrev(state->newitemoff));
	tup = (IndexTuple) PageGetItem(state->page, itemid);
	/* Do cheaper test first */
	if (!_bt_adjacenthtid(&tup->t_tid, &state->newitem->t_tid))
		return false;
	/* Check same conditions as rightmost item case, too */
	keepnatts = _bt_keep_natts_fast(state->rel, tup, state->newitem);

	if (keepnatts > 1 && keepnatts <= nkeyatts)
	{
		double		interp = (double) state->newitemoff / ((double) maxoff + 1);
		double		leaffillfactormult = (double) leaffillfactor / 100.0;

		/*
		 * Don't allow caller to split after a new item when it will result in
		 * a split point to the right of the point that a leaf fillfactor
		 * split would use -- have caller apply leaf fillfactor instead
		 */
		*usemult = interp > leaffillfactormult;

		return true;
	}

	return false;
}