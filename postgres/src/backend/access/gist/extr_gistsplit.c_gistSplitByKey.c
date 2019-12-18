#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* nonLeafTupdesc; int /*<<< orphan*/  leafTupdesc; } ;
struct TYPE_19__ {int* spl_right; int spl_nright; int* spl_left; int spl_nleft; } ;
struct TYPE_18__ {int n; int /*<<< orphan*/ * vector; } ;
struct TYPE_17__ {int* spl_risnull; int* spl_lisnull; scalar_t__* spl_dontcare; TYPE_4__ splitVector; } ;
struct TYPE_16__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_2__ GistSplitVector ;
typedef  TYPE_3__ GistEntryVector ;
typedef  TYPE_4__ GIST_SPLITVEC ;
typedef  TYPE_5__ GISTSTATE ;
typedef  int /*<<< orphan*/  GISTENTRY ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int GEVHDRSZ ; 
 int /*<<< orphan*/  gistSplitHalf (TYPE_4__*,int) ; 
 scalar_t__ gistUserPicksplit (int /*<<< orphan*/ ,TYPE_3__*,int,TYPE_2__*,int /*<<< orphan*/ *,int,TYPE_5__*) ; 
 int /*<<< orphan*/  gistdentryinit (TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  gistunionsubkey (TYPE_5__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 TYPE_3__* palloc (int) ; 

void
gistSplitByKey(Relation r, Page page, IndexTuple *itup, int len,
			   GISTSTATE *giststate, GistSplitVector *v, int attno)
{
	GistEntryVector *entryvec;
	OffsetNumber *offNullTuples;
	int			nOffNullTuples = 0;
	int			i;

	/* generate the item array, and identify tuples with null keys */
	/* note that entryvec->vector[0] goes unused in this code */
	entryvec = palloc(GEVHDRSZ + (len + 1) * sizeof(GISTENTRY));
	entryvec->n = len + 1;
	offNullTuples = (OffsetNumber *) palloc(len * sizeof(OffsetNumber));

	for (i = 1; i <= len; i++)
	{
		Datum		datum;
		bool		IsNull;

		datum = index_getattr(itup[i - 1], attno + 1, giststate->leafTupdesc,
							  &IsNull);
		gistdentryinit(giststate, attno, &(entryvec->vector[i]),
					   datum, r, page, i,
					   false, IsNull);
		if (IsNull)
			offNullTuples[nOffNullTuples++] = i;
	}

	if (nOffNullTuples == len)
	{
		/*
		 * Corner case: All keys in attno column are null, so just transfer
		 * our attention to the next column.  If there's no next column, just
		 * split page in half.
		 */
		v->spl_risnull[attno] = v->spl_lisnull[attno] = true;

		if (attno + 1 < giststate->nonLeafTupdesc->natts)
			gistSplitByKey(r, page, itup, len, giststate, v, attno + 1);
		else
			gistSplitHalf(&v->splitVector, len);
	}
	else if (nOffNullTuples > 0)
	{
		int			j = 0;

		/*
		 * We don't want to mix NULL and not-NULL keys on one page, so split
		 * nulls to right page and not-nulls to left.
		 */
		v->splitVector.spl_right = offNullTuples;
		v->splitVector.spl_nright = nOffNullTuples;
		v->spl_risnull[attno] = true;

		v->splitVector.spl_left = (OffsetNumber *) palloc(len * sizeof(OffsetNumber));
		v->splitVector.spl_nleft = 0;
		for (i = 1; i <= len; i++)
			if (j < v->splitVector.spl_nright && offNullTuples[j] == i)
				j++;
			else
				v->splitVector.spl_left[v->splitVector.spl_nleft++] = i;

		/* Compute union keys, unless outer recursion level will handle it */
		if (attno == 0 && giststate->nonLeafTupdesc->natts == 1)
		{
			v->spl_dontcare = NULL;
			gistunionsubkey(giststate, itup, v);
		}
	}
	else
	{
		/*
		 * All keys are not-null, so apply user-defined PickSplit method
		 */
		if (gistUserPicksplit(r, entryvec, attno, v, itup, len, giststate))
		{
			/*
			 * Splitting on attno column is not optimal, so consider
			 * redistributing don't-care tuples according to the next column
			 */
			Assert(attno + 1 < giststate->nonLeafTupdesc->natts);

			if (v->spl_dontcare == NULL)
			{
				/*
				 * This split was actually degenerate, so ignore it altogether
				 * and just split according to the next column.
				 */
				gistSplitByKey(r, page, itup, len, giststate, v, attno + 1);
			}
			else
			{
				/*
				 * Form an array of just the don't-care tuples to pass to a
				 * recursive invocation of this function for the next column.
				 */
				IndexTuple *newitup = (IndexTuple *) palloc(len * sizeof(IndexTuple));
				OffsetNumber *map = (OffsetNumber *) palloc(len * sizeof(OffsetNumber));
				int			newlen = 0;
				GIST_SPLITVEC backupSplit;

				for (i = 0; i < len; i++)
				{
					if (v->spl_dontcare[i + 1])
					{
						newitup[newlen] = itup[i];
						map[newlen] = i + 1;
						newlen++;
					}
				}

				Assert(newlen > 0);

				/*
				 * Make a backup copy of v->splitVector, since the recursive
				 * call will overwrite that with its own result.
				 */
				backupSplit = v->splitVector;
				backupSplit.spl_left = (OffsetNumber *) palloc(sizeof(OffsetNumber) * len);
				memcpy(backupSplit.spl_left, v->splitVector.spl_left, sizeof(OffsetNumber) * v->splitVector.spl_nleft);
				backupSplit.spl_right = (OffsetNumber *) palloc(sizeof(OffsetNumber) * len);
				memcpy(backupSplit.spl_right, v->splitVector.spl_right, sizeof(OffsetNumber) * v->splitVector.spl_nright);

				/* Recursively decide how to split the don't-care tuples */
				gistSplitByKey(r, page, newitup, newlen, giststate, v, attno + 1);

				/* Merge result of subsplit with non-don't-care tuples */
				for (i = 0; i < v->splitVector.spl_nleft; i++)
					backupSplit.spl_left[backupSplit.spl_nleft++] = map[v->splitVector.spl_left[i] - 1];
				for (i = 0; i < v->splitVector.spl_nright; i++)
					backupSplit.spl_right[backupSplit.spl_nright++] = map[v->splitVector.spl_right[i] - 1];

				v->splitVector = backupSplit;
			}
		}
	}

	/*
	 * If we're handling a multicolumn index, at the end of the recursion
	 * recompute the left and right union datums for all index columns.  This
	 * makes sure we hand back correct union datums in all corner cases,
	 * including when we haven't processed all columns to start with, or when
	 * a secondary split moved "don't care" tuples from one side to the other
	 * (we really shouldn't assume that that didn't change the union datums).
	 *
	 * Note: when we're in an internal recursion (attno > 0), we do not worry
	 * about whether the union datums we return with are sensible, since
	 * calling levels won't care.  Also, in a single-column index, we expect
	 * that PickSplit (or the special cases above) produced correct union
	 * datums.
	 */
	if (attno == 0 && giststate->nonLeafTupdesc->natts > 1)
	{
		v->spl_dontcare = NULL;
		gistunionsubkey(giststate, itup, v);
	}
}