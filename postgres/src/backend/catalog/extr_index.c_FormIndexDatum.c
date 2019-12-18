#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_5__ {scalar_t__ ii_Expressions; scalar_t__ ii_ExpressionsState; int ii_NumIndexAttrs; int* ii_IndexAttrNumbers; } ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_1__ IndexInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecEvalExprSwitchContext (int /*<<< orphan*/ *,TYPE_2__*,int*) ; 
 scalar_t__ ExecPrepareExprList (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (scalar_t__) ; 
 int /*<<< orphan*/ * lnext (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  slot_getsysattr (int /*<<< orphan*/ *,int,int*) ; 

void
FormIndexDatum(IndexInfo *indexInfo,
			   TupleTableSlot *slot,
			   EState *estate,
			   Datum *values,
			   bool *isnull)
{
	ListCell   *indexpr_item;
	int			i;

	if (indexInfo->ii_Expressions != NIL &&
		indexInfo->ii_ExpressionsState == NIL)
	{
		/* First time through, set up expression evaluation state */
		indexInfo->ii_ExpressionsState =
			ExecPrepareExprList(indexInfo->ii_Expressions, estate);
		/* Check caller has set up context correctly */
		Assert(GetPerTupleExprContext(estate)->ecxt_scantuple == slot);
	}
	indexpr_item = list_head(indexInfo->ii_ExpressionsState);

	for (i = 0; i < indexInfo->ii_NumIndexAttrs; i++)
	{
		int			keycol = indexInfo->ii_IndexAttrNumbers[i];
		Datum		iDatum;
		bool		isNull;

		if (keycol < 0)
			iDatum = slot_getsysattr(slot, keycol, &isNull);
		else if (keycol != 0)
		{
			/*
			 * Plain index column; get the value we need directly from the
			 * heap tuple.
			 */
			iDatum = slot_getattr(slot, keycol, &isNull);
		}
		else
		{
			/*
			 * Index expression --- need to evaluate it.
			 */
			if (indexpr_item == NULL)
				elog(ERROR, "wrong number of index expressions");
			iDatum = ExecEvalExprSwitchContext((ExprState *) lfirst(indexpr_item),
											   GetPerTupleExprContext(estate),
											   &isNull);
			indexpr_item = lnext(indexInfo->ii_ExpressionsState, indexpr_item);
		}
		values[i] = iDatum;
		isnull[i] = isNull;
	}

	if (indexpr_item != NULL)
		elog(ERROR, "wrong number of index expressions");
}