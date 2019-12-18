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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_7__ {int /*<<< orphan*/ * ss_ScanTupleSlot; } ;
struct TYPE_9__ {TYPE_1__ ss; scalar_t__ fdw_state; } ;
struct TYPE_8__ {scalar_t__ next_tuple; scalar_t__ num_tuples; int /*<<< orphan*/ * tuples; int /*<<< orphan*/  eof_reached; int /*<<< orphan*/  cursor_exists; } ;
typedef  TYPE_2__ PgFdwScanState ;
typedef  TYPE_3__ ForeignScanState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecStoreHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  create_cursor (TYPE_3__*) ; 
 int /*<<< orphan*/  fetch_more_data (TYPE_3__*) ; 

__attribute__((used)) static TupleTableSlot *
postgresIterateForeignScan(ForeignScanState *node)
{
	PgFdwScanState *fsstate = (PgFdwScanState *) node->fdw_state;
	TupleTableSlot *slot = node->ss.ss_ScanTupleSlot;

	/*
	 * If this is the first call after Begin or ReScan, we need to create the
	 * cursor on the remote side.
	 */
	if (!fsstate->cursor_exists)
		create_cursor(node);

	/*
	 * Get some more tuples, if we've run out.
	 */
	if (fsstate->next_tuple >= fsstate->num_tuples)
	{
		/* No point in another fetch if we already detected EOF, though. */
		if (!fsstate->eof_reached)
			fetch_more_data(node);
		/* If we didn't get any tuples, must be end of data. */
		if (fsstate->next_tuple >= fsstate->num_tuples)
			return ExecClearTuple(slot);
	}

	/*
	 * Return the next tuple.
	 */
	ExecStoreHeapTuple(fsstate->tuples[fsstate->next_tuple++],
					   slot,
					   false);

	return slot;
}