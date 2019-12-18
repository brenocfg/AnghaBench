#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
struct TYPE_17__ {int scan_key; int num_elems; int /*<<< orphan*/ * elem_values; } ;
struct TYPE_16__ {int numArrayKeys; TYPE_5__* arrayKeys; TYPE_2__* arrayKeyData; int /*<<< orphan*/ * arrayContext; } ;
struct TYPE_15__ {int numberOfKeys; TYPE_2__* keyData; TYPE_1__* indexRelation; int /*<<< orphan*/  opaque; } ;
struct TYPE_14__ {int sk_flags; int sk_strategy; int sk_attno; void* sk_argument; } ;
struct TYPE_13__ {int* rd_indoption; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* ScanKey ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  TYPE_3__* IndexScanDesc ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__* BTScanOpaque ;
typedef  TYPE_5__ BTArrayKeyInfo ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
#define  BTEqualStrategyNumber 132 
#define  BTGreaterEqualStrategyNumber 131 
#define  BTGreaterStrategyNumber 130 
#define  BTLessEqualStrategyNumber 129 
#define  BTLessStrategyNumber 128 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (void*) ; 
 int /*<<< orphan*/  ERROR ; 
 int INDOPTION_DESC ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int SK_ISNULL ; 
 int SK_ROW_HEADER ; 
 int SK_SEARCHARRAY ; 
 int SK_SEARCHNOTNULL ; 
 int SK_SEARCHNULL ; 
 void* _bt_find_extreme_element (TYPE_3__*,TYPE_2__*,int const,int /*<<< orphan*/ *,int) ; 
 int _bt_sort_array_elements (TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int /*<<< orphan*/ ,int*,int*,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

void
_bt_preprocess_array_keys(IndexScanDesc scan)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	int			numberOfKeys = scan->numberOfKeys;
	int16	   *indoption = scan->indexRelation->rd_indoption;
	int			numArrayKeys;
	ScanKey		cur;
	int			i;
	MemoryContext oldContext;

	/* Quick check to see if there are any array keys */
	numArrayKeys = 0;
	for (i = 0; i < numberOfKeys; i++)
	{
		cur = &scan->keyData[i];
		if (cur->sk_flags & SK_SEARCHARRAY)
		{
			numArrayKeys++;
			Assert(!(cur->sk_flags & (SK_ROW_HEADER | SK_SEARCHNULL | SK_SEARCHNOTNULL)));
			/* If any arrays are null as a whole, we can quit right now. */
			if (cur->sk_flags & SK_ISNULL)
			{
				so->numArrayKeys = -1;
				so->arrayKeyData = NULL;
				return;
			}
		}
	}

	/* Quit if nothing to do. */
	if (numArrayKeys == 0)
	{
		so->numArrayKeys = 0;
		so->arrayKeyData = NULL;
		return;
	}

	/*
	 * Make a scan-lifespan context to hold array-associated data, or reset it
	 * if we already have one from a previous rescan cycle.
	 */
	if (so->arrayContext == NULL)
		so->arrayContext = AllocSetContextCreate(CurrentMemoryContext,
												 "BTree array context",
												 ALLOCSET_SMALL_SIZES);
	else
		MemoryContextReset(so->arrayContext);

	oldContext = MemoryContextSwitchTo(so->arrayContext);

	/* Create modifiable copy of scan->keyData in the workspace context */
	so->arrayKeyData = (ScanKey) palloc(scan->numberOfKeys * sizeof(ScanKeyData));
	memcpy(so->arrayKeyData,
		   scan->keyData,
		   scan->numberOfKeys * sizeof(ScanKeyData));

	/* Allocate space for per-array data in the workspace context */
	so->arrayKeys = (BTArrayKeyInfo *) palloc0(numArrayKeys * sizeof(BTArrayKeyInfo));

	/* Now process each array key */
	numArrayKeys = 0;
	for (i = 0; i < numberOfKeys; i++)
	{
		ArrayType  *arrayval;
		int16		elmlen;
		bool		elmbyval;
		char		elmalign;
		int			num_elems;
		Datum	   *elem_values;
		bool	   *elem_nulls;
		int			num_nonnulls;
		int			j;

		cur = &so->arrayKeyData[i];
		if (!(cur->sk_flags & SK_SEARCHARRAY))
			continue;

		/*
		 * First, deconstruct the array into elements.  Anything allocated
		 * here (including a possibly detoasted array value) is in the
		 * workspace context.
		 */
		arrayval = DatumGetArrayTypeP(cur->sk_argument);
		/* We could cache this data, but not clear it's worth it */
		get_typlenbyvalalign(ARR_ELEMTYPE(arrayval),
							 &elmlen, &elmbyval, &elmalign);
		deconstruct_array(arrayval,
						  ARR_ELEMTYPE(arrayval),
						  elmlen, elmbyval, elmalign,
						  &elem_values, &elem_nulls, &num_elems);

		/*
		 * Compress out any null elements.  We can ignore them since we assume
		 * all btree operators are strict.
		 */
		num_nonnulls = 0;
		for (j = 0; j < num_elems; j++)
		{
			if (!elem_nulls[j])
				elem_values[num_nonnulls++] = elem_values[j];
		}

		/* We could pfree(elem_nulls) now, but not worth the cycles */

		/* If there's no non-nulls, the scan qual is unsatisfiable */
		if (num_nonnulls == 0)
		{
			numArrayKeys = -1;
			break;
		}

		/*
		 * If the comparison operator is not equality, then the array qual
		 * degenerates to a simple comparison against the smallest or largest
		 * non-null array element, as appropriate.
		 */
		switch (cur->sk_strategy)
		{
			case BTLessStrategyNumber:
			case BTLessEqualStrategyNumber:
				cur->sk_argument =
					_bt_find_extreme_element(scan, cur,
											 BTGreaterStrategyNumber,
											 elem_values, num_nonnulls);
				continue;
			case BTEqualStrategyNumber:
				/* proceed with rest of loop */
				break;
			case BTGreaterEqualStrategyNumber:
			case BTGreaterStrategyNumber:
				cur->sk_argument =
					_bt_find_extreme_element(scan, cur,
											 BTLessStrategyNumber,
											 elem_values, num_nonnulls);
				continue;
			default:
				elog(ERROR, "unrecognized StrategyNumber: %d",
					 (int) cur->sk_strategy);
				break;
		}

		/*
		 * Sort the non-null elements and eliminate any duplicates.  We must
		 * sort in the same ordering used by the index column, so that the
		 * successive primitive indexscans produce data in index order.
		 */
		num_elems = _bt_sort_array_elements(scan, cur,
											(indoption[cur->sk_attno - 1] & INDOPTION_DESC) != 0,
											elem_values, num_nonnulls);

		/*
		 * And set up the BTArrayKeyInfo data.
		 */
		so->arrayKeys[numArrayKeys].scan_key = i;
		so->arrayKeys[numArrayKeys].num_elems = num_elems;
		so->arrayKeys[numArrayKeys].elem_values = elem_values;
		numArrayKeys++;
	}

	so->numArrayKeys = numArrayKeys;

	MemoryContextSwitchTo(oldContext);
}