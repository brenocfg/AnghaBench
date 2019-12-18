#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
typedef  TYPE_3__* WindowStatePerAgg ;
typedef  TYPE_4__* WindowObject ;
struct TYPE_21__ {TYPE_6__* ps_ExprContext; } ;
struct TYPE_23__ {TYPE_1__ ps; } ;
struct TYPE_26__ {int numaggs; scalar_t__ frameheadpos; scalar_t__ aggregatedbase; int frameOptions; scalar_t__ currentpos; scalar_t__ aggregatedupto; scalar_t__ aggcontext; int /*<<< orphan*/ * perfunc; TYPE_3__* peragg; TYPE_20__* tmpcontext; int /*<<< orphan*/ * temp_slot_1; int /*<<< orphan*/ * agg_row_slot; TYPE_4__* agg_winobj; TYPE_2__ ss; } ;
typedef  TYPE_5__ WindowAggState ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_27__ {void** ecxt_aggvalues; int* ecxt_aggnulls; } ;
struct TYPE_25__ {scalar_t__ markptr; } ;
struct TYPE_24__ {int wfuncno; void* resultValue; int resultValueIsNull; int restart; scalar_t__ aggcontext; int /*<<< orphan*/  resulttypeLen; int /*<<< orphan*/  resulttypeByVal; int /*<<< orphan*/  invtransfn_oid; } ;
struct TYPE_22__ {int /*<<< orphan*/ * ecxt_outertuple; } ;
typedef  scalar_t__ MemoryContext ;
typedef  TYPE_6__ ExprContext ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetPointer (void*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int FRAMEOPTION_END_CURRENT_ROW ; 
 int FRAMEOPTION_END_UNBOUNDED_FOLLOWING ; 
 int FRAMEOPTION_EXCLUSION ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (scalar_t__) ; 
 scalar_t__ MemoryContextSwitchTo (scalar_t__) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_20__*) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WinSetMarkPosition (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  advance_windowaggregate (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int advance_windowaggregate_base (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* datumCopy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  finalize_windowaggregate (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,void**,int*) ; 
 int /*<<< orphan*/  initialize_windowaggregate (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int row_is_in_frame (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_frameheadpos (TYPE_5__*) ; 
 int /*<<< orphan*/  window_gettupleslot (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
eval_windowaggregates(WindowAggState *winstate)
{
	WindowStatePerAgg peraggstate;
	int			wfuncno,
				numaggs,
				numaggs_restart,
				i;
	int64		aggregatedupto_nonrestarted;
	MemoryContext oldContext;
	ExprContext *econtext;
	WindowObject agg_winobj;
	TupleTableSlot *agg_row_slot;
	TupleTableSlot *temp_slot;

	numaggs = winstate->numaggs;
	if (numaggs == 0)
		return;					/* nothing to do */

	/* final output execution is in ps_ExprContext */
	econtext = winstate->ss.ps.ps_ExprContext;
	agg_winobj = winstate->agg_winobj;
	agg_row_slot = winstate->agg_row_slot;
	temp_slot = winstate->temp_slot_1;

	/*
	 * If the window's frame start clause is UNBOUNDED_PRECEDING and no
	 * exclusion clause is specified, then the window frame consists of a
	 * contiguous group of rows extending forward from the start of the
	 * partition, and rows only enter the frame, never exit it, as the current
	 * row advances forward.  This makes it possible to use an incremental
	 * strategy for evaluating aggregates: we run the transition function for
	 * each row added to the frame, and run the final function whenever we
	 * need the current aggregate value.  This is considerably more efficient
	 * than the naive approach of re-running the entire aggregate calculation
	 * for each current row.  It does assume that the final function doesn't
	 * damage the running transition value, but we have the same assumption in
	 * nodeAgg.c too (when it rescans an existing hash table).
	 *
	 * If the frame start does sometimes move, we can still optimize as above
	 * whenever successive rows share the same frame head, but if the frame
	 * head moves beyond the previous head we try to remove those rows using
	 * the aggregate's inverse transition function.  This function restores
	 * the aggregate's current state to what it would be if the removed row
	 * had never been aggregated in the first place.  Inverse transition
	 * functions may optionally return NULL, indicating that the function was
	 * unable to remove the tuple from aggregation.  If this happens, or if
	 * the aggregate doesn't have an inverse transition function at all, we
	 * must perform the aggregation all over again for all tuples within the
	 * new frame boundaries.
	 *
	 * If there's any exclusion clause, then we may have to aggregate over a
	 * non-contiguous set of rows, so we punt and recalculate for every row.
	 * (For some frame end choices, it might be that the frame is always
	 * contiguous anyway, but that's an optimization to investigate later.)
	 *
	 * In many common cases, multiple rows share the same frame and hence the
	 * same aggregate value. (In particular, if there's no ORDER BY in a RANGE
	 * window, then all rows are peers and so they all have window frame equal
	 * to the whole partition.)  We optimize such cases by calculating the
	 * aggregate value once when we reach the first row of a peer group, and
	 * then returning the saved value for all subsequent rows.
	 *
	 * 'aggregatedupto' keeps track of the first row that has not yet been
	 * accumulated into the aggregate transition values.  Whenever we start a
	 * new peer group, we accumulate forward to the end of the peer group.
	 */

	/*
	 * First, update the frame head position.
	 *
	 * The frame head should never move backwards, and the code below wouldn't
	 * cope if it did, so for safety we complain if it does.
	 */
	update_frameheadpos(winstate);
	if (winstate->frameheadpos < winstate->aggregatedbase)
		elog(ERROR, "window frame head moved backward");

	/*
	 * If the frame didn't change compared to the previous row, we can re-use
	 * the result values that were previously saved at the bottom of this
	 * function.  Since we don't know the current frame's end yet, this is not
	 * possible to check for fully.  But if the frame end mode is UNBOUNDED
	 * FOLLOWING or CURRENT ROW, no exclusion clause is specified, and the
	 * current row lies within the previous row's frame, then the two frames'
	 * ends must coincide.  Note that on the first row aggregatedbase ==
	 * aggregatedupto, meaning this test must fail, so we don't need to check
	 * the "there was no previous row" case explicitly here.
	 */
	if (winstate->aggregatedbase == winstate->frameheadpos &&
		(winstate->frameOptions & (FRAMEOPTION_END_UNBOUNDED_FOLLOWING |
								   FRAMEOPTION_END_CURRENT_ROW)) &&
		!(winstate->frameOptions & FRAMEOPTION_EXCLUSION) &&
		winstate->aggregatedbase <= winstate->currentpos &&
		winstate->aggregatedupto > winstate->currentpos)
	{
		for (i = 0; i < numaggs; i++)
		{
			peraggstate = &winstate->peragg[i];
			wfuncno = peraggstate->wfuncno;
			econtext->ecxt_aggvalues[wfuncno] = peraggstate->resultValue;
			econtext->ecxt_aggnulls[wfuncno] = peraggstate->resultValueIsNull;
		}
		return;
	}

	/*----------
	 * Initialize restart flags.
	 *
	 * We restart the aggregation:
	 *	 - if we're processing the first row in the partition, or
	 *	 - if the frame's head moved and we cannot use an inverse
	 *	   transition function, or
	 *	 - we have an EXCLUSION clause, or
	 *	 - if the new frame doesn't overlap the old one
	 *
	 * Note that we don't strictly need to restart in the last case, but if
	 * we're going to remove all rows from the aggregation anyway, a restart
	 * surely is faster.
	 *----------
	 */
	numaggs_restart = 0;
	for (i = 0; i < numaggs; i++)
	{
		peraggstate = &winstate->peragg[i];
		if (winstate->currentpos == 0 ||
			(winstate->aggregatedbase != winstate->frameheadpos &&
			 !OidIsValid(peraggstate->invtransfn_oid)) ||
			(winstate->frameOptions & FRAMEOPTION_EXCLUSION) ||
			winstate->aggregatedupto <= winstate->frameheadpos)
		{
			peraggstate->restart = true;
			numaggs_restart++;
		}
		else
			peraggstate->restart = false;
	}

	/*
	 * If we have any possibly-moving aggregates, attempt to advance
	 * aggregatedbase to match the frame's head by removing input rows that
	 * fell off the top of the frame from the aggregations.  This can fail,
	 * i.e. advance_windowaggregate_base() can return false, in which case
	 * we'll restart that aggregate below.
	 */
	while (numaggs_restart < numaggs &&
		   winstate->aggregatedbase < winstate->frameheadpos)
	{
		/*
		 * Fetch the next tuple of those being removed. This should never fail
		 * as we should have been here before.
		 */
		if (!window_gettupleslot(agg_winobj, winstate->aggregatedbase,
								 temp_slot))
			elog(ERROR, "could not re-fetch previously fetched frame row");

		/* Set tuple context for evaluation of aggregate arguments */
		winstate->tmpcontext->ecxt_outertuple = temp_slot;

		/*
		 * Perform the inverse transition for each aggregate function in the
		 * window, unless it has already been marked as needing a restart.
		 */
		for (i = 0; i < numaggs; i++)
		{
			bool		ok;

			peraggstate = &winstate->peragg[i];
			if (peraggstate->restart)
				continue;

			wfuncno = peraggstate->wfuncno;
			ok = advance_windowaggregate_base(winstate,
											  &winstate->perfunc[wfuncno],
											  peraggstate);
			if (!ok)
			{
				/* Inverse transition function has failed, must restart */
				peraggstate->restart = true;
				numaggs_restart++;
			}
		}

		/* Reset per-input-tuple context after each tuple */
		ResetExprContext(winstate->tmpcontext);

		/* And advance the aggregated-row state */
		winstate->aggregatedbase++;
		ExecClearTuple(temp_slot);
	}

	/*
	 * If we successfully advanced the base rows of all the aggregates,
	 * aggregatedbase now equals frameheadpos; but if we failed for any, we
	 * must forcibly update aggregatedbase.
	 */
	winstate->aggregatedbase = winstate->frameheadpos;

	/*
	 * If we created a mark pointer for aggregates, keep it pushed up to frame
	 * head, so that tuplestore can discard unnecessary rows.
	 */
	if (agg_winobj->markptr >= 0)
		WinSetMarkPosition(agg_winobj, winstate->frameheadpos);

	/*
	 * Now restart the aggregates that require it.
	 *
	 * We assume that aggregates using the shared context always restart if
	 * *any* aggregate restarts, and we may thus clean up the shared
	 * aggcontext if that is the case.  Private aggcontexts are reset by
	 * initialize_windowaggregate() if their owning aggregate restarts. If we
	 * aren't restarting an aggregate, we need to free any previously saved
	 * result for it, else we'll leak memory.
	 */
	if (numaggs_restart > 0)
		MemoryContextResetAndDeleteChildren(winstate->aggcontext);
	for (i = 0; i < numaggs; i++)
	{
		peraggstate = &winstate->peragg[i];

		/* Aggregates using the shared ctx must restart if *any* agg does */
		Assert(peraggstate->aggcontext != winstate->aggcontext ||
			   numaggs_restart == 0 ||
			   peraggstate->restart);

		if (peraggstate->restart)
		{
			wfuncno = peraggstate->wfuncno;
			initialize_windowaggregate(winstate,
									   &winstate->perfunc[wfuncno],
									   peraggstate);
		}
		else if (!peraggstate->resultValueIsNull)
		{
			if (!peraggstate->resulttypeByVal)
				pfree(DatumGetPointer(peraggstate->resultValue));
			peraggstate->resultValue = (Datum) 0;
			peraggstate->resultValueIsNull = true;
		}
	}

	/*
	 * Non-restarted aggregates now contain the rows between aggregatedbase
	 * (i.e., frameheadpos) and aggregatedupto, while restarted aggregates
	 * contain no rows.  If there are any restarted aggregates, we must thus
	 * begin aggregating anew at frameheadpos, otherwise we may simply
	 * continue at aggregatedupto.  We must remember the old value of
	 * aggregatedupto to know how long to skip advancing non-restarted
	 * aggregates.  If we modify aggregatedupto, we must also clear
	 * agg_row_slot, per the loop invariant below.
	 */
	aggregatedupto_nonrestarted = winstate->aggregatedupto;
	if (numaggs_restart > 0 &&
		winstate->aggregatedupto != winstate->frameheadpos)
	{
		winstate->aggregatedupto = winstate->frameheadpos;
		ExecClearTuple(agg_row_slot);
	}

	/*
	 * Advance until we reach a row not in frame (or end of partition).
	 *
	 * Note the loop invariant: agg_row_slot is either empty or holds the row
	 * at position aggregatedupto.  We advance aggregatedupto after processing
	 * a row.
	 */
	for (;;)
	{
		int			ret;

		/* Fetch next row if we didn't already */
		if (TupIsNull(agg_row_slot))
		{
			if (!window_gettupleslot(agg_winobj, winstate->aggregatedupto,
									 agg_row_slot))
				break;			/* must be end of partition */
		}

		/*
		 * Exit loop if no more rows can be in frame.  Skip aggregation if
		 * current row is not in frame but there might be more in the frame.
		 */
		ret = row_is_in_frame(winstate, winstate->aggregatedupto, agg_row_slot);
		if (ret < 0)
			break;
		if (ret == 0)
			goto next_tuple;

		/* Set tuple context for evaluation of aggregate arguments */
		winstate->tmpcontext->ecxt_outertuple = agg_row_slot;

		/* Accumulate row into the aggregates */
		for (i = 0; i < numaggs; i++)
		{
			peraggstate = &winstate->peragg[i];

			/* Non-restarted aggs skip until aggregatedupto_nonrestarted */
			if (!peraggstate->restart &&
				winstate->aggregatedupto < aggregatedupto_nonrestarted)
				continue;

			wfuncno = peraggstate->wfuncno;
			advance_windowaggregate(winstate,
									&winstate->perfunc[wfuncno],
									peraggstate);
		}

next_tuple:
		/* Reset per-input-tuple context after each tuple */
		ResetExprContext(winstate->tmpcontext);

		/* And advance the aggregated-row state */
		winstate->aggregatedupto++;
		ExecClearTuple(agg_row_slot);
	}

	/* The frame's end is not supposed to move backwards, ever */
	Assert(aggregatedupto_nonrestarted <= winstate->aggregatedupto);

	/*
	 * finalize aggregates and fill result/isnull fields.
	 */
	for (i = 0; i < numaggs; i++)
	{
		Datum	   *result;
		bool	   *isnull;

		peraggstate = &winstate->peragg[i];
		wfuncno = peraggstate->wfuncno;
		result = &econtext->ecxt_aggvalues[wfuncno];
		isnull = &econtext->ecxt_aggnulls[wfuncno];
		finalize_windowaggregate(winstate,
								 &winstate->perfunc[wfuncno],
								 peraggstate,
								 result, isnull);

		/*
		 * save the result in case next row shares the same frame.
		 *
		 * XXX in some framing modes, eg ROWS/END_CURRENT_ROW, we can know in
		 * advance that the next row can't possibly share the same frame. Is
		 * it worth detecting that and skipping this code?
		 */
		if (!peraggstate->resulttypeByVal && !*isnull)
		{
			oldContext = MemoryContextSwitchTo(peraggstate->aggcontext);
			peraggstate->resultValue =
				datumCopy(*result,
						  peraggstate->resulttypeByVal,
						  peraggstate->resulttypeLen);
			MemoryContextSwitchTo(oldContext);
		}
		else
		{
			peraggstate->resultValue = *result;
		}
		peraggstate->resultValueIsNull = *isnull;
	}
}