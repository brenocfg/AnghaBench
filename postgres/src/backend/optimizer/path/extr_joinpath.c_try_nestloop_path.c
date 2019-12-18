#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
struct TYPE_29__ {int /*<<< orphan*/  restrictlist; int /*<<< orphan*/  param_source_rels; } ;
struct TYPE_28__ {TYPE_1__* parent; } ;
struct TYPE_27__ {scalar_t__ relids; scalar_t__ top_parent_relids; } ;
typedef  scalar_t__ Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  TYPE_3__ JoinPathExtraData ;
typedef  TYPE_4__ JoinCostWorkspace ;

/* Variables and functions */
 scalar_t__ PATH_PARAM_BY_PARENT (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ PATH_REQ_OUTER (TYPE_2__*) ; 
 int /*<<< orphan*/  add_path (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ add_path_precheck (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  allow_star_schema_join (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bms_free (scalar_t__) ; 
 int /*<<< orphan*/  bms_overlap (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ calc_nestloop_required_outer (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ create_nestloop_path (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ have_dangerous_phv (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  initial_cost_nestloop (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_3__*) ; 
 TYPE_2__* reparameterize_path_by_child (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void
try_nestloop_path(PlannerInfo *root,
				  RelOptInfo *joinrel,
				  Path *outer_path,
				  Path *inner_path,
				  List *pathkeys,
				  JoinType jointype,
				  JoinPathExtraData *extra)
{
	Relids		required_outer;
	JoinCostWorkspace workspace;
	RelOptInfo *innerrel = inner_path->parent;
	RelOptInfo *outerrel = outer_path->parent;
	Relids		innerrelids;
	Relids		outerrelids;
	Relids		inner_paramrels = PATH_REQ_OUTER(inner_path);
	Relids		outer_paramrels = PATH_REQ_OUTER(outer_path);

	/*
	 * Paths are parameterized by top-level parents, so run parameterization
	 * tests on the parent relids.
	 */
	if (innerrel->top_parent_relids)
		innerrelids = innerrel->top_parent_relids;
	else
		innerrelids = innerrel->relids;

	if (outerrel->top_parent_relids)
		outerrelids = outerrel->top_parent_relids;
	else
		outerrelids = outerrel->relids;

	/*
	 * Check to see if proposed path is still parameterized, and reject if the
	 * parameterization wouldn't be sensible --- unless allow_star_schema_join
	 * says to allow it anyway.  Also, we must reject if have_dangerous_phv
	 * doesn't like the look of it, which could only happen if the nestloop is
	 * still parameterized.
	 */
	required_outer = calc_nestloop_required_outer(outerrelids, outer_paramrels,
												  innerrelids, inner_paramrels);
	if (required_outer &&
		((!bms_overlap(required_outer, extra->param_source_rels) &&
		  !allow_star_schema_join(root, outerrelids, inner_paramrels)) ||
		 have_dangerous_phv(root, outerrelids, inner_paramrels)))
	{
		/* Waste no memory when we reject a path here */
		bms_free(required_outer);
		return;
	}

	/*
	 * Do a precheck to quickly eliminate obviously-inferior paths.  We
	 * calculate a cheap lower bound on the path's cost and then use
	 * add_path_precheck() to see if the path is clearly going to be dominated
	 * by some existing path for the joinrel.  If not, do the full pushup with
	 * creating a fully valid path structure and submitting it to add_path().
	 * The latter two steps are expensive enough to make this two-phase
	 * methodology worthwhile.
	 */
	initial_cost_nestloop(root, &workspace, jointype,
						  outer_path, inner_path, extra);

	if (add_path_precheck(joinrel,
						  workspace.startup_cost, workspace.total_cost,
						  pathkeys, required_outer))
	{
		/*
		 * If the inner path is parameterized, it is parameterized by the
		 * topmost parent of the outer rel, not the outer rel itself.  Fix
		 * that.
		 */
		if (PATH_PARAM_BY_PARENT(inner_path, outer_path->parent))
		{
			inner_path = reparameterize_path_by_child(root, inner_path,
													  outer_path->parent);

			/*
			 * If we could not translate the path, we can't create nest loop
			 * path.
			 */
			if (!inner_path)
			{
				bms_free(required_outer);
				return;
			}
		}

		add_path(joinrel, (Path *)
				 create_nestloop_path(root,
									  joinrel,
									  jointype,
									  &workspace,
									  extra,
									  outer_path,
									  inner_path,
									  extra->restrictlist,
									  pathkeys,
									  required_outer));
	}
	else
	{
		/* Waste no memory when we reject a path here */
		bms_free(required_outer);
	}
}