#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  double int64 ;
struct TYPE_4__ {int number_of_rows; int sort_done; int /*<<< orphan*/  sortstate; TYPE_1__* qstate; } ;
struct TYPE_3__ {scalar_t__ sortColType; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__ OSAPerGroupState ;
typedef  int /*<<< orphan*/  (* LerpFunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ AGG_CONTEXT_AGGREGATE ; 
 scalar_t__ AggCheckCallContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PG_ARGISNULL (int) ; 
 double PG_GETARG_FLOAT8 (int) ; 
 scalar_t__ PG_GETARG_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 double ceil (double) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,double) ; 
 double floor (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  tuplesort_getdatum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplesort_performsort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_rescan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_skiptuples (int /*<<< orphan*/ ,double,int) ; 

__attribute__((used)) static Datum
percentile_cont_final_common(FunctionCallInfo fcinfo,
							 Oid expect_type,
							 LerpFunc lerpfunc)
{
	OSAPerGroupState *osastate;
	double		percentile;
	int64		first_row = 0;
	int64		second_row = 0;
	Datum		val;
	Datum		first_val;
	Datum		second_val;
	double		proportion;
	bool		isnull;

	Assert(AggCheckCallContext(fcinfo, NULL) == AGG_CONTEXT_AGGREGATE);

	/* Get and check the percentile argument */
	if (PG_ARGISNULL(1))
		PG_RETURN_NULL();

	percentile = PG_GETARG_FLOAT8(1);

	if (percentile < 0 || percentile > 1 || isnan(percentile))
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("percentile value %g is not between 0 and 1",
						percentile)));

	/* If there were no regular rows, the result is NULL */
	if (PG_ARGISNULL(0))
		PG_RETURN_NULL();

	osastate = (OSAPerGroupState *) PG_GETARG_POINTER(0);

	/* number_of_rows could be zero if we only saw NULL input values */
	if (osastate->number_of_rows == 0)
		PG_RETURN_NULL();

	Assert(expect_type == osastate->qstate->sortColType);

	/* Finish the sort, or rescan if we already did */
	if (!osastate->sort_done)
	{
		tuplesort_performsort(osastate->sortstate);
		osastate->sort_done = true;
	}
	else
		tuplesort_rescan(osastate->sortstate);

	first_row = floor(percentile * (osastate->number_of_rows - 1));
	second_row = ceil(percentile * (osastate->number_of_rows - 1));

	Assert(first_row < osastate->number_of_rows);

	if (!tuplesort_skiptuples(osastate->sortstate, first_row, true))
		elog(ERROR, "missing row in percentile_cont");

	if (!tuplesort_getdatum(osastate->sortstate, true, &first_val, &isnull, NULL))
		elog(ERROR, "missing row in percentile_cont");
	if (isnull)
		PG_RETURN_NULL();

	if (first_row == second_row)
	{
		val = first_val;
	}
	else
	{
		if (!tuplesort_getdatum(osastate->sortstate, true, &second_val, &isnull, NULL))
			elog(ERROR, "missing row in percentile_cont");

		if (isnull)
			PG_RETURN_NULL();

		proportion = (percentile * (osastate->number_of_rows - 1)) - first_row;
		val = lerpfunc(first_val, second_val, proportion);
	}

	PG_RETURN_DATUM(val);
}