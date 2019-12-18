#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  IndexFetchTableData ;

/* Variables and functions */
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * table_index_fetch_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_index_fetch_end (int /*<<< orphan*/ *) ; 
 int table_index_fetch_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * table_slot_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
table_index_fetch_tuple_check(Relation rel,
							  ItemPointer tid,
							  Snapshot snapshot,
							  bool *all_dead)
{
	IndexFetchTableData *scan;
	TupleTableSlot *slot;
	bool		call_again = false;
	bool		found;

	slot = table_slot_create(rel, NULL);
	scan = table_index_fetch_begin(rel);
	found = table_index_fetch_tuple(scan, tid, snapshot, slot, &call_again,
									all_dead);
	table_index_fetch_end(scan);
	ExecDropSingleTupleTableSlot(slot);

	return found;
}