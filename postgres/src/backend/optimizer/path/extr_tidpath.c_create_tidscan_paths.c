#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * joininfo; int /*<<< orphan*/  lateral_referencers; scalar_t__ has_eclass_joins; int /*<<< orphan*/  lateral_relids; int /*<<< orphan*/  baserestrictinfo; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  BuildParameterizedTidPaths (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TidQualFromRestrictInfoList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  add_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ create_tidscan_path (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_member_matches_ctid ; 
 int /*<<< orphan*/ * generate_implied_equalities_for_column (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
create_tidscan_paths(PlannerInfo *root, RelOptInfo *rel)
{
	List	   *tidquals;

	/*
	 * If any suitable quals exist in the rel's baserestrict list, generate a
	 * plain (unparameterized) TidPath with them.
	 */
	tidquals = TidQualFromRestrictInfoList(rel->baserestrictinfo, rel);

	if (tidquals)
	{
		/*
		 * This path uses no join clauses, but it could still have required
		 * parameterization due to LATERAL refs in its tlist.
		 */
		Relids		required_outer = rel->lateral_relids;

		add_path(rel, (Path *) create_tidscan_path(root, rel, tidquals,
												   required_outer));
	}

	/*
	 * Try to generate parameterized TidPaths using equality clauses extracted
	 * from EquivalenceClasses.  (This is important since simple "t1.ctid =
	 * t2.ctid" clauses will turn into ECs.)
	 */
	if (rel->has_eclass_joins)
	{
		List	   *clauses;

		/* Generate clauses, skipping any that join to lateral_referencers */
		clauses = generate_implied_equalities_for_column(root,
														 rel,
														 ec_member_matches_ctid,
														 NULL,
														 rel->lateral_referencers);

		/* Generate a path for each usable join clause */
		BuildParameterizedTidPaths(root, rel, clauses);
	}

	/*
	 * Also consider parameterized TidPaths using "loose" join quals.  Quals
	 * of the form "t1.ctid = t2.ctid" would turn into these if they are outer
	 * join quals, for example.
	 */
	BuildParameterizedTidPaths(root, rel, rel->joininfo);
}