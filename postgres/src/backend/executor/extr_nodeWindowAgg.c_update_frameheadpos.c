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
struct TYPE_12__ {int frameOptions; int framehead_valid; scalar_t__ frameheadpos; scalar_t__ currentpos; scalar_t__ spooled_rows; scalar_t__ currentgroup; scalar_t__ frameheadgroup; int /*<<< orphan*/  temp_slot_2; int /*<<< orphan*/  framehead_slot; int /*<<< orphan*/  buffer; int /*<<< orphan*/  framehead_ptr; int /*<<< orphan*/  startOffsetValue; int /*<<< orphan*/  inRangeColl; int /*<<< orphan*/  startInRangeFunc; scalar_t__ inRangeNullsFirst; TYPE_3__ ss; int /*<<< orphan*/  inRangeAsc; } ;
typedef  TYPE_4__ WindowAggState ;
struct TYPE_13__ {int ordNumCols; int* ordColIdx; } ;
typedef  TYPE_5__ WindowAgg ;
struct TYPE_9__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FRAMEOPTION_GROUPS ; 
 int FRAMEOPTION_RANGE ; 
 int FRAMEOPTION_ROWS ; 
 int FRAMEOPTION_START_CURRENT_ROW ; 
 int FRAMEOPTION_START_OFFSET ; 
 int FRAMEOPTION_START_OFFSET_PRECEDING ; 
 int FRAMEOPTION_START_UNBOUNDED_PRECEDING ; 
 int /*<<< orphan*/  FunctionCall5Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ ) ; 
 scalar_t__ are_peers (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  spool_tuples (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_frameheadpos(WindowAggState *winstate)
{
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	int			frameOptions = winstate->frameOptions;
	MemoryContext oldcontext;

	if (winstate->framehead_valid)
		return;					/* already known for current row */

	/* We may be called in a short-lived context */
	oldcontext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_query_memory);

	if (frameOptions & FRAMEOPTION_START_UNBOUNDED_PRECEDING)
	{
		/* In UNBOUNDED PRECEDING mode, frame head is always row 0 */
		winstate->frameheadpos = 0;
		winstate->framehead_valid = true;
	}
	else if (frameOptions & FRAMEOPTION_START_CURRENT_ROW)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{
			/* In ROWS mode, frame head is the same as current */
			winstate->frameheadpos = winstate->currentpos;
			winstate->framehead_valid = true;
		}
		else if (frameOptions & (FRAMEOPTION_RANGE | FRAMEOPTION_GROUPS))
		{
			/* If no ORDER BY, all rows are peers with each other */
			if (node->ordNumCols == 0)
			{
				winstate->frameheadpos = 0;
				winstate->framehead_valid = true;
				MemoryContextSwitchTo(oldcontext);
				return;
			}

			/*
			 * In RANGE or GROUPS START_CURRENT_ROW mode, frame head is the
			 * first row that is a peer of current row.  We keep a copy of the
			 * last-known frame head row in framehead_slot, and advance as
			 * necessary.  Note that if we reach end of partition, we will
			 * leave frameheadpos = end+1 and framehead_slot empty.
			 */
			tuplestore_select_read_pointer(winstate->buffer,
										   winstate->framehead_ptr);
			if (winstate->frameheadpos == 0 &&
				TupIsNull(winstate->framehead_slot))
			{
				/* fetch first row into framehead_slot, if we didn't already */
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->framehead_slot))
					elog(ERROR, "unexpected end of tuplestore");
			}

			while (!TupIsNull(winstate->framehead_slot))
			{
				if (are_peers(winstate, winstate->framehead_slot,
							  winstate->ss.ss_ScanTupleSlot))
					break;		/* this row is the correct frame head */
				/* Note we advance frameheadpos even if the fetch fails */
				winstate->frameheadpos++;
				spool_tuples(winstate, winstate->frameheadpos);
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->framehead_slot))
					break;		/* end of partition */
			}
			winstate->framehead_valid = true;
		}
		else
			Assert(false);
	}
	else if (frameOptions & FRAMEOPTION_START_OFFSET)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{
			/* In ROWS mode, bound is physically n before/after current */
			int64		offset = DatumGetInt64(winstate->startOffsetValue);

			if (frameOptions & FRAMEOPTION_START_OFFSET_PRECEDING)
				offset = -offset;

			winstate->frameheadpos = winstate->currentpos + offset;
			/* frame head can't go before first row */
			if (winstate->frameheadpos < 0)
				winstate->frameheadpos = 0;
			else if (winstate->frameheadpos > winstate->currentpos + 1)
			{
				/* make sure frameheadpos is not past end of partition */
				spool_tuples(winstate, winstate->frameheadpos - 1);
				if (winstate->frameheadpos > winstate->spooled_rows)
					winstate->frameheadpos = winstate->spooled_rows;
			}
			winstate->framehead_valid = true;
		}
		else if (frameOptions & FRAMEOPTION_RANGE)
		{
			/*
			 * In RANGE START_OFFSET mode, frame head is the first row that
			 * satisfies the in_range constraint relative to the current row.
			 * We keep a copy of the last-known frame head row in
			 * framehead_slot, and advance as necessary.  Note that if we
			 * reach end of partition, we will leave frameheadpos = end+1 and
			 * framehead_slot empty.
			 */
			int			sortCol = node->ordColIdx[0];
			bool		sub,
						less;

			/* We must have an ordering column */
			Assert(node->ordNumCols == 1);

			/* Precompute flags for in_range checks */
			if (frameOptions & FRAMEOPTION_START_OFFSET_PRECEDING)
				sub = true;		/* subtract startOffset from current row */
			else
				sub = false;	/* add it */
			less = false;		/* normally, we want frame head >= sum */
			/* If sort order is descending, flip both flags */
			if (!winstate->inRangeAsc)
			{
				sub = !sub;
				less = true;
			}

			tuplestore_select_read_pointer(winstate->buffer,
										   winstate->framehead_ptr);
			if (winstate->frameheadpos == 0 &&
				TupIsNull(winstate->framehead_slot))
			{
				/* fetch first row into framehead_slot, if we didn't already */
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->framehead_slot))
					elog(ERROR, "unexpected end of tuplestore");
			}

			while (!TupIsNull(winstate->framehead_slot))
			{
				Datum		headval,
							currval;
				bool		headisnull,
							currisnull;

				headval = slot_getattr(winstate->framehead_slot, sortCol,
									   &headisnull);
				currval = slot_getattr(winstate->ss.ss_ScanTupleSlot, sortCol,
									   &currisnull);
				if (headisnull || currisnull)
				{
					/* order of the rows depends only on nulls_first */
					if (winstate->inRangeNullsFirst)
					{
						/* advance head if head is null and curr is not */
						if (!headisnull || currisnull)
							break;
					}
					else
					{
						/* advance head if head is not null and curr is null */
						if (headisnull || !currisnull)
							break;
					}
				}
				else
				{
					if (DatumGetBool(FunctionCall5Coll(&winstate->startInRangeFunc,
													   winstate->inRangeColl,
													   headval,
													   currval,
													   winstate->startOffsetValue,
													   BoolGetDatum(sub),
													   BoolGetDatum(less))))
						break;	/* this row is the correct frame head */
				}
				/* Note we advance frameheadpos even if the fetch fails */
				winstate->frameheadpos++;
				spool_tuples(winstate, winstate->frameheadpos);
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->framehead_slot))
					break;		/* end of partition */
			}
			winstate->framehead_valid = true;
		}
		else if (frameOptions & FRAMEOPTION_GROUPS)
		{
			/*
			 * In GROUPS START_OFFSET mode, frame head is the first row of the
			 * first peer group whose number satisfies the offset constraint.
			 * We keep a copy of the last-known frame head row in
			 * framehead_slot, and advance as necessary.  Note that if we
			 * reach end of partition, we will leave frameheadpos = end+1 and
			 * framehead_slot empty.
			 */
			int64		offset = DatumGetInt64(winstate->startOffsetValue);
			int64		minheadgroup;

			if (frameOptions & FRAMEOPTION_START_OFFSET_PRECEDING)
				minheadgroup = winstate->currentgroup - offset;
			else
				minheadgroup = winstate->currentgroup + offset;

			tuplestore_select_read_pointer(winstate->buffer,
										   winstate->framehead_ptr);
			if (winstate->frameheadpos == 0 &&
				TupIsNull(winstate->framehead_slot))
			{
				/* fetch first row into framehead_slot, if we didn't already */
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->framehead_slot))
					elog(ERROR, "unexpected end of tuplestore");
			}

			while (!TupIsNull(winstate->framehead_slot))
			{
				if (winstate->frameheadgroup >= minheadgroup)
					break;		/* this row is the correct frame head */
				ExecCopySlot(winstate->temp_slot_2, winstate->framehead_slot);
				/* Note we advance frameheadpos even if the fetch fails */
				winstate->frameheadpos++;
				spool_tuples(winstate, winstate->frameheadpos);
				if (!tuplestore_gettupleslot(winstate->buffer, true, true,
											 winstate->framehead_slot))
					break;		/* end of partition */
				if (!are_peers(winstate, winstate->temp_slot_2,
							   winstate->framehead_slot))
					winstate->frameheadgroup++;
			}
			ExecClearTuple(winstate->temp_slot_2);
			winstate->framehead_valid = true;
		}
		else
			Assert(false);
	}
	else
		Assert(false);

	MemoryContextSwitchTo(oldcontext);
}