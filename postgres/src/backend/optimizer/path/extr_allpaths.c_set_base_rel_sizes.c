#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t simple_rel_array_size; TYPE_1__* glob; int /*<<< orphan*/ ** simple_rte_array; TYPE_2__** simple_rel_array; } ;
struct TYPE_10__ {size_t relid; scalar_t__ reloptkind; } ;
struct TYPE_9__ {scalar_t__ parallelModeOK; } ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_3__ PlannerInfo ;
typedef  size_t Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RELOPT_BASEREL ; 
 int /*<<< orphan*/  set_rel_consider_parallel (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rel_size (TYPE_3__*,TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_base_rel_sizes(PlannerInfo *root)
{
	Index		rti;

	for (rti = 1; rti < root->simple_rel_array_size; rti++)
	{
		RelOptInfo *rel = root->simple_rel_array[rti];
		RangeTblEntry *rte;

		/* there may be empty slots corresponding to non-baserel RTEs */
		if (rel == NULL)
			continue;

		Assert(rel->relid == rti);	/* sanity check on array */

		/* ignore RTEs that are "other rels" */
		if (rel->reloptkind != RELOPT_BASEREL)
			continue;

		rte = root->simple_rte_array[rti];

		/*
		 * If parallelism is allowable for this query in general, see whether
		 * it's allowable for this rel in particular.  We have to do this
		 * before set_rel_size(), because (a) if this rel is an inheritance
		 * parent, set_append_rel_size() will use and perhaps change the rel's
		 * consider_parallel flag, and (b) for some RTE types, set_rel_size()
		 * goes ahead and makes paths immediately.
		 */
		if (root->glob->parallelModeOK)
			set_rel_consider_parallel(root, rel, rte);

		set_rel_size(root, rel, rti, rte);
	}
}