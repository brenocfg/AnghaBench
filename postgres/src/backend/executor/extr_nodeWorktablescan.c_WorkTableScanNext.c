#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* state; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ss_ScanTupleSlot; TYPE_2__ ps; } ;
struct TYPE_11__ {TYPE_4__ ss; TYPE_3__* rustate; } ;
typedef  TYPE_5__ WorkTableScanState ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_9__ {int /*<<< orphan*/ * working_table; } ;
struct TYPE_7__ {int /*<<< orphan*/  es_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
WorkTableScanNext(WorkTableScanState *node)
{
	TupleTableSlot *slot;
	Tuplestorestate *tuplestorestate;

	/*
	 * get information from the estate and scan state
	 *
	 * Note: we intentionally do not support backward scan.  Although it would
	 * take only a couple more lines here, it would force nodeRecursiveunion.c
	 * to create the tuplestore with backward scan enabled, which has a
	 * performance cost.  In practice backward scan is never useful for a
	 * worktable plan node, since it cannot appear high enough in the plan
	 * tree of a scrollable cursor to be exposed to a backward-scan
	 * requirement.  So it's not worth expending effort to support it.
	 *
	 * Note: we are also assuming that this node is the only reader of the
	 * worktable.  Therefore, we don't need a private read pointer for the
	 * tuplestore, nor do we need to tell tuplestore_gettupleslot to copy.
	 */
	Assert(ScanDirectionIsForward(node->ss.ps.state->es_direction));

	tuplestorestate = node->rustate->working_table;

	/*
	 * Get the next tuple from tuplestore. Return NULL if no more tuples.
	 */
	slot = node->ss.ss_ScanTupleSlot;
	(void) tuplestore_gettupleslot(tuplestorestate, true, false, slot);
	return slot;
}