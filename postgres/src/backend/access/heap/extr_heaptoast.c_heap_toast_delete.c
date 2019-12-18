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
typedef  TYPE_2__* TupleDesc ;
struct TYPE_9__ {TYPE_2__* rd_att; TYPE_1__* rd_rel; } ;
struct TYPE_8__ {int natts; } ;
struct TYPE_7__ {scalar_t__ relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int MaxHeapAttributeNumber ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  toast_delete_external (TYPE_3__*,int /*<<< orphan*/ *,int*,int) ; 

void
heap_toast_delete(Relation rel, HeapTuple oldtup, bool is_speculative)
{
	TupleDesc	tupleDesc;
	Datum		toast_values[MaxHeapAttributeNumber];
	bool		toast_isnull[MaxHeapAttributeNumber];

	/*
	 * We should only ever be called for tuples of plain relations or
	 * materialized views --- recursing on a toast rel is bad news.
	 */
	Assert(rel->rd_rel->relkind == RELKIND_RELATION ||
		   rel->rd_rel->relkind == RELKIND_MATVIEW);

	/*
	 * Get the tuple descriptor and break down the tuple into fields.
	 *
	 * NOTE: it's debatable whether to use heap_deform_tuple() here or just
	 * heap_getattr() only the varlena columns.  The latter could win if there
	 * are few varlena columns and many non-varlena ones. However,
	 * heap_deform_tuple costs only O(N) while the heap_getattr way would cost
	 * O(N^2) if there are many varlena columns, so it seems better to err on
	 * the side of linear cost.  (We won't even be here unless there's at
	 * least one varlena column, by the way.)
	 */
	tupleDesc = rel->rd_att;

	Assert(tupleDesc->natts <= MaxHeapAttributeNumber);
	heap_deform_tuple(oldtup, tupleDesc, toast_values, toast_isnull);

	/* Do the real work. */
	toast_delete_external(rel, toast_values, toast_isnull, is_speculative);
}