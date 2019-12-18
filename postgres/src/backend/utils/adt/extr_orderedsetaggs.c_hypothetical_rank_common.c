#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_10__ {int* tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_11__ {int number_of_rows; int sort_done; int /*<<< orphan*/  sortstate; TYPE_1__* qstate; } ;
struct TYPE_9__ {TYPE_2__* tupslot; int /*<<< orphan*/  tupdesc; } ;
typedef  TYPE_3__ OSAPerGroupState ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ AGG_CONTEXT_AGGREGATE ; 
 scalar_t__ AggCheckCallContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int PG_ARGISNULL (int) ; 
 int /*<<< orphan*/  PG_GETARG_DATUM (int) ; 
 scalar_t__ PG_GETARG_POINTER (int /*<<< orphan*/ ) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hypothetical_check_argtypes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getattr (TYPE_2__*,int,int*) ; 
 scalar_t__ tuplesort_gettupleslot (int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplesort_performsort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_puttupleslot (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int64
hypothetical_rank_common(FunctionCallInfo fcinfo, int flag,
						 int64 *number_of_rows)
{
	int			nargs = PG_NARGS() - 1;
	int64		rank = 1;
	OSAPerGroupState *osastate;
	TupleTableSlot *slot;
	int			i;

	Assert(AggCheckCallContext(fcinfo, NULL) == AGG_CONTEXT_AGGREGATE);

	/* If there were no regular rows, the rank is always 1 */
	if (PG_ARGISNULL(0))
	{
		*number_of_rows = 0;
		return 1;
	}

	osastate = (OSAPerGroupState *) PG_GETARG_POINTER(0);
	*number_of_rows = osastate->number_of_rows;

	/* Adjust nargs to be the number of direct (or aggregated) args */
	if (nargs % 2 != 0)
		elog(ERROR, "wrong number of arguments in hypothetical-set function");
	nargs /= 2;

	hypothetical_check_argtypes(fcinfo, nargs, osastate->qstate->tupdesc);

	/* because we need a hypothetical row, we can't share transition state */
	Assert(!osastate->sort_done);

	/* insert the hypothetical row into the sort */
	slot = osastate->qstate->tupslot;
	ExecClearTuple(slot);
	for (i = 0; i < nargs; i++)
	{
		slot->tts_values[i] = PG_GETARG_DATUM(i + 1);
		slot->tts_isnull[i] = PG_ARGISNULL(i + 1);
	}
	slot->tts_values[i] = Int32GetDatum(flag);
	slot->tts_isnull[i] = false;
	ExecStoreVirtualTuple(slot);

	tuplesort_puttupleslot(osastate->sortstate, slot);

	/* finish the sort */
	tuplesort_performsort(osastate->sortstate);
	osastate->sort_done = true;

	/* iterate till we find the hypothetical row */
	while (tuplesort_gettupleslot(osastate->sortstate, true, true, slot, NULL))
	{
		bool		isnull;
		Datum		d = slot_getattr(slot, nargs + 1, &isnull);

		if (!isnull && DatumGetInt32(d) != 0)
			break;

		rank++;

		CHECK_FOR_INTERRUPTS();
	}

	ExecClearTuple(slot);

	return rank;
}