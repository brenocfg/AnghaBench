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
struct TYPE_6__ {int /*<<< orphan*/  leafTupdesc; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GISTSTATE ;
typedef  int /*<<< orphan*/  GISTENTRY ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GistPageIsLeaf (int /*<<< orphan*/ ) ; 
 int INDEX_MAX_KEYS ; 
 int IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int MAX_RANDOM_VALUE ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistDeCompressAtt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  gistdentryinit (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 float gistpenalty (TYPE_1__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int random () ; 

OffsetNumber
gistchoose(Relation r, Page p, IndexTuple it,	/* it has compressed entry */
		   GISTSTATE *giststate)
{
	OffsetNumber result;
	OffsetNumber maxoff;
	OffsetNumber i;
	float		best_penalty[INDEX_MAX_KEYS];
	GISTENTRY	entry,
				identry[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	int			keep_current_best;

	Assert(!GistPageIsLeaf(p));

	gistDeCompressAtt(giststate, r,
					  it, NULL, (OffsetNumber) 0,
					  identry, isnull);

	/* we'll return FirstOffsetNumber if page is empty (shouldn't happen) */
	result = FirstOffsetNumber;

	/*
	 * The index may have multiple columns, and there's a penalty value for
	 * each column.  The penalty associated with a column that appears earlier
	 * in the index definition is strictly more important than the penalty of
	 * a column that appears later in the index definition.
	 *
	 * best_penalty[j] is the best penalty we have seen so far for column j,
	 * or -1 when we haven't yet examined column j.  Array entries to the
	 * right of the first -1 are undefined.
	 */
	best_penalty[0] = -1;

	/*
	 * If we find a tuple that's exactly as good as the currently best one, we
	 * could use either one.  When inserting a lot of tuples with the same or
	 * similar keys, it's preferable to descend down the same path when
	 * possible, as that's more cache-friendly.  On the other hand, if all
	 * inserts land on the same leaf page after a split, we're never going to
	 * insert anything to the other half of the split, and will end up using
	 * only 50% of the available space.  Distributing the inserts evenly would
	 * lead to better space usage, but that hurts cache-locality during
	 * insertion.  To get the best of both worlds, when we find a tuple that's
	 * exactly as good as the previous best, choose randomly whether to stick
	 * to the old best, or use the new one.  Once we decide to stick to the
	 * old best, we keep sticking to it for any subsequent equally good tuples
	 * we might find.  This favors tuples with low offsets, but still allows
	 * some inserts to go to other equally-good subtrees.
	 *
	 * keep_current_best is -1 if we haven't yet had to make a random choice
	 * whether to keep the current best tuple.  If we have done so, and
	 * decided to keep it, keep_current_best is 1; if we've decided to
	 * replace, keep_current_best is 0.  (This state will be reset to -1 as
	 * soon as we've made the replacement, but sometimes we make the choice in
	 * advance of actually finding a replacement best tuple.)
	 */
	keep_current_best = -1;

	/*
	 * Loop over tuples on page.
	 */
	maxoff = PageGetMaxOffsetNumber(p);
	Assert(maxoff >= FirstOffsetNumber);

	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(p, PageGetItemId(p, i));
		bool		zero_penalty;
		int			j;

		zero_penalty = true;

		/* Loop over index attributes. */
		for (j = 0; j < IndexRelationGetNumberOfKeyAttributes(r); j++)
		{
			Datum		datum;
			float		usize;
			bool		IsNull;

			/* Compute penalty for this column. */
			datum = index_getattr(itup, j + 1, giststate->leafTupdesc,
								  &IsNull);
			gistdentryinit(giststate, j, &entry, datum, r, p, i,
						   false, IsNull);
			usize = gistpenalty(giststate, j, &entry, IsNull,
								&identry[j], isnull[j]);
			if (usize > 0)
				zero_penalty = false;

			if (best_penalty[j] < 0 || usize < best_penalty[j])
			{
				/*
				 * New best penalty for column.  Tentatively select this tuple
				 * as the target, and record the best penalty.  Then reset the
				 * next column's penalty to "unknown" (and indirectly, the
				 * same for all the ones to its right).  This will force us to
				 * adopt this tuple's penalty values as the best for all the
				 * remaining columns during subsequent loop iterations.
				 */
				result = i;
				best_penalty[j] = usize;

				if (j < IndexRelationGetNumberOfKeyAttributes(r) - 1)
					best_penalty[j + 1] = -1;

				/* we have new best, so reset keep-it decision */
				keep_current_best = -1;
			}
			else if (best_penalty[j] == usize)
			{
				/*
				 * The current tuple is exactly as good for this column as the
				 * best tuple seen so far.  The next iteration of this loop
				 * will compare the next column.
				 */
			}
			else
			{
				/*
				 * The current tuple is worse for this column than the best
				 * tuple seen so far.  Skip the remaining columns and move on
				 * to the next tuple, if any.
				 */
				zero_penalty = false;	/* so outer loop won't exit */
				break;
			}
		}

		/*
		 * If we looped past the last column, and did not update "result",
		 * then this tuple is exactly as good as the prior best tuple.
		 */
		if (j == IndexRelationGetNumberOfKeyAttributes(r) && result != i)
		{
			if (keep_current_best == -1)
			{
				/* we didn't make the random choice yet for this old best */
				keep_current_best = (random() <= (MAX_RANDOM_VALUE / 2)) ? 1 : 0;
			}
			if (keep_current_best == 0)
			{
				/* we choose to use the new tuple */
				result = i;
				/* choose again if there are even more exactly-as-good ones */
				keep_current_best = -1;
			}
		}

		/*
		 * If we find a tuple with zero penalty for all columns, and we've
		 * decided we don't want to search for another tuple with equal
		 * penalty, there's no need to examine remaining tuples; just break
		 * out of the loop and return it.
		 */
		if (zero_penalty)
		{
			if (keep_current_best == -1)
			{
				/* we didn't make the random choice yet for this old best */
				keep_current_best = (random() <= (MAX_RANDOM_VALUE / 2)) ? 1 : 0;
			}
			if (keep_current_best == 1)
				break;
		}
	}

	return result;
}