#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_9__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_8__ {int* elem_nulls; int num_elems; int next_elem; int /*<<< orphan*/ * elem_values; int /*<<< orphan*/ * array_expr; TYPE_1__* scan_key; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk_flags; int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ IndexArrayKeyInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_3__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecEvalExpr (int /*<<< orphan*/ *,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SK_ISNULL ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*) ; 

bool
ExecIndexEvalArrayKeys(ExprContext *econtext,
					   IndexArrayKeyInfo *arrayKeys, int numArrayKeys)
{
	bool		result = true;
	int			j;
	MemoryContext oldContext;

	/* We want to keep the arrays in per-tuple memory */
	oldContext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

	for (j = 0; j < numArrayKeys; j++)
	{
		ScanKey		scan_key = arrayKeys[j].scan_key;
		ExprState  *array_expr = arrayKeys[j].array_expr;
		Datum		arraydatum;
		bool		isNull;
		ArrayType  *arrayval;
		int16		elmlen;
		bool		elmbyval;
		char		elmalign;
		int			num_elems;
		Datum	   *elem_values;
		bool	   *elem_nulls;

		/*
		 * Compute and deconstruct the array expression. (Notes in
		 * ExecIndexEvalRuntimeKeys() apply here too.)
		 */
		arraydatum = ExecEvalExpr(array_expr,
								  econtext,
								  &isNull);
		if (isNull)
		{
			result = false;
			break;				/* no point in evaluating more */
		}
		arrayval = DatumGetArrayTypeP(arraydatum);
		/* We could cache this data, but not clear it's worth it */
		get_typlenbyvalalign(ARR_ELEMTYPE(arrayval),
							 &elmlen, &elmbyval, &elmalign);
		deconstruct_array(arrayval,
						  ARR_ELEMTYPE(arrayval),
						  elmlen, elmbyval, elmalign,
						  &elem_values, &elem_nulls, &num_elems);
		if (num_elems <= 0)
		{
			result = false;
			break;				/* no point in evaluating more */
		}

		/*
		 * Note: we expect the previous array data, if any, to be
		 * automatically freed by resetting the per-tuple context; hence no
		 * pfree's here.
		 */
		arrayKeys[j].elem_values = elem_values;
		arrayKeys[j].elem_nulls = elem_nulls;
		arrayKeys[j].num_elems = num_elems;
		scan_key->sk_argument = elem_values[0];
		if (elem_nulls[0])
			scan_key->sk_flags |= SK_ISNULL;
		else
			scan_key->sk_flags &= ~SK_ISNULL;
		arrayKeys[j].next_elem = 1;
	}

	MemoryContextSwitchTo(oldContext);

	return result;
}