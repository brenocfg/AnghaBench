#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  rows; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; TYPE_1__* pathtarget; } ;
struct TYPE_15__ {double tuple_fraction; } ;
struct TYPE_14__ {int /*<<< orphan*/  width; } ;
typedef  double Size ;
typedef  TYPE_2__ PlannerInfo ;
typedef  TYPE_3__ Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_HASHED ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 double MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  SizeofMinimalTupleHeader ; 
 scalar_t__ compare_fractional_path_costs (TYPE_3__*,TYPE_3__*,double) ; 
 int /*<<< orphan*/  cost_agg (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cost_group (TYPE_3__*,TYPE_2__*,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cost_sort (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,long,double) ; 
 int /*<<< orphan*/  enable_hashagg ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int grouping_is_hashable (int /*<<< orphan*/ *) ; 
 int grouping_is_sortable (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 long work_mem ; 

__attribute__((used)) static bool
choose_hashed_setop(PlannerInfo *root, List *groupClauses,
					Path *input_path,
					double dNumGroups, double dNumOutputRows,
					const char *construct)
{
	int			numGroupCols = list_length(groupClauses);
	bool		can_sort;
	bool		can_hash;
	Size		hashentrysize;
	Path		hashed_p;
	Path		sorted_p;
	double		tuple_fraction;

	/* Check whether the operators support sorting or hashing */
	can_sort = grouping_is_sortable(groupClauses);
	can_hash = grouping_is_hashable(groupClauses);
	if (can_hash && can_sort)
	{
		/* we have a meaningful choice to make, continue ... */
	}
	else if (can_hash)
		return true;
	else if (can_sort)
		return false;
	else
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
		/* translator: %s is UNION, INTERSECT, or EXCEPT */
				 errmsg("could not implement %s", construct),
				 errdetail("Some of the datatypes only support hashing, while others only support sorting.")));

	/* Prefer sorting when enable_hashagg is off */
	if (!enable_hashagg)
		return false;

	/*
	 * Don't do it if it doesn't look like the hashtable will fit into
	 * work_mem.
	 */
	hashentrysize = MAXALIGN(input_path->pathtarget->width) + MAXALIGN(SizeofMinimalTupleHeader);

	if (hashentrysize * dNumGroups > work_mem * 1024L)
		return false;

	/*
	 * See if the estimated cost is no more than doing it the other way.
	 *
	 * We need to consider input_plan + hashagg versus input_plan + sort +
	 * group.  Note that the actual result plan might involve a SetOp or
	 * Unique node, not Agg or Group, but the cost estimates for Agg and Group
	 * should be close enough for our purposes here.
	 *
	 * These path variables are dummies that just hold cost fields; we don't
	 * make actual Paths for these steps.
	 */
	cost_agg(&hashed_p, root, AGG_HASHED, NULL,
			 numGroupCols, dNumGroups,
			 NIL,
			 input_path->startup_cost, input_path->total_cost,
			 input_path->rows);

	/*
	 * Now for the sorted case.  Note that the input is *always* unsorted,
	 * since it was made by appending unrelated sub-relations together.
	 */
	sorted_p.startup_cost = input_path->startup_cost;
	sorted_p.total_cost = input_path->total_cost;
	/* XXX cost_sort doesn't actually look at pathkeys, so just pass NIL */
	cost_sort(&sorted_p, root, NIL, sorted_p.total_cost,
			  input_path->rows, input_path->pathtarget->width,
			  0.0, work_mem, -1.0);
	cost_group(&sorted_p, root, numGroupCols, dNumGroups,
			   NIL,
			   sorted_p.startup_cost, sorted_p.total_cost,
			   input_path->rows);

	/*
	 * Now make the decision using the top-level tuple fraction.  First we
	 * have to convert an absolute count (LIMIT) into fractional form.
	 */
	tuple_fraction = root->tuple_fraction;
	if (tuple_fraction >= 1.0)
		tuple_fraction /= dNumOutputRows;

	if (compare_fractional_path_costs(&hashed_p, &sorted_p,
									  tuple_fraction) < 0)
	{
		/* Hashed is cheaper, so use it */
		return true;
	}
	return false;
}