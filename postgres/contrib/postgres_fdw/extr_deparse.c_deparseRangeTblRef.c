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
struct TYPE_11__ {scalar_t__ local_conds; int relation_index; int /*<<< orphan*/  remote_conds; } ;
struct TYPE_10__ {TYPE_1__* reltarget; int /*<<< orphan*/  relids; scalar_t__ fdw_private; } ;
struct TYPE_9__ {int /*<<< orphan*/  exprs; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ PgFdwRelationInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IS_JOIN_REL (TYPE_2__*) ; 
 scalar_t__ IS_SIMPLE_REL (TYPE_2__*) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  SUBQUERY_COL_ALIAS_PREFIX ; 
 int /*<<< orphan*/  SUBQUERY_REL_ALIAS_PREFIX ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bms_is_member (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deparseFromExprForRel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  deparseSelectStmtForRel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deparseRangeTblRef(StringInfo buf, PlannerInfo *root, RelOptInfo *foreignrel,
				   bool make_subquery, Index ignore_rel, List **ignore_conds,
				   List **params_list)
{
	PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) foreignrel->fdw_private;

	/* Should only be called in these cases. */
	Assert(IS_SIMPLE_REL(foreignrel) || IS_JOIN_REL(foreignrel));

	Assert(fpinfo->local_conds == NIL);

	/* If make_subquery is true, deparse the relation as a subquery. */
	if (make_subquery)
	{
		List	   *retrieved_attrs;
		int			ncols;

		/*
		 * The given relation shouldn't contain the target relation, because
		 * this should only happen for input relations for a full join, and
		 * such relations can never contain an UPDATE/DELETE target.
		 */
		Assert(ignore_rel == 0 ||
			   !bms_is_member(ignore_rel, foreignrel->relids));

		/* Deparse the subquery representing the relation. */
		appendStringInfoChar(buf, '(');
		deparseSelectStmtForRel(buf, root, foreignrel, NIL,
								fpinfo->remote_conds, NIL,
								false, false, true,
								&retrieved_attrs, params_list);
		appendStringInfoChar(buf, ')');

		/* Append the relation alias. */
		appendStringInfo(buf, " %s%d", SUBQUERY_REL_ALIAS_PREFIX,
						 fpinfo->relation_index);

		/*
		 * Append the column aliases if needed.  Note that the subquery emits
		 * expressions specified in the relation's reltarget (see
		 * deparseSubqueryTargetList).
		 */
		ncols = list_length(foreignrel->reltarget->exprs);
		if (ncols > 0)
		{
			int			i;

			appendStringInfoChar(buf, '(');
			for (i = 1; i <= ncols; i++)
			{
				if (i > 1)
					appendStringInfoString(buf, ", ");

				appendStringInfo(buf, "%s%d", SUBQUERY_COL_ALIAS_PREFIX, i);
			}
			appendStringInfoChar(buf, ')');
		}
	}
	else
		deparseFromExprForRel(buf, root, foreignrel, true, ignore_rel,
							  ignore_conds, params_list);
}