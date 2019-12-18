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
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 int QTW_IGNORE_CTE_SUBQUERIES ; 
 int QTW_IGNORE_RANGE_TABLE ; 
 int /*<<< orphan*/  assign_query_collations_walker ; 
 int /*<<< orphan*/  query_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

void
assign_query_collations(ParseState *pstate, Query *query)
{
	/*
	 * We just use query_tree_walker() to visit all the contained expressions.
	 * We can skip the rangetable and CTE subqueries, though, since RTEs and
	 * subqueries had better have been processed already (else Vars referring
	 * to them would not get created with the right collation).
	 */
	(void) query_tree_walker(query,
							 assign_query_collations_walker,
							 (void *) pstate,
							 QTW_IGNORE_RANGE_TABLE |
							 QTW_IGNORE_CTE_SUBQUERIES);
}