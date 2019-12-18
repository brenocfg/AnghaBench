#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int hasLateralRTEs; int hasPseudoConstantQuals; int /*<<< orphan*/ * full_join_clauses; int /*<<< orphan*/ * right_join_clauses; int /*<<< orphan*/ * left_join_clauses; TYPE_1__* parse; } ;
struct TYPE_21__ {int /*<<< orphan*/ * left_relids; int /*<<< orphan*/ * right_relids; scalar_t__ can_join; scalar_t__ mergeopfamilies; int /*<<< orphan*/ * relids; int /*<<< orphan*/ * qual; } ;
struct TYPE_20__ {scalar_t__ jointree; } ;
typedef  TYPE_2__ RestrictInfo ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  TYPE_2__ PostponedQual ;
typedef  TYPE_4__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ JoinType ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BMS_MULTIPLE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ JOIN_FULL ; 
 scalar_t__ JOIN_INNER ; 
 int PVC_INCLUDE_PLACEHOLDERS ; 
 int PVC_RECURSE_AGGREGATES ; 
 int PVC_RECURSE_WINDOWFUNCS ; 
 int /*<<< orphan*/  add_vars_to_targetlist (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * bms_copy (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bms_membership (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ check_equivalence_delay (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  check_mergejoinable (TYPE_2__*) ; 
 int check_outerjoin_delay (TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 scalar_t__ check_redundant_nullability_qual (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  contain_volatile_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  distribute_restrictinfo_to_rels (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * get_relids_in_jointree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  initialize_mergeclause_eclasses (TYPE_4__*,TYPE_2__*) ; 
 void* lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* make_restrictinfo (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ process_equivalence (TYPE_4__*,TYPE_2__**,int) ; 
 int /*<<< orphan*/ * pull_var_clause (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pull_varnos (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
distribute_qual_to_rels(PlannerInfo *root, Node *clause,
						bool is_deduced,
						bool below_outer_join,
						JoinType jointype,
						Index security_level,
						Relids qualscope,
						Relids ojscope,
						Relids outerjoin_nonnullable,
						Relids deduced_nullable_relids,
						List **postponed_qual_list)
{
	Relids		relids;
	bool		is_pushed_down;
	bool		outerjoin_delayed;
	bool		pseudoconstant = false;
	bool		maybe_equivalence;
	bool		maybe_outer_join;
	Relids		nullable_relids;
	RestrictInfo *restrictinfo;

	/*
	 * Retrieve all relids mentioned within the clause.
	 */
	relids = pull_varnos(clause);

	/*
	 * In ordinary SQL, a WHERE or JOIN/ON clause can't reference any rels
	 * that aren't within its syntactic scope; however, if we pulled up a
	 * LATERAL subquery then we might find such references in quals that have
	 * been pulled up.  We need to treat such quals as belonging to the join
	 * level that includes every rel they reference.  Although we could make
	 * pull_up_subqueries() place such quals correctly to begin with, it's
	 * easier to handle it here.  When we find a clause that contains Vars
	 * outside its syntactic scope, we add it to the postponed-quals list, and
	 * process it once we've recursed back up to the appropriate join level.
	 */
	if (!bms_is_subset(relids, qualscope))
	{
		PostponedQual *pq = (PostponedQual *) palloc(sizeof(PostponedQual));

		Assert(root->hasLateralRTEs);	/* shouldn't happen otherwise */
		Assert(jointype == JOIN_INNER); /* mustn't postpone past outer join */
		Assert(!is_deduced);	/* shouldn't be deduced, either */
		pq->qual = clause;
		pq->relids = relids;
		*postponed_qual_list = lappend(*postponed_qual_list, pq);
		return;
	}

	/*
	 * If it's an outer-join clause, also check that relids is a subset of
	 * ojscope.  (This should not fail if the syntactic scope check passed.)
	 */
	if (ojscope && !bms_is_subset(relids, ojscope))
		elog(ERROR, "JOIN qualification cannot refer to other relations");

	/*
	 * If the clause is variable-free, our normal heuristic for pushing it
	 * down to just the mentioned rels doesn't work, because there are none.
	 *
	 * If the clause is an outer-join clause, we must force it to the OJ's
	 * semantic level to preserve semantics.
	 *
	 * Otherwise, when the clause contains volatile functions, we force it to
	 * be evaluated at its original syntactic level.  This preserves the
	 * expected semantics.
	 *
	 * When the clause contains no volatile functions either, it is actually a
	 * pseudoconstant clause that will not change value during any one
	 * execution of the plan, and hence can be used as a one-time qual in a
	 * gating Result plan node.  We put such a clause into the regular
	 * RestrictInfo lists for the moment, but eventually createplan.c will
	 * pull it out and make a gating Result node immediately above whatever
	 * plan node the pseudoconstant clause is assigned to.  It's usually best
	 * to put a gating node as high in the plan tree as possible. If we are
	 * not below an outer join, we can actually push the pseudoconstant qual
	 * all the way to the top of the tree.  If we are below an outer join, we
	 * leave the qual at its original syntactic level (we could push it up to
	 * just below the outer join, but that seems more complex than it's
	 * worth).
	 */
	if (bms_is_empty(relids))
	{
		if (ojscope)
		{
			/* clause is attached to outer join, eval it there */
			relids = bms_copy(ojscope);
			/* mustn't use as gating qual, so don't mark pseudoconstant */
		}
		else
		{
			/* eval at original syntactic level */
			relids = bms_copy(qualscope);
			if (!contain_volatile_functions(clause))
			{
				/* mark as gating qual */
				pseudoconstant = true;
				/* tell createplan.c to check for gating quals */
				root->hasPseudoConstantQuals = true;
				/* if not below outer join, push it to top of tree */
				if (!below_outer_join)
				{
					relids =
						get_relids_in_jointree((Node *) root->parse->jointree,
											   false);
					qualscope = bms_copy(relids);
				}
			}
		}
	}

	/*----------
	 * Check to see if clause application must be delayed by outer-join
	 * considerations.
	 *
	 * A word about is_pushed_down: we mark the qual as "pushed down" if
	 * it is (potentially) applicable at a level different from its original
	 * syntactic level.  This flag is used to distinguish OUTER JOIN ON quals
	 * from other quals pushed down to the same joinrel.  The rules are:
	 *		WHERE quals and INNER JOIN quals: is_pushed_down = true.
	 *		Non-degenerate OUTER JOIN quals: is_pushed_down = false.
	 *		Degenerate OUTER JOIN quals: is_pushed_down = true.
	 * A "degenerate" OUTER JOIN qual is one that doesn't mention the
	 * non-nullable side, and hence can be pushed down into the nullable side
	 * without changing the join result.  It is correct to treat it as a
	 * regular filter condition at the level where it is evaluated.
	 *
	 * Note: it is not immediately obvious that a simple boolean is enough
	 * for this: if for some reason we were to attach a degenerate qual to
	 * its original join level, it would need to be treated as an outer join
	 * qual there.  However, this cannot happen, because all the rels the
	 * clause mentions must be in the outer join's min_righthand, therefore
	 * the join it needs must be formed before the outer join; and we always
	 * attach quals to the lowest level where they can be evaluated.  But
	 * if we were ever to re-introduce a mechanism for delaying evaluation
	 * of "expensive" quals, this area would need work.
	 *
	 * Note: generally, use of is_pushed_down has to go through the macro
	 * RINFO_IS_PUSHED_DOWN, because that flag alone is not always sufficient
	 * to tell whether a clause must be treated as pushed-down in context.
	 * This seems like another reason why it should perhaps be rethought.
	 *----------
	 */
	if (is_deduced)
	{
		/*
		 * If the qual came from implied-equality deduction, it should not be
		 * outerjoin-delayed, else deducer blew it.  But we can't check this
		 * because the join_info_list may now contain OJs above where the qual
		 * belongs.  For the same reason, we must rely on caller to supply the
		 * correct nullable_relids set.
		 */
		Assert(!ojscope);
		is_pushed_down = true;
		outerjoin_delayed = false;
		nullable_relids = deduced_nullable_relids;
		/* Don't feed it back for more deductions */
		maybe_equivalence = false;
		maybe_outer_join = false;
	}
	else if (bms_overlap(relids, outerjoin_nonnullable))
	{
		/*
		 * The qual is attached to an outer join and mentions (some of the)
		 * rels on the nonnullable side, so it's not degenerate.
		 *
		 * We can't use such a clause to deduce equivalence (the left and
		 * right sides might be unequal above the join because one of them has
		 * gone to NULL) ... but we might be able to use it for more limited
		 * deductions, if it is mergejoinable.  So consider adding it to the
		 * lists of set-aside outer-join clauses.
		 */
		is_pushed_down = false;
		maybe_equivalence = false;
		maybe_outer_join = true;

		/* Check to see if must be delayed by lower outer join */
		outerjoin_delayed = check_outerjoin_delay(root,
												  &relids,
												  &nullable_relids,
												  false);

		/*
		 * Now force the qual to be evaluated exactly at the level of joining
		 * corresponding to the outer join.  We cannot let it get pushed down
		 * into the nonnullable side, since then we'd produce no output rows,
		 * rather than the intended single null-extended row, for any
		 * nonnullable-side rows failing the qual.
		 *
		 * (Do this step after calling check_outerjoin_delay, because that
		 * trashes relids.)
		 */
		Assert(ojscope);
		relids = ojscope;
		Assert(!pseudoconstant);
	}
	else
	{
		/*
		 * Normal qual clause or degenerate outer-join clause.  Either way, we
		 * can mark it as pushed-down.
		 */
		is_pushed_down = true;

		/* Check to see if must be delayed by lower outer join */
		outerjoin_delayed = check_outerjoin_delay(root,
												  &relids,
												  &nullable_relids,
												  true);

		if (outerjoin_delayed)
		{
			/* Should still be a subset of current scope ... */
			Assert(root->hasLateralRTEs || bms_is_subset(relids, qualscope));
			Assert(ojscope == NULL || bms_is_subset(relids, ojscope));

			/*
			 * Because application of the qual will be delayed by outer join,
			 * we mustn't assume its vars are equal everywhere.
			 */
			maybe_equivalence = false;

			/*
			 * It's possible that this is an IS NULL clause that's redundant
			 * with a lower antijoin; if so we can just discard it.  We need
			 * not test in any of the other cases, because this will only be
			 * possible for pushed-down, delayed clauses.
			 */
			if (check_redundant_nullability_qual(root, clause))
				return;
		}
		else
		{
			/*
			 * Qual is not delayed by any lower outer-join restriction, so we
			 * can consider feeding it to the equivalence machinery. However,
			 * if it's itself within an outer-join clause, treat it as though
			 * it appeared below that outer join (note that we can only get
			 * here when the clause references only nullable-side rels).
			 */
			maybe_equivalence = true;
			if (outerjoin_nonnullable != NULL)
				below_outer_join = true;
		}

		/*
		 * Since it doesn't mention the LHS, it's certainly not useful as a
		 * set-aside OJ clause, even if it's in an OJ.
		 */
		maybe_outer_join = false;
	}

	/*
	 * Build the RestrictInfo node itself.
	 */
	restrictinfo = make_restrictinfo((Expr *) clause,
									 is_pushed_down,
									 outerjoin_delayed,
									 pseudoconstant,
									 security_level,
									 relids,
									 outerjoin_nonnullable,
									 nullable_relids);

	/*
	 * If it's a join clause (either naturally, or because delayed by
	 * outer-join rules), add vars used in the clause to targetlists of their
	 * relations, so that they will be emitted by the plan nodes that scan
	 * those relations (else they won't be available at the join node!).
	 *
	 * Note: if the clause gets absorbed into an EquivalenceClass then this
	 * may be unnecessary, but for now we have to do it to cover the case
	 * where the EC becomes ec_broken and we end up reinserting the original
	 * clauses into the plan.
	 */
	if (bms_membership(relids) == BMS_MULTIPLE)
	{
		List	   *vars = pull_var_clause(clause,
										   PVC_RECURSE_AGGREGATES |
										   PVC_RECURSE_WINDOWFUNCS |
										   PVC_INCLUDE_PLACEHOLDERS);

		add_vars_to_targetlist(root, vars, relids, false);
		list_free(vars);
	}

	/*
	 * We check "mergejoinability" of every clause, not only join clauses,
	 * because we want to know about equivalences between vars of the same
	 * relation, or between vars and consts.
	 */
	check_mergejoinable(restrictinfo);

	/*
	 * If it is a true equivalence clause, send it to the EquivalenceClass
	 * machinery.  We do *not* attach it directly to any restriction or join
	 * lists.  The EC code will propagate it to the appropriate places later.
	 *
	 * If the clause has a mergejoinable operator and is not
	 * outerjoin-delayed, yet isn't an equivalence because it is an outer-join
	 * clause, the EC code may yet be able to do something with it.  We add it
	 * to appropriate lists for further consideration later.  Specifically:
	 *
	 * If it is a left or right outer-join qualification that relates the two
	 * sides of the outer join (no funny business like leftvar1 = leftvar2 +
	 * rightvar), we add it to root->left_join_clauses or
	 * root->right_join_clauses according to which side the nonnullable
	 * variable appears on.
	 *
	 * If it is a full outer-join qualification, we add it to
	 * root->full_join_clauses.  (Ideally we'd discard cases that aren't
	 * leftvar = rightvar, as we do for left/right joins, but this routine
	 * doesn't have the info needed to do that; and the current usage of the
	 * full_join_clauses list doesn't require that, so it's not currently
	 * worth complicating this routine's API to make it possible.)
	 *
	 * If none of the above hold, pass it off to
	 * distribute_restrictinfo_to_rels().
	 *
	 * In all cases, it's important to initialize the left_ec and right_ec
	 * fields of a mergejoinable clause, so that all possibly mergejoinable
	 * expressions have representations in EquivalenceClasses.  If
	 * process_equivalence is successful, it will take care of that;
	 * otherwise, we have to call initialize_mergeclause_eclasses to do it.
	 */
	if (restrictinfo->mergeopfamilies)
	{
		if (maybe_equivalence)
		{
			if (check_equivalence_delay(root, restrictinfo) &&
				process_equivalence(root, &restrictinfo, below_outer_join))
				return;
			/* EC rejected it, so set left_ec/right_ec the hard way ... */
			if (restrictinfo->mergeopfamilies)	/* EC might have changed this */
				initialize_mergeclause_eclasses(root, restrictinfo);
			/* ... and fall through to distribute_restrictinfo_to_rels */
		}
		else if (maybe_outer_join && restrictinfo->can_join)
		{
			/* we need to set up left_ec/right_ec the hard way */
			initialize_mergeclause_eclasses(root, restrictinfo);
			/* now see if it should go to any outer-join lists */
			if (bms_is_subset(restrictinfo->left_relids,
							  outerjoin_nonnullable) &&
				!bms_overlap(restrictinfo->right_relids,
							 outerjoin_nonnullable))
			{
				/* we have outervar = innervar */
				root->left_join_clauses = lappend(root->left_join_clauses,
												  restrictinfo);
				return;
			}
			if (bms_is_subset(restrictinfo->right_relids,
							  outerjoin_nonnullable) &&
				!bms_overlap(restrictinfo->left_relids,
							 outerjoin_nonnullable))
			{
				/* we have innervar = outervar */
				root->right_join_clauses = lappend(root->right_join_clauses,
												   restrictinfo);
				return;
			}
			if (jointype == JOIN_FULL)
			{
				/* FULL JOIN (above tests cannot match in this case) */
				root->full_join_clauses = lappend(root->full_join_clauses,
												  restrictinfo);
				return;
			}
			/* nope, so fall through to distribute_restrictinfo_to_rels */
		}
		else
		{
			/* we still need to set up left_ec/right_ec */
			initialize_mergeclause_eclasses(root, restrictinfo);
		}
	}

	/* No EC special case applies, so push it into the clause lists */
	distribute_restrictinfo_to_rels(root, restrictinfo);
}