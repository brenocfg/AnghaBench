#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int newitemsz; int is_leaf; int is_rightmost; int leftspace; int rightspace; int olddataitemstotal; int maxsplits; int nsplits; int interval; TYPE_1__* splits; int /*<<< orphan*/  rel; scalar_t__ newitemoff; int /*<<< orphan*/  minfirstrightsz; int /*<<< orphan*/  newitem; int /*<<< orphan*/  page; } ;
struct TYPE_12__ {scalar_t__ firstoldonright; scalar_t__ newitemonleft; } ;
typedef  TYPE_1__ SplitPoint ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  scalar_t__ FindSplitStrat ;
typedef  TYPE_2__ FindSplitData ;
typedef  int /*<<< orphan*/  BTPageOpaqueData ;
typedef  scalar_t__ BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTREE_DEFAULT_FILLFACTOR ; 
 double BTREE_NONLEAF_FILLFACTOR ; 
 double BTREE_SINGLEVAL_FILLFACTOR ; 
 int /*<<< orphan*/  ERROR ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  MAX_INTERNAL_INTERVAL ; 
 int /*<<< orphan*/  MAX_LEAF_INTERVAL ; 
 int /*<<< orphan*/  Max (int,double) ; 
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ P_FIRSTDATAKEY (scalar_t__) ; 
 scalar_t__ P_HIKEY ; 
 int P_ISLEAF (scalar_t__) ; 
 int P_RIGHTMOST (scalar_t__) ; 
 scalar_t__ PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int PageGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int RelationGetFillFactor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 scalar_t__ SPLIT_DEFAULT ; 
 scalar_t__ SPLIT_MANY_DUPLICATES ; 
 scalar_t__ SPLIT_SINGLE_VALUE ; 
 int SizeOfPageHeaderData ; 
 scalar_t__ _bt_afternewitemoff (TYPE_2__*,scalar_t__,int,int*) ; 
 scalar_t__ _bt_bestsplitloc (TYPE_2__*,int,int*,scalar_t__) ; 
 int /*<<< orphan*/  _bt_deltasortsplits (TYPE_2__*,double,int) ; 
 int /*<<< orphan*/  _bt_recsplitloc (TYPE_2__*,scalar_t__,int,int,int) ; 
 int _bt_strategy (TYPE_2__*,TYPE_1__*,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

OffsetNumber
_bt_findsplitloc(Relation rel,
				 Page page,
				 OffsetNumber newitemoff,
				 Size newitemsz,
				 IndexTuple newitem,
				 bool *newitemonleft)
{
	BTPageOpaque opaque;
	int			leftspace,
				rightspace,
				olddataitemstotal,
				olddataitemstoleft,
				perfectpenalty,
				leaffillfactor;
	FindSplitData state;
	FindSplitStrat strategy;
	ItemId		itemid;
	OffsetNumber offnum,
				maxoff,
				foundfirstright;
	double		fillfactormult;
	bool		usemult;
	SplitPoint	leftpage,
				rightpage;

	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	maxoff = PageGetMaxOffsetNumber(page);

	/* Total free space available on a btree page, after fixed overhead */
	leftspace = rightspace =
		PageGetPageSize(page) - SizeOfPageHeaderData -
		MAXALIGN(sizeof(BTPageOpaqueData));

	/* The right page will have the same high key as the old page */
	if (!P_RIGHTMOST(opaque))
	{
		itemid = PageGetItemId(page, P_HIKEY);
		rightspace -= (int) (MAXALIGN(ItemIdGetLength(itemid)) +
							 sizeof(ItemIdData));
	}

	/* Count up total space in data items before actually scanning 'em */
	olddataitemstotal = rightspace - (int) PageGetExactFreeSpace(page);
	leaffillfactor = RelationGetFillFactor(rel, BTREE_DEFAULT_FILLFACTOR);

	/* Passed-in newitemsz is MAXALIGNED but does not include line pointer */
	newitemsz += sizeof(ItemIdData);
	state.rel = rel;
	state.page = page;
	state.newitem = newitem;
	state.newitemsz = newitemsz;
	state.is_leaf = P_ISLEAF(opaque);
	state.is_rightmost = P_RIGHTMOST(opaque);
	state.leftspace = leftspace;
	state.rightspace = rightspace;
	state.olddataitemstotal = olddataitemstotal;
	state.minfirstrightsz = SIZE_MAX;
	state.newitemoff = newitemoff;

	/*
	 * maxsplits should never exceed maxoff because there will be at most as
	 * many candidate split points as there are points _between_ tuples, once
	 * you imagine that the new item is already on the original page (the
	 * final number of splits may be slightly lower because not all points
	 * between tuples will be legal).
	 */
	state.maxsplits = maxoff;
	state.splits = palloc(sizeof(SplitPoint) * state.maxsplits);
	state.nsplits = 0;

	/*
	 * Scan through the data items and calculate space usage for a split at
	 * each possible position
	 */
	olddataitemstoleft = 0;

	for (offnum = P_FIRSTDATAKEY(opaque);
		 offnum <= maxoff;
		 offnum = OffsetNumberNext(offnum))
	{
		Size		itemsz;

		itemid = PageGetItemId(page, offnum);
		itemsz = MAXALIGN(ItemIdGetLength(itemid)) + sizeof(ItemIdData);

		/*
		 * When item offset number is not newitemoff, neither side of the
		 * split can be newitem.  Record a split after the previous data item
		 * from original page, but before the current data item from original
		 * page. (_bt_recsplitloc() will reject the split when there are no
		 * previous items, which we rely on.)
		 */
		if (offnum < newitemoff)
			_bt_recsplitloc(&state, offnum, false, olddataitemstoleft, itemsz);
		else if (offnum > newitemoff)
			_bt_recsplitloc(&state, offnum, true, olddataitemstoleft, itemsz);
		else
		{
			/*
			 * Record a split after all "offnum < newitemoff" original page
			 * data items, but before newitem
			 */
			_bt_recsplitloc(&state, offnum, false, olddataitemstoleft, itemsz);

			/*
			 * Record a split after newitem, but before data item from
			 * original page at offset newitemoff/current offset
			 */
			_bt_recsplitloc(&state, offnum, true, olddataitemstoleft, itemsz);
		}

		olddataitemstoleft += itemsz;
	}

	/*
	 * Record a split after all original page data items, but before newitem.
	 * (Though only when it's possible that newitem will end up alone on new
	 * right page.)
	 */
	Assert(olddataitemstoleft == olddataitemstotal);
	if (newitemoff > maxoff)
		_bt_recsplitloc(&state, newitemoff, false, olddataitemstotal, 0);

	/*
	 * I believe it is not possible to fail to find a feasible split, but just
	 * in case ...
	 */
	if (state.nsplits == 0)
		elog(ERROR, "could not find a feasible split point for index \"%s\"",
			 RelationGetRelationName(rel));

	/*
	 * Start search for a split point among list of legal split points.  Give
	 * primary consideration to equalizing available free space in each half
	 * of the split initially (start with default strategy), while applying
	 * rightmost and split-after-new-item optimizations where appropriate.
	 * Either of the two other fallback strategies may be required for cases
	 * with a large number of duplicates around the original/space-optimal
	 * split point.
	 *
	 * Default strategy gives some weight to suffix truncation in deciding a
	 * split point on leaf pages.  It attempts to select a split point where a
	 * distinguishing attribute appears earlier in the new high key for the
	 * left side of the split, in order to maximize the number of trailing
	 * attributes that can be truncated away.  Only candidate split points
	 * that imply an acceptable balance of free space on each side are
	 * considered.
	 */
	if (!state.is_leaf)
	{
		/* fillfactormult only used on rightmost page */
		usemult = state.is_rightmost;
		fillfactormult = BTREE_NONLEAF_FILLFACTOR / 100.0;
	}
	else if (state.is_rightmost)
	{
		/* Rightmost leaf page --  fillfactormult always used */
		usemult = true;
		fillfactormult = leaffillfactor / 100.0;
	}
	else if (_bt_afternewitemoff(&state, maxoff, leaffillfactor, &usemult))
	{
		/*
		 * New item inserted at rightmost point among a localized grouping on
		 * a leaf page -- apply "split after new item" optimization, either by
		 * applying leaf fillfactor multiplier, or by choosing the exact split
		 * point that leaves the new item as last on the left. (usemult is set
		 * for us.)
		 */
		if (usemult)
		{
			/* fillfactormult should be set based on leaf fillfactor */
			fillfactormult = leaffillfactor / 100.0;
		}
		else
		{
			/* find precise split point after newitemoff */
			for (int i = 0; i < state.nsplits; i++)
			{
				SplitPoint *split = state.splits + i;

				if (split->newitemonleft &&
					newitemoff == split->firstoldonright)
				{
					pfree(state.splits);
					*newitemonleft = true;
					return newitemoff;
				}
			}

			/*
			 * Cannot legally split after newitemoff; proceed with split
			 * without using fillfactor multiplier.  This is defensive, and
			 * should never be needed in practice.
			 */
			fillfactormult = 0.50;
		}
	}
	else
	{
		/* Other leaf page.  50:50 page split. */
		usemult = false;
		/* fillfactormult not used, but be tidy */
		fillfactormult = 0.50;
	}

	/*
	 * Set an initial limit on the split interval/number of candidate split
	 * points as appropriate.  The "Prefix B-Trees" paper refers to this as
	 * sigma l for leaf splits and sigma b for internal ("branch") splits.
	 * It's hard to provide a theoretical justification for the initial size
	 * of the split interval, though it's clear that a small split interval
	 * makes suffix truncation much more effective without noticeably
	 * affecting space utilization over time.
	 */
	state.interval = Min(Max(1, state.nsplits * 0.05),
						 state.is_leaf ? MAX_LEAF_INTERVAL :
						 MAX_INTERNAL_INTERVAL);

	/*
	 * Save leftmost and rightmost splits for page before original ordinal
	 * sort order is lost by delta/fillfactormult sort
	 */
	leftpage = state.splits[0];
	rightpage = state.splits[state.nsplits - 1];

	/* Give split points a fillfactormult-wise delta, and sort on deltas */
	_bt_deltasortsplits(&state, fillfactormult, usemult);

	/*
	 * Determine if default strategy/split interval will produce a
	 * sufficiently distinguishing split, or if we should change strategies.
	 * Alternative strategies change the range of split points that are
	 * considered acceptable (split interval), and possibly change
	 * fillfactormult, in order to deal with pages with a large number of
	 * duplicates gracefully.
	 *
	 * Pass low and high splits for the entire page (actually, they're for an
	 * imaginary version of the page that includes newitem).  These are used
	 * when the initial split interval encloses split points that are full of
	 * duplicates, and we need to consider if it's even possible to avoid
	 * appending a heap TID.
	 */
	perfectpenalty = _bt_strategy(&state, &leftpage, &rightpage, &strategy);

	if (strategy == SPLIT_DEFAULT)
	{
		/*
		 * Default strategy worked out (always works out with internal page).
		 * Original split interval still stands.
		 */
	}

	/*
	 * Many duplicates strategy is used when a heap TID would otherwise be
	 * appended, but the page isn't completely full of logical duplicates.
	 *
	 * The split interval is widened to include all legal candidate split
	 * points.  There might be a few as two distinct values in the whole-page
	 * split interval, though it's also possible that most of the values on
	 * the page are unique.  The final split point will either be to the
	 * immediate left or to the immediate right of the group of duplicate
	 * tuples that enclose the first/delta-optimal split point (perfect
	 * penalty was set so that the lowest delta split point that avoids
	 * appending a heap TID will be chosen).  Maximizing the number of
	 * attributes that can be truncated away is not a goal of the many
	 * duplicates strategy.
	 *
	 * Single value strategy is used when it is impossible to avoid appending
	 * a heap TID.  It arranges to leave the left page very full.  This
	 * maximizes space utilization in cases where tuples with the same
	 * attribute values span many pages.  Newly inserted duplicates will tend
	 * to have higher heap TID values, so we'll end up splitting to the right
	 * consistently.  (Single value strategy is harmless though not
	 * particularly useful with !heapkeyspace indexes.)
	 */
	else if (strategy == SPLIT_MANY_DUPLICATES)
	{
		Assert(state.is_leaf);
		/* Shouldn't try to truncate away extra user attributes */
		Assert(perfectpenalty ==
			   IndexRelationGetNumberOfKeyAttributes(state.rel));
		/* No need to resort splits -- no change in fillfactormult/deltas */
		state.interval = state.nsplits;
	}
	else if (strategy == SPLIT_SINGLE_VALUE)
	{
		Assert(state.is_leaf);
		/* Split near the end of the page */
		usemult = true;
		fillfactormult = BTREE_SINGLEVAL_FILLFACTOR / 100.0;
		/* Resort split points with new delta */
		_bt_deltasortsplits(&state, fillfactormult, usemult);
		/* Appending a heap TID is unavoidable, so interval of 1 is fine */
		state.interval = 1;
	}

	/*
	 * Search among acceptable split points (using final split interval) for
	 * the entry that has the lowest penalty, and is therefore expected to
	 * maximize fan-out.  Sets *newitemonleft for us.
	 */
	foundfirstright = _bt_bestsplitloc(&state, perfectpenalty, newitemonleft,
									   strategy);
	pfree(state.splits);

	return foundfirstright;
}