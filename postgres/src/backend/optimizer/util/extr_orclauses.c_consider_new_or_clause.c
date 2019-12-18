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
struct TYPE_11__ {int /*<<< orphan*/  relids; int /*<<< orphan*/  baserestrict_min_security; int /*<<< orphan*/  baserestrictinfo; } ;
struct TYPE_10__ {double norm_selec; int /*<<< orphan*/  clause_relids; int /*<<< orphan*/  security_level; } ;
struct TYPE_9__ {int lhs_strict; int delay_upper_joins; int semi_can_btree; int semi_can_hash; void* semi_rhs_exprs; void* semi_operators; int /*<<< orphan*/  jointype; int /*<<< orphan*/  min_righthand; int /*<<< orphan*/  syn_righthand; int /*<<< orphan*/  min_lefthand; int /*<<< orphan*/  syn_lefthand; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SpecialJoinInfo ;
typedef  double Selectivity ;
typedef  TYPE_2__ RestrictInfo ;
typedef  TYPE_3__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  JOIN_INNER ; 
 int /*<<< orphan*/  Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* NIL ; 
 int /*<<< orphan*/  T_SpecialJoinInfo ; 
 int /*<<< orphan*/  bms_difference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double clause_selectivity (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* make_restrictinfo (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
consider_new_or_clause(PlannerInfo *root, RelOptInfo *rel,
					   Expr *orclause, RestrictInfo *join_or_rinfo)
{
	RestrictInfo *or_rinfo;
	Selectivity or_selec,
				orig_selec;

	/*
	 * Build a RestrictInfo from the new OR clause.  We can assume it's valid
	 * as a base restriction clause.
	 */
	or_rinfo = make_restrictinfo(orclause,
								 true,
								 false,
								 false,
								 join_or_rinfo->security_level,
								 NULL,
								 NULL,
								 NULL);

	/*
	 * Estimate its selectivity.  (We could have done this earlier, but doing
	 * it on the RestrictInfo representation allows the result to get cached,
	 * saving work later.)
	 */
	or_selec = clause_selectivity(root, (Node *) or_rinfo,
								  0, JOIN_INNER, NULL);

	/*
	 * The clause is only worth adding to the query if it rejects a useful
	 * fraction of the base relation's rows; otherwise, it's just going to
	 * cause duplicate computation (since we will still have to check the
	 * original OR clause when the join is formed).  Somewhat arbitrarily, we
	 * set the selectivity threshold at 0.9.
	 */
	if (or_selec > 0.9)
		return;					/* forget it */

	/*
	 * OK, add it to the rel's restriction-clause list.
	 */
	rel->baserestrictinfo = lappend(rel->baserestrictinfo, or_rinfo);
	rel->baserestrict_min_security = Min(rel->baserestrict_min_security,
										 or_rinfo->security_level);

	/*
	 * Adjust the original join OR clause's cached selectivity to compensate
	 * for the selectivity of the added (but redundant) lower-level qual. This
	 * should result in the join rel getting approximately the same rows
	 * estimate as it would have gotten without all these shenanigans.
	 *
	 * XXX major hack alert: this depends on the assumption that the
	 * selectivity will stay cached.
	 *
	 * XXX another major hack: we adjust only norm_selec, the cached
	 * selectivity for JOIN_INNER semantics, even though the join clause
	 * might've been an outer-join clause.  This is partly because we can't
	 * easily identify the relevant SpecialJoinInfo here, and partly because
	 * the linearity assumption we're making would fail anyway.  (If it is an
	 * outer-join clause, "rel" must be on the nullable side, else we'd not
	 * have gotten here.  So the computation of the join size is going to be
	 * quite nonlinear with respect to the size of "rel", so it's not clear
	 * how we ought to adjust outer_selec even if we could compute its
	 * original value correctly.)
	 */
	if (or_selec > 0)
	{
		SpecialJoinInfo sjinfo;

		/*
		 * Make up a SpecialJoinInfo for JOIN_INNER semantics.  (Compare
		 * approx_tuple_count() in costsize.c.)
		 */
		sjinfo.type = T_SpecialJoinInfo;
		sjinfo.min_lefthand = bms_difference(join_or_rinfo->clause_relids,
											 rel->relids);
		sjinfo.min_righthand = rel->relids;
		sjinfo.syn_lefthand = sjinfo.min_lefthand;
		sjinfo.syn_righthand = sjinfo.min_righthand;
		sjinfo.jointype = JOIN_INNER;
		/* we don't bother trying to make the remaining fields valid */
		sjinfo.lhs_strict = false;
		sjinfo.delay_upper_joins = false;
		sjinfo.semi_can_btree = false;
		sjinfo.semi_can_hash = false;
		sjinfo.semi_operators = NIL;
		sjinfo.semi_rhs_exprs = NIL;

		/* Compute inner-join size */
		orig_selec = clause_selectivity(root, (Node *) join_or_rinfo,
										0, JOIN_INNER, &sjinfo);

		/* And hack cached selectivity so join size remains the same */
		join_or_rinfo->norm_selec = orig_selec / or_selec;
		/* ensure result stays in sane range, in particular not "redundant" */
		if (join_or_rinfo->norm_selec > 1)
			join_or_rinfo->norm_selec = 1;
		/* as explained above, we don't touch outer_selec */
	}
}