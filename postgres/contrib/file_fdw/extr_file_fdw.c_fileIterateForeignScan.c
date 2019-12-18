#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tts_isnull; int /*<<< orphan*/  tts_values; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_15__ {struct TYPE_15__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_14__ {scalar_t__ cstate; } ;
struct TYPE_11__ {TYPE_2__* ss_ScanTupleSlot; } ;
struct TYPE_13__ {TYPE_1__ ss; scalar_t__ fdw_state; } ;
typedef  TYPE_3__ ForeignScanState ;
typedef  TYPE_4__ FileFdwExecutionState ;
typedef  TYPE_5__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CopyFromErrorCallback ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_2__*) ; 
 int NextCopyFrom (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* error_context_stack ; 

__attribute__((used)) static TupleTableSlot *
fileIterateForeignScan(ForeignScanState *node)
{
	FileFdwExecutionState *festate = (FileFdwExecutionState *) node->fdw_state;
	TupleTableSlot *slot = node->ss.ss_ScanTupleSlot;
	bool		found;
	ErrorContextCallback errcallback;

	/* Set up callback to identify error line number. */
	errcallback.callback = CopyFromErrorCallback;
	errcallback.arg = (void *) festate->cstate;
	errcallback.previous = error_context_stack;
	error_context_stack = &errcallback;

	/*
	 * The protocol for loading a virtual tuple into a slot is first
	 * ExecClearTuple, then fill the values/isnull arrays, then
	 * ExecStoreVirtualTuple.  If we don't find another row in the file, we
	 * just skip the last step, leaving the slot empty as required.
	 *
	 * We can pass ExprContext = NULL because we read all columns from the
	 * file, so no need to evaluate default expressions.
	 *
	 * We can also pass tupleOid = NULL because we don't allow oids for
	 * foreign tables.
	 */
	ExecClearTuple(slot);
	found = NextCopyFrom(festate->cstate, NULL,
						 slot->tts_values, slot->tts_isnull);
	if (found)
		ExecStoreVirtualTuple(slot);

	/* Remove error callback. */
	error_context_stack = errcallback.previous;

	return slot;
}