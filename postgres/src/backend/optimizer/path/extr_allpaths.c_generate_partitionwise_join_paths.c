#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nparts; struct TYPE_11__** part_rels; int /*<<< orphan*/  consider_partitionwise_join; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DUMMY_REL (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_JOIN_REL (TYPE_1__*) ; 
 int /*<<< orphan*/  IS_PARTITIONED_REL (TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  add_paths_to_append_rel (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  debug_print_rel (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_dummy_rel (TYPE_1__*) ; 
 int /*<<< orphan*/  set_cheapest (TYPE_1__*) ; 

void
generate_partitionwise_join_paths(PlannerInfo *root, RelOptInfo *rel)
{
	List	   *live_children = NIL;
	int			cnt_parts;
	int			num_parts;
	RelOptInfo **part_rels;

	/* Handle only join relations here. */
	if (!IS_JOIN_REL(rel))
		return;

	/* We've nothing to do if the relation is not partitioned. */
	if (!IS_PARTITIONED_REL(rel))
		return;

	/* The relation should have consider_partitionwise_join set. */
	Assert(rel->consider_partitionwise_join);

	/* Guard against stack overflow due to overly deep partition hierarchy. */
	check_stack_depth();

	num_parts = rel->nparts;
	part_rels = rel->part_rels;

	/* Collect non-dummy child-joins. */
	for (cnt_parts = 0; cnt_parts < num_parts; cnt_parts++)
	{
		RelOptInfo *child_rel = part_rels[cnt_parts];

		/* If it's been pruned entirely, it's certainly dummy. */
		if (child_rel == NULL)
			continue;

		/* Add partitionwise join paths for partitioned child-joins. */
		generate_partitionwise_join_paths(root, child_rel);

		set_cheapest(child_rel);

		/* Dummy children will not be scanned, so ignore those. */
		if (IS_DUMMY_REL(child_rel))
			continue;

#ifdef OPTIMIZER_DEBUG
		debug_print_rel(root, child_rel);
#endif

		live_children = lappend(live_children, child_rel);
	}

	/* If all child-joins are dummy, parent join is also dummy. */
	if (!live_children)
	{
		mark_dummy_rel(rel);
		return;
	}

	/* Build additional paths for this rel from child-join paths. */
	add_paths_to_append_rel(root, rel, live_children);
	list_free(live_children);
}