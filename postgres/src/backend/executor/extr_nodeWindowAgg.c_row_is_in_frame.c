#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_10__ {scalar_t__ plan; } ;
struct TYPE_11__ {TYPE_1__ ps; int /*<<< orphan*/  ss_ScanTupleSlot; } ;
struct TYPE_12__ {int frameOptions; scalar_t__ frameheadpos; scalar_t__ currentpos; scalar_t__ frametailpos; scalar_t__ groupheadpos; scalar_t__ grouptailpos; TYPE_2__ ss; int /*<<< orphan*/  endOffsetValue; } ;
typedef  TYPE_3__ WindowAggState ;
struct TYPE_13__ {scalar_t__ ordNumCols; } ;
typedef  TYPE_4__ WindowAgg ;
typedef  int /*<<< orphan*/  TupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int FRAMEOPTION_END_CURRENT_ROW ; 
 int FRAMEOPTION_END_OFFSET ; 
 int FRAMEOPTION_END_OFFSET_PRECEDING ; 
 int FRAMEOPTION_EXCLUDE_CURRENT_ROW ; 
 int FRAMEOPTION_EXCLUDE_GROUP ; 
 int FRAMEOPTION_EXCLUDE_TIES ; 
 int FRAMEOPTION_GROUPS ; 
 int FRAMEOPTION_RANGE ; 
 int FRAMEOPTION_ROWS ; 
 int /*<<< orphan*/  are_peers (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_frameheadpos (TYPE_3__*) ; 
 int /*<<< orphan*/  update_frametailpos (TYPE_3__*) ; 
 int /*<<< orphan*/  update_grouptailpos (TYPE_3__*) ; 

__attribute__((used)) static int
row_is_in_frame(WindowAggState *winstate, int64 pos, TupleTableSlot *slot)
{
	int			frameOptions = winstate->frameOptions;

	Assert(pos >= 0);			/* else caller error */

	/*
	 * First, check frame starting conditions.  We might as well delegate this
	 * to update_frameheadpos always; it doesn't add any notable cost.
	 */
	update_frameheadpos(winstate);
	if (pos < winstate->frameheadpos)
		return 0;

	/*
	 * Okay so far, now check frame ending conditions.  Here, we avoid calling
	 * update_frametailpos in simple cases, so as not to spool tuples further
	 * ahead than necessary.
	 */
	if (frameOptions & FRAMEOPTION_END_CURRENT_ROW)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{
			/* rows after current row are out of frame */
			if (pos > winstate->currentpos)
				return -1;
		}
		else if (frameOptions & (FRAMEOPTION_RANGE | FRAMEOPTION_GROUPS))
		{
			/* following row that is not peer is out of frame */
			if (pos > winstate->currentpos &&
				!are_peers(winstate, slot, winstate->ss.ss_ScanTupleSlot))
				return -1;
		}
		else
			Assert(false);
	}
	else if (frameOptions & FRAMEOPTION_END_OFFSET)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{
			int64		offset = DatumGetInt64(winstate->endOffsetValue);

			/* rows after current row + offset are out of frame */
			if (frameOptions & FRAMEOPTION_END_OFFSET_PRECEDING)
				offset = -offset;

			if (pos > winstate->currentpos + offset)
				return -1;
		}
		else if (frameOptions & (FRAMEOPTION_RANGE | FRAMEOPTION_GROUPS))
		{
			/* hard cases, so delegate to update_frametailpos */
			update_frametailpos(winstate);
			if (pos >= winstate->frametailpos)
				return -1;
		}
		else
			Assert(false);
	}

	/* Check exclusion clause */
	if (frameOptions & FRAMEOPTION_EXCLUDE_CURRENT_ROW)
	{
		if (pos == winstate->currentpos)
			return 0;
	}
	else if ((frameOptions & FRAMEOPTION_EXCLUDE_GROUP) ||
			 ((frameOptions & FRAMEOPTION_EXCLUDE_TIES) &&
			  pos != winstate->currentpos))
	{
		WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;

		/* If no ORDER BY, all rows are peers with each other */
		if (node->ordNumCols == 0)
			return 0;
		/* Otherwise, check the group boundaries */
		if (pos >= winstate->groupheadpos)
		{
			update_grouptailpos(winstate);
			if (pos < winstate->grouptailpos)
				return 0;
		}
	}

	/* If we get here, it's in frame */
	return 1;
}