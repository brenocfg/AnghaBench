#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  self_reference; int /*<<< orphan*/ * tablesample; int /*<<< orphan*/  relkind; scalar_t__ inh; } ;
struct TYPE_30__ {scalar_t__ reloptkind; int rtekind; scalar_t__ rows; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IS_DUMMY_REL (TYPE_1__*) ; 
 int /*<<< orphan*/  RELKIND_FOREIGN_TABLE ; 
 int /*<<< orphan*/  RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELOPT_BASEREL ; 
#define  RTE_CTE 135 
#define  RTE_FUNCTION 134 
#define  RTE_NAMEDTUPLESTORE 133 
#define  RTE_RELATION 132 
#define  RTE_RESULT 131 
#define  RTE_SUBQUERY 130 
#define  RTE_TABLEFUNC 129 
#define  RTE_VALUES 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ relation_excluded_by_constraints (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_append_rel_size (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_cte_pathlist (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_dummy_rel_pathlist (TYPE_1__*) ; 
 int /*<<< orphan*/  set_foreign_size (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_function_size_estimates (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_namedtuplestore_pathlist (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_plain_rel_size (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_result_pathlist (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_subquery_pathlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_tablefunc_size_estimates (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_tablesample_rel_size (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_values_size_estimates (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  set_worktable_pathlist (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void
set_rel_size(PlannerInfo *root, RelOptInfo *rel,
			 Index rti, RangeTblEntry *rte)
{
	if (rel->reloptkind == RELOPT_BASEREL &&
		relation_excluded_by_constraints(root, rel, rte))
	{
		/*
		 * We proved we don't need to scan the rel via constraint exclusion,
		 * so set up a single dummy path for it.  Here we only check this for
		 * regular baserels; if it's an otherrel, CE was already checked in
		 * set_append_rel_size().
		 *
		 * In this case, we go ahead and set up the relation's path right away
		 * instead of leaving it for set_rel_pathlist to do.  This is because
		 * we don't have a convention for marking a rel as dummy except by
		 * assigning a dummy path to it.
		 */
		set_dummy_rel_pathlist(rel);
	}
	else if (rte->inh)
	{
		/* It's an "append relation", process accordingly */
		set_append_rel_size(root, rel, rti, rte);
	}
	else
	{
		switch (rel->rtekind)
		{
			case RTE_RELATION:
				if (rte->relkind == RELKIND_FOREIGN_TABLE)
				{
					/* Foreign table */
					set_foreign_size(root, rel, rte);
				}
				else if (rte->relkind == RELKIND_PARTITIONED_TABLE)
				{
					/*
					 * We could get here if asked to scan a partitioned table
					 * with ONLY.  In that case we shouldn't scan any of the
					 * partitions, so mark it as a dummy rel.
					 */
					set_dummy_rel_pathlist(rel);
				}
				else if (rte->tablesample != NULL)
				{
					/* Sampled relation */
					set_tablesample_rel_size(root, rel, rte);
				}
				else
				{
					/* Plain relation */
					set_plain_rel_size(root, rel, rte);
				}
				break;
			case RTE_SUBQUERY:

				/*
				 * Subqueries don't support making a choice between
				 * parameterized and unparameterized paths, so just go ahead
				 * and build their paths immediately.
				 */
				set_subquery_pathlist(root, rel, rti, rte);
				break;
			case RTE_FUNCTION:
				set_function_size_estimates(root, rel);
				break;
			case RTE_TABLEFUNC:
				set_tablefunc_size_estimates(root, rel);
				break;
			case RTE_VALUES:
				set_values_size_estimates(root, rel);
				break;
			case RTE_CTE:

				/*
				 * CTEs don't support making a choice between parameterized
				 * and unparameterized paths, so just go ahead and build their
				 * paths immediately.
				 */
				if (rte->self_reference)
					set_worktable_pathlist(root, rel, rte);
				else
					set_cte_pathlist(root, rel, rte);
				break;
			case RTE_NAMEDTUPLESTORE:
				/* Might as well just build the path immediately */
				set_namedtuplestore_pathlist(root, rel, rte);
				break;
			case RTE_RESULT:
				/* Might as well just build the path immediately */
				set_result_pathlist(root, rel, rte);
				break;
			default:
				elog(ERROR, "unexpected rtekind: %d", (int) rel->rtekind);
				break;
		}
	}

	/*
	 * We insist that all non-dummy rels have a nonzero rowcount estimate.
	 */
	Assert(rel->rows > 0 || IS_DUMMY_REL(rel));
}