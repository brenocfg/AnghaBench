#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int minfirstrightsz; scalar_t__ newitem; int /*<<< orphan*/  rel; int /*<<< orphan*/  page; scalar_t__ is_rightmost; int /*<<< orphan*/  is_leaf; } ;
typedef  int /*<<< orphan*/  SplitPoint ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  FindSplitStrat ;
typedef  TYPE_1__ FindSplitData ;

/* Variables and functions */
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_HIKEY ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLIT_DEFAULT ; 
 int /*<<< orphan*/  SPLIT_MANY_DUPLICATES ; 
 int /*<<< orphan*/  SPLIT_SINGLE_VALUE ; 
 int /*<<< orphan*/  _bt_interval_edges (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int _bt_keep_natts_fast (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ _bt_split_firstright (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ _bt_split_lastleft (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_bt_strategy(FindSplitData *state, SplitPoint *leftpage,
			 SplitPoint *rightpage, FindSplitStrat *strategy)
{
	IndexTuple	leftmost,
				rightmost;
	SplitPoint *leftinterval,
			   *rightinterval;
	int			perfectpenalty;
	int			indnkeyatts = IndexRelationGetNumberOfKeyAttributes(state->rel);

	/* Assume that alternative strategy won't be used for now */
	*strategy = SPLIT_DEFAULT;

	/*
	 * Use smallest observed first right item size for entire page as perfect
	 * penalty on internal pages.  This can save cycles in the common case
	 * where most or all splits (not just splits within interval) have first
	 * right tuples that are the same size.
	 */
	if (!state->is_leaf)
		return state->minfirstrightsz;

	/*
	 * Use leftmost and rightmost tuples from leftmost and rightmost splits in
	 * current split interval
	 */
	_bt_interval_edges(state, &leftinterval, &rightinterval);
	leftmost = _bt_split_lastleft(state, leftinterval);
	rightmost = _bt_split_firstright(state, rightinterval);

	/*
	 * If initial split interval can produce a split point that will at least
	 * avoid appending a heap TID in new high key, we're done.  Finish split
	 * with default strategy and initial split interval.
	 */
	perfectpenalty = _bt_keep_natts_fast(state->rel, leftmost, rightmost);
	if (perfectpenalty <= indnkeyatts)
		return perfectpenalty;

	/*
	 * Work out how caller should finish split when even their "perfect"
	 * penalty for initial/default split interval indicates that the interval
	 * does not contain even a single split that avoids appending a heap TID.
	 *
	 * Use the leftmost split's lastleft tuple and the rightmost split's
	 * firstright tuple to assess every possible split.
	 */
	leftmost = _bt_split_lastleft(state, leftpage);
	rightmost = _bt_split_firstright(state, rightpage);

	/*
	 * If page (including new item) has many duplicates but is not entirely
	 * full of duplicates, a many duplicates strategy split will be performed.
	 * If page is entirely full of duplicates, a single value strategy split
	 * will be performed.
	 */
	perfectpenalty = _bt_keep_natts_fast(state->rel, leftmost, rightmost);
	if (perfectpenalty <= indnkeyatts)
	{
		*strategy = SPLIT_MANY_DUPLICATES;

		/*
		 * Many duplicates strategy should split at either side the group of
		 * duplicates that enclose the delta-optimal split point.  Return
		 * indnkeyatts rather than the true perfect penalty to make that
		 * happen.  (If perfectpenalty was returned here then low cardinality
		 * composite indexes could have continual unbalanced splits.)
		 *
		 * Note that caller won't go through with a many duplicates split in
		 * rare cases where it looks like there are ever-decreasing insertions
		 * to the immediate right of the split point.  This must happen just
		 * before a final decision is made, within _bt_bestsplitloc().
		 */
		return indnkeyatts;
	}

	/*
	 * Single value strategy is only appropriate with ever-increasing heap
	 * TIDs; otherwise, original default strategy split should proceed to
	 * avoid pathological performance.  Use page high key to infer if this is
	 * the rightmost page among pages that store the same duplicate value.
	 * This should not prevent insertions of heap TIDs that are slightly out
	 * of order from using single value strategy, since that's expected with
	 * concurrent inserters of the same duplicate value.
	 */
	else if (state->is_rightmost)
		*strategy = SPLIT_SINGLE_VALUE;
	else
	{
		ItemId		itemid;
		IndexTuple	hikey;

		itemid = PageGetItemId(state->page, P_HIKEY);
		hikey = (IndexTuple) PageGetItem(state->page, itemid);
		perfectpenalty = _bt_keep_natts_fast(state->rel, hikey,
											 state->newitem);
		if (perfectpenalty <= indnkeyatts)
			*strategy = SPLIT_SINGLE_VALUE;
		else
		{
			/*
			 * Have caller finish split using default strategy, since page
			 * does not appear to be the rightmost page for duplicates of the
			 * value the page is filled with
			 */
		}
	}

	return perfectpenalty;
}