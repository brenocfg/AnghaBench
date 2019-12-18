#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int es_range_table_size; int /*<<< orphan*/ * es_rowmarks; int /*<<< orphan*/ * es_relations; int /*<<< orphan*/ * es_range_table; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

void
ExecInitRangeTable(EState *estate, List *rangeTable)
{
	/* Remember the range table List as-is */
	estate->es_range_table = rangeTable;

	/* Set size of associated arrays */
	estate->es_range_table_size = list_length(rangeTable);

	/*
	 * Allocate an array to store an open Relation corresponding to each
	 * rangetable entry, and initialize entries to NULL.  Relations are opened
	 * and stored here as needed.
	 */
	estate->es_relations = (Relation *)
		palloc0(estate->es_range_table_size * sizeof(Relation));

	/*
	 * es_rowmarks is also parallel to the es_range_table, but it's allocated
	 * only if needed.
	 */
	estate->es_rowmarks = NULL;
}