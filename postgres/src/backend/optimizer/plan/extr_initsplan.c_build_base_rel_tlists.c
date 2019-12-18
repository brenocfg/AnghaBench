#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* parse; } ;
struct TYPE_5__ {int /*<<< orphan*/ * havingQual; } ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int PVC_INCLUDE_PLACEHOLDERS ; 
 int PVC_RECURSE_AGGREGATES ; 
 int PVC_RECURSE_WINDOWFUNCS ; 
 int /*<<< orphan*/  add_vars_to_targetlist (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bms_make_singleton (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pull_var_clause (int /*<<< orphan*/ *,int) ; 

void
build_base_rel_tlists(PlannerInfo *root, List *final_tlist)
{
	List	   *tlist_vars = pull_var_clause((Node *) final_tlist,
											 PVC_RECURSE_AGGREGATES |
											 PVC_RECURSE_WINDOWFUNCS |
											 PVC_INCLUDE_PLACEHOLDERS);

	if (tlist_vars != NIL)
	{
		add_vars_to_targetlist(root, tlist_vars, bms_make_singleton(0), true);
		list_free(tlist_vars);
	}

	/*
	 * If there's a HAVING clause, we'll need the Vars it uses, too.  Note
	 * that HAVING can contain Aggrefs but not WindowFuncs.
	 */
	if (root->parse->havingQual)
	{
		List	   *having_vars = pull_var_clause(root->parse->havingQual,
												  PVC_RECURSE_AGGREGATES |
												  PVC_INCLUDE_PLACEHOLDERS);

		if (having_vars != NIL)
		{
			add_vars_to_targetlist(root, having_vars,
								   bms_make_singleton(0), true);
			list_free(having_vars);
		}
	}
}