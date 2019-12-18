#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_11__ {int nKeys; int /*<<< orphan*/  estate; TYPE_8__* indexInfo; int /*<<< orphan*/  tupDesc; TYPE_3__* sortKeys; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_15__ {scalar_t__* ii_IndexAttrNumbers; int /*<<< orphan*/ * ii_Expressions; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_13__ {scalar_t__ abbrev_converter; } ;
struct TYPE_12__ {int isnull1; int /*<<< orphan*/  datum1; scalar_t__ tuple; } ;
typedef  TYPE_2__ SortTuple ;
typedef  TYPE_3__* SortSupport ;
typedef  scalar_t__ HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 scalar_t__ ApplySortAbbrevFullComparator (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ ApplySortComparator (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ExecStoreHeapTuple (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FormIndexDatum (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 TYPE_7__* GetPerTupleExprContext (int /*<<< orphan*/ ) ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  ResetPerTupleExprContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
comparetup_cluster(const SortTuple *a, const SortTuple *b,
				   Tuplesortstate *state)
{
	SortSupport sortKey = state->sortKeys;
	HeapTuple	ltup;
	HeapTuple	rtup;
	TupleDesc	tupDesc;
	int			nkey;
	int32		compare;
	Datum		datum1,
				datum2;
	bool		isnull1,
				isnull2;
	AttrNumber	leading = state->indexInfo->ii_IndexAttrNumbers[0];

	/* Be prepared to compare additional sort keys */
	ltup = (HeapTuple) a->tuple;
	rtup = (HeapTuple) b->tuple;
	tupDesc = state->tupDesc;

	/* Compare the leading sort key, if it's simple */
	if (leading != 0)
	{
		compare = ApplySortComparator(a->datum1, a->isnull1,
									  b->datum1, b->isnull1,
									  sortKey);
		if (compare != 0)
			return compare;

		if (sortKey->abbrev_converter)
		{
			datum1 = heap_getattr(ltup, leading, tupDesc, &isnull1);
			datum2 = heap_getattr(rtup, leading, tupDesc, &isnull2);

			compare = ApplySortAbbrevFullComparator(datum1, isnull1,
													datum2, isnull2,
													sortKey);
		}
		if (compare != 0 || state->nKeys == 1)
			return compare;
		/* Compare additional columns the hard way */
		sortKey++;
		nkey = 1;
	}
	else
	{
		/* Must compare all keys the hard way */
		nkey = 0;
	}

	if (state->indexInfo->ii_Expressions == NULL)
	{
		/* If not expression index, just compare the proper heap attrs */

		for (; nkey < state->nKeys; nkey++, sortKey++)
		{
			AttrNumber	attno = state->indexInfo->ii_IndexAttrNumbers[nkey];

			datum1 = heap_getattr(ltup, attno, tupDesc, &isnull1);
			datum2 = heap_getattr(rtup, attno, tupDesc, &isnull2);

			compare = ApplySortComparator(datum1, isnull1,
										  datum2, isnull2,
										  sortKey);
			if (compare != 0)
				return compare;
		}
	}
	else
	{
		/*
		 * In the expression index case, compute the whole index tuple and
		 * then compare values.  It would perhaps be faster to compute only as
		 * many columns as we need to compare, but that would require
		 * duplicating all the logic in FormIndexDatum.
		 */
		Datum		l_index_values[INDEX_MAX_KEYS];
		bool		l_index_isnull[INDEX_MAX_KEYS];
		Datum		r_index_values[INDEX_MAX_KEYS];
		bool		r_index_isnull[INDEX_MAX_KEYS];
		TupleTableSlot *ecxt_scantuple;

		/* Reset context each time to prevent memory leakage */
		ResetPerTupleExprContext(state->estate);

		ecxt_scantuple = GetPerTupleExprContext(state->estate)->ecxt_scantuple;

		ExecStoreHeapTuple(ltup, ecxt_scantuple, false);
		FormIndexDatum(state->indexInfo, ecxt_scantuple, state->estate,
					   l_index_values, l_index_isnull);

		ExecStoreHeapTuple(rtup, ecxt_scantuple, false);
		FormIndexDatum(state->indexInfo, ecxt_scantuple, state->estate,
					   r_index_values, r_index_isnull);

		for (; nkey < state->nKeys; nkey++, sortKey++)
		{
			compare = ApplySortComparator(l_index_values[nkey],
										  l_index_isnull[nkey],
										  r_index_values[nkey],
										  r_index_isnull[nkey],
										  sortKey);
			if (compare != 0)
				return compare;
		}
	}

	return 0;
}