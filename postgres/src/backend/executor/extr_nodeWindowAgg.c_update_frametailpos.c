#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_10__ {TYPE_1__* ps_ExprContext; scalar_t__ plan; } ;
struct TYPE_11__ {int /*<<< orphan*/  ss_ScanTupleSlot; TYPE_2__ ps; } ;
struct TYPE_12__ {int frameOptions; int frametail_valid; int frametailpos; int spooled_rows; int currentpos; scalar_t__ currentgroup; scalar_t__ frametailgroup; int /*<<< orphan*/  temp_slot_2; int /*<<< orphan*/  frametail_slot; int /*<<< orphan*/  buffer; int /*<<< orphan*/  frametail_ptr; int /*<<< orphan*/  endOffsetValue; int /*<<< orphan*/  inRangeColl; int /*<<< orphan*/  endInRangeFunc; scalar_t__ inRangeNullsFirst; TYPE_3__ ss; int /*<<< orphan*/  inRangeAsc; } ;
typedef  TYPE_4__ WindowAggState ;
struct TYPE_13__ {int ordNumCols; int* ordColIdx; } ;
typedef  TYPE_5__ WindowAgg ;
struct TYPE_9__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FRAMEOPTION_END_CURRENT_ROW ; 
 int FRAMEOPTION_END_OFFSET ; 
 int FRAMEOPTION_END_OFFSET_PRECEDING ; 
 int FRAMEOPTION_END_UNBOUNDED_FOLLOWING ; 
 int FRAMEOPTION_GROUPS ; 
 int FRAMEOPTION_RANGE ; 
 int FRAMEOPTION_ROWS ; 
 int /*<<< orphan*/  FunctionCall5Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  are_peers (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  spool_tuples (TYPE_4__*,int) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_frametailpos(WindowAggState *winstate)
{
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	int			frameOptions = winstate->frameOptions;
	MemoryContext oldcontext;

	if (winstate->frametail_valid)
		return;					/* already known for current row */

	/* We may be called in a short-lived context */
	oldcontext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_query_memory);

	if (frameOptions & FRAMEOPTION_END_UNBOUNDED_FOLLOWING)
	{
		/* In UNBOUNDED FOLLOWING mode, all partition rows are in frame */
		spool_tuples(winstate, -1);
		winstate->frametailpos = winstate->spooled_rows;
		winstate->frametail_valid = true;
	}
	else if (frameOptions & FRAMEOPTION_END_CURRENT_ROW)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{
			/* In ROWS mode, exactly the rows up to current are in frame */
			winstate->frametailpos = winstate->currentpos + 1;
			winstate->frametail_valid = true;
		}
		else if (frameOptions & (FRAMEOPTION_RANGE | FRAMEOPTION_GROUPS))
		{
			/* If no ORDER BY, all rows are peers with each other */
			if (node->ordNumCols == 0)
			{
				spool_tuples(winstate, -1);
				winstate->frametailpos = winstate->spooled_rows;
				winstate->frametail_valid = true;
				MemoryContextSwitchTo(oldcontext);
				return;
			}

			/*
			 * In RANGE or GROUPS END_CURRENT_ROW mode, frame end is the last
			 * row that is a peer of current row, frame tail is the row after
			 * that (if any).  We keep a copy of the last-known frame tail row
			 * in frametail_slot, and advance as necessary.  Note that if we
			 * reach end of partition, we will leave frametailpos = end+1 and
			 * frametail_slot empty.
			 */
			tuplestore_select_read_pointer(winstate->buffer,
										   winstate->frametail_ptr);
			if (winstate->frametailpos == 0 &&
				TupIsNull(winstate->frametail_slot))
			{
				/* fetch first row into frametail_slot, if we didn't already */
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->frametail_slot))
					elog(ERROR, "unexpected end of tuplestore");
			}

			while (!TupIsNull(winstate->frametail_slot))
			{
				if (winstate->frametailpos > winstate->currentpos &&
					!are_peers(winstate, winstate->frametail_slot,
							   winstate->ss.ss_ScanTupleSlot))
					break;		/* this row is the frame tail */
				/* Note we advance frametailpos even if the fetch fails */
				winstate->frametailpos++;
				spool_tuples(winstate, winstate->frametailpos);
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->frametail_slot))
					break;		/* end of partition */
			}
			winstate->frametail_valid = true;
		}
		else
			Assert(false);
	}
	else if (frameOptions & FRAMEOPTION_END_OFFSET)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{
			/* In ROWS mode, bound is physically n before/after current */
			int64		offset = DatumGetInt64(winstate->endOffsetValue);

			if (frameOptions & FRAMEOPTION_END_OFFSET_PRECEDING)
				offset = -offset;

			winstate->frametailpos = winstate->currentpos + offset + 1;
			/* smallest allowable value of frametailpos is 0 */
			if (winstate->frametailpos < 0)
				winstate->frametailpos = 0;
			else if (winstate->frametailpos > winstate->currentpos + 1)
			{
				/* make sure frametailpos is not past end of partition */
				spool_tuples(winstate, winstate->frametailpos - 1);
				if (winstate->frametailpos > winstate->spooled_rows)
					winstate->frametailpos = winstate->spooled_rows;
			}
			winstate->frametail_valid = true;
		}
		else if (frameOptions & FRAMEOPTION_RANGE)
		{
			/*
			 * In RANGE END_OFFSET mode, frame end is the last row that
			 * satisfies the in_range constraint relative to the current row,
			 * frame tail is the row after that (if any).  We keep a copy of
			 * the last-known frame tail row in frametail_slot, and advance as
			 * necessary.  Note that if we reach end of partition, we will
			 * leave frametailpos = end+1 and frametail_slot empty.
			 */
			int			sortCol = node->ordColIdx[0];
			bool		sub,
						less;

			/* We must have an ordering column */
			Assert(node->ordNumCols == 1);

			/* Precompute flags for in_range checks */
			if (frameOptions & FRAMEOPTION_END_OFFSET_PRECEDING)
				sub = true;		/* subtract endOffset from current row */
			else
				sub = false;	/* add it */
			less = true;		/* normally, we want frame tail <= sum */
			/* If sort order is descending, flip both flags */
			if (!winstate->inRangeAsc)
			{
				sub = !sub;
				less = false;
			}

			tuplestore_select_read_pointer(winstate->buffer,
										   winstate->frametail_ptr);
			if (winstate->frametailpos == 0 &&
				TupIsNull(winstate->frametail_slot))
			{
				/* fetch first row into frametail_slot, if we didn't already */
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->frametail_slot))
					elog(ERROR, "unexpected end of tuplestore");
			}

			while (!TupIsNull(winstate->frametail_slot))
			{
				Datum		tailval,
							currval;
				bool		tailisnull,
							currisnull;

				tailval = slot_getattr(winstate->frametail_slot, sortCol,
									   &tailisnull);
				currval = slot_getattr(winstate->ss.ss_ScanTupleSlot, sortCol,
									   &currisnull);
				if (tailisnull || currisnull)
				{
					/* order of the rows depends only on nulls_first */
					if (winstate->inRangeNullsFirst)
					{
						/* advance tail if tail is null or curr is not */
						if (!tailisnull)
							break;
					}
					else
					{
						/* advance tail if tail is not null or curr is null */
						if (!currisnull)
							break;
					}
				}
				else
				{
					if (!DatumGetBool(FunctionCall5Coll(&winstate->endInRangeFunc,
														winstate->inRangeColl,
														tailval,
														currval,
														winstate->endOffsetValue,
														BoolGetDatum(sub),
														BoolGetDatum(less))))
						break;	/* this row is the correct frame tail */
				}
				/* Note we advance frametailpos even if the fetch fails */
				winstate->frametailpos++;
				spool_tuples(winstate, winstate->frametailpos);
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->frametail_slot))
					break;		/* end of partition */
			}
			winstate->frametail_valid = true;
		}
		else if (frameOptions & FRAMEOPTION_GROUPS)
		{
			/*
			 * In GROUPS END_OFFSET mode, frame end is the last row of the
			 * last peer group whose number satisfies the offset constraint,
			 * and frame tail is the row after that (if any).  We keep a copy
			 * of the last-known frame tail row in frametail_slot, and advance
			 * as necessary.  Note that if we reach end of partition, we will
			 * leave frametailpos = end+1 and frametail_slot empty.
			 */
			int64		offset = DatumGetInt64(winstate->endOffsetValue);
			int64		maxtailgroup;

			if (frameOptions & FRAMEOPTION_END_OFFSET_PRECEDING)
				maxtailgroup = winstate->currentgroup - offset;
			else
				maxtailgroup = winstate->currentgroup + offset;

			tuplestore_select_read_pointer(winstate->buffer,
										   winstate->frametail_ptr);
			if (winstate->frametailpos == 0 &&
				TupIsNull(winstate->frametail_slot))
			{
				/* fetch first row into frametail_slot, if we didn't already */
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->frametail_slot))
					elog(ERROR, "unexpected end of tuplestore");
			}

			while (!TupIsNull(winstate->frametail_slot))
			{
				if (winstate->frametailgroup > maxtailgroup)
					break;		/* this row is the correct frame tail */
				ExecCopySlot(winstate->temp_slot_2, winstate->frametail_slot);
				/* Note we advance frametailpos even if the fetch fails */
				winstate->frametailpos++;
				spool_tuples(winstate, winstate->frametailpos);
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->frametail_slot))
					break;		/* end of partition */
				if (!are_peers(winstate, winstate->temp_slot_2,
							   winstate->frametail_slot))
					winstate->frametailgroup++;
			}
			ExecClearTuple(winstate->temp_slot_2);
			winstate->frametail_valid = true;
		}
		else
			Assert(false);
	}
	else
		Assert(false);

	MemoryContextSwitchTo(oldcontext);
}