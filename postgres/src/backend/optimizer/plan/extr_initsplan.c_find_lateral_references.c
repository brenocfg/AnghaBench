#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t simple_rel_array_size; TYPE_1__** simple_rel_array; int /*<<< orphan*/  hasLateralRTEs; } ;
struct TYPE_6__ {size_t relid; scalar_t__ reloptkind; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  size_t Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RELOPT_BASEREL ; 
 int /*<<< orphan*/  extract_lateral_references (TYPE_2__*,TYPE_1__*,size_t) ; 

void
find_lateral_references(PlannerInfo *root)
{
	Index		rti;

	/* We need do nothing if the query contains no LATERAL RTEs */
	if (!root->hasLateralRTEs)
		return;

	/*
	 * Examine all baserels (the rel array has been set up by now).
	 */
	for (rti = 1; rti < root->simple_rel_array_size; rti++)
	{
		RelOptInfo *brel = root->simple_rel_array[rti];

		/* there may be empty slots corresponding to non-baserel RTEs */
		if (brel == NULL)
			continue;

		Assert(brel->relid == rti); /* sanity check on array */

		/*
		 * This bit is less obvious than it might look.  We ignore appendrel
		 * otherrels and consider only their parent baserels.  In a case where
		 * a LATERAL-containing UNION ALL subquery was pulled up, it is the
		 * otherrel that is actually going to be in the plan.  However, we
		 * want to mark all its lateral references as needed by the parent,
		 * because it is the parent's relid that will be used for join
		 * planning purposes.  And the parent's RTE will contain all the
		 * lateral references we need to know, since the pulled-up member is
		 * nothing but a copy of parts of the original RTE's subquery.  We
		 * could visit the parent's children instead and transform their
		 * references back to the parent's relid, but it would be much more
		 * complicated for no real gain.  (Important here is that the child
		 * members have not yet received any processing beyond being pulled
		 * up.)  Similarly, in appendrels created by inheritance expansion,
		 * it's sufficient to look at the parent relation.
		 */

		/* ignore RTEs that are "other rels" */
		if (brel->reloptkind != RELOPT_BASEREL)
			continue;

		extract_lateral_references(root, brel, rti);
	}
}