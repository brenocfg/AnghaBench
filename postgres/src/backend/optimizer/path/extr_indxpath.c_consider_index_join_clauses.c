#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * indexclauses; } ;
struct TYPE_11__ {int nkeycolumns; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ IndexOptInfo ;
typedef  TYPE_2__ IndexClauseSet ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  consider_index_join_outer_rels (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
consider_index_join_clauses(PlannerInfo *root, RelOptInfo *rel,
							IndexOptInfo *index,
							IndexClauseSet *rclauseset,
							IndexClauseSet *jclauseset,
							IndexClauseSet *eclauseset,
							List **bitindexpaths)
{
	int			considered_clauses = 0;
	List	   *considered_relids = NIL;
	int			indexcol;

	/*
	 * The strategy here is to identify every potentially useful set of outer
	 * rels that can provide indexable join clauses.  For each such set,
	 * select all the join clauses available from those outer rels, add on all
	 * the indexable restriction clauses, and generate plain and/or bitmap
	 * index paths for that set of clauses.  This is based on the assumption
	 * that it's always better to apply a clause as an indexqual than as a
	 * filter (qpqual); which is where an available clause would end up being
	 * applied if we omit it from the indexquals.
	 *
	 * This looks expensive, but in most practical cases there won't be very
	 * many distinct sets of outer rels to consider.  As a safety valve when
	 * that's not true, we use a heuristic: limit the number of outer rel sets
	 * considered to a multiple of the number of clauses considered.  (We'll
	 * always consider using each individual join clause, though.)
	 *
	 * For simplicity in selecting relevant clauses, we represent each set of
	 * outer rels as a maximum set of clause_relids --- that is, the indexed
	 * relation itself is also included in the relids set.  considered_relids
	 * lists all relids sets we've already tried.
	 */
	for (indexcol = 0; indexcol < index->nkeycolumns; indexcol++)
	{
		/* Consider each applicable simple join clause */
		considered_clauses += list_length(jclauseset->indexclauses[indexcol]);
		consider_index_join_outer_rels(root, rel, index,
									   rclauseset, jclauseset, eclauseset,
									   bitindexpaths,
									   jclauseset->indexclauses[indexcol],
									   considered_clauses,
									   &considered_relids);
		/* Consider each applicable eclass join clause */
		considered_clauses += list_length(eclauseset->indexclauses[indexcol]);
		consider_index_join_outer_rels(root, rel, index,
									   rclauseset, jclauseset, eclauseset,
									   bitindexpaths,
									   eclauseset->indexclauses[indexcol],
									   considered_clauses,
									   &considered_relids);
	}
}