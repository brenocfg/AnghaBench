#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int simple_rel_array_size; TYPE_2__** simple_rte_array; TYPE_1__** simple_rel_array; } ;
struct TYPE_9__ {scalar_t__ inh; } ;
struct TYPE_8__ {scalar_t__ reloptkind; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ PlannerInfo ;

/* Variables and functions */
 scalar_t__ RELOPT_BASEREL ; 
 int /*<<< orphan*/  expand_inherited_rtentry (TYPE_3__*,TYPE_1__*,TYPE_2__*,int) ; 

void
add_other_rels_to_query(PlannerInfo *root)
{
	int			rti;

	for (rti = 1; rti < root->simple_rel_array_size; rti++)
	{
		RelOptInfo *rel = root->simple_rel_array[rti];
		RangeTblEntry *rte = root->simple_rte_array[rti];

		/* there may be empty slots corresponding to non-baserel RTEs */
		if (rel == NULL)
			continue;

		/* Ignore any "otherrels" that were already added. */
		if (rel->reloptkind != RELOPT_BASEREL)
			continue;

		/* If it's marked as inheritable, look for children. */
		if (rte->inh)
			expand_inherited_rtentry(root, rel, rte, rti);
	}
}