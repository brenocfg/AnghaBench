#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
struct TYPE_42__ {int /*<<< orphan*/  all_baserels; } ;
struct TYPE_41__ {int /*<<< orphan*/ * tablesample; int /*<<< orphan*/  relkind; scalar_t__ inh; } ;
struct TYPE_40__ {int rtekind; scalar_t__ reloptkind; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 scalar_t__ BMS_SINGLETON ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IS_DUMMY_REL (TYPE_1__*) ; 
 int /*<<< orphan*/  RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELOPT_BASEREL ; 
#define  RTE_CTE 135 
#define  RTE_FUNCTION 134 
#define  RTE_NAMEDTUPLESTORE 133 
#define  RTE_RELATION 132 
#define  RTE_RESULT 131 
#define  RTE_SUBQUERY 130 
#define  RTE_TABLEFUNC 129 
#define  RTE_VALUES 128 
 scalar_t__ bms_membership (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_print_rel (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  generate_gather_paths (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_append_rel_pathlist (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_cheapest (TYPE_1__*) ; 
 int /*<<< orphan*/  set_foreign_pathlist (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_function_pathlist (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_plain_rel_pathlist (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_rel_pathlist_hook (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_tablefunc_pathlist (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_tablesample_rel_pathlist (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_values_pathlist (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
set_rel_pathlist(PlannerInfo *root, RelOptInfo *rel,
				 Index rti, RangeTblEntry *rte)
{
	if (IS_DUMMY_REL(rel))
	{
		/* We already proved the relation empty, so nothing more to do */
	}
	else if (rte->inh)
	{
		/* It's an "append relation", process accordingly */
		set_append_rel_pathlist(root, rel, rti, rte);
	}
	else
	{
		switch (rel->rtekind)
		{
			case RTE_RELATION:
				if (rte->relkind == RELKIND_FOREIGN_TABLE)
				{
					/* Foreign table */
					set_foreign_pathlist(root, rel, rte);
				}
				else if (rte->tablesample != NULL)
				{
					/* Sampled relation */
					set_tablesample_rel_pathlist(root, rel, rte);
				}
				else
				{
					/* Plain relation */
					set_plain_rel_pathlist(root, rel, rte);
				}
				break;
			case RTE_SUBQUERY:
				/* Subquery --- fully handled during set_rel_size */
				break;
			case RTE_FUNCTION:
				/* RangeFunction */
				set_function_pathlist(root, rel, rte);
				break;
			case RTE_TABLEFUNC:
				/* Table Function */
				set_tablefunc_pathlist(root, rel, rte);
				break;
			case RTE_VALUES:
				/* Values list */
				set_values_pathlist(root, rel, rte);
				break;
			case RTE_CTE:
				/* CTE reference --- fully handled during set_rel_size */
				break;
			case RTE_NAMEDTUPLESTORE:
				/* tuplestore reference --- fully handled during set_rel_size */
				break;
			case RTE_RESULT:
				/* simple Result --- fully handled during set_rel_size */
				break;
			default:
				elog(ERROR, "unexpected rtekind: %d", (int) rel->rtekind);
				break;
		}
	}

	/*
	 * Allow a plugin to editorialize on the set of Paths for this base
	 * relation.  It could add new paths (such as CustomPaths) by calling
	 * add_path(), or add_partial_path() if parallel aware.  It could also
	 * delete or modify paths added by the core code.
	 */
	if (set_rel_pathlist_hook)
		(*set_rel_pathlist_hook) (root, rel, rti, rte);

	/*
	 * If this is a baserel, we should normally consider gathering any partial
	 * paths we may have created for it.  We have to do this after calling the
	 * set_rel_pathlist_hook, else it cannot add partial paths to be included
	 * here.
	 *
	 * However, if this is an inheritance child, skip it.  Otherwise, we could
	 * end up with a very large number of gather nodes, each trying to grab
	 * its own pool of workers.  Instead, we'll consider gathering partial
	 * paths for the parent appendrel.
	 *
	 * Also, if this is the topmost scan/join rel (that is, the only baserel),
	 * we postpone gathering until the final scan/join targetlist is available
	 * (see grouping_planner).
	 */
	if (rel->reloptkind == RELOPT_BASEREL &&
		bms_membership(root->all_baserels) != BMS_SINGLETON)
		generate_gather_paths(root, rel, false);

	/* Now find the cheapest of the paths for this rel */
	set_cheapest(rel);

#ifdef OPTIMIZER_DEBUG
	debug_print_rel(root, rel);
#endif
}