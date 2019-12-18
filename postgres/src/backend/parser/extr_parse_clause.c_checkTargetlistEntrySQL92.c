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
struct TYPE_6__ {scalar_t__ expr; } ;
typedef  TYPE_1__ TargetEntry ;
struct TYPE_7__ {int /*<<< orphan*/  p_hasWindowFuncs; int /*<<< orphan*/  p_hasAggs; } ;
typedef  TYPE_2__ ParseState ;
typedef  int ParseExprKind ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_GROUPING_ERROR ; 
 int /*<<< orphan*/  ERRCODE_WINDOWING_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
#define  EXPR_KIND_DISTINCT_ON 130 
#define  EXPR_KIND_GROUP_BY 129 
#define  EXPR_KIND_ORDER_BY 128 
 int /*<<< orphan*/  ParseExprKindName (int) ; 
 int /*<<< orphan*/  contain_aggs_of_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  contain_windowfuncs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locate_agg_of_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locate_windowfunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
checkTargetlistEntrySQL92(ParseState *pstate, TargetEntry *tle,
						  ParseExprKind exprKind)
{
	switch (exprKind)
	{
		case EXPR_KIND_GROUP_BY:
			/* reject aggregates and window functions */
			if (pstate->p_hasAggs &&
				contain_aggs_of_level((Node *) tle->expr, 0))
				ereport(ERROR,
						(errcode(ERRCODE_GROUPING_ERROR),
				/* translator: %s is name of a SQL construct, eg GROUP BY */
						 errmsg("aggregate functions are not allowed in %s",
								ParseExprKindName(exprKind)),
						 parser_errposition(pstate,
											locate_agg_of_level((Node *) tle->expr, 0))));
			if (pstate->p_hasWindowFuncs &&
				contain_windowfuncs((Node *) tle->expr))
				ereport(ERROR,
						(errcode(ERRCODE_WINDOWING_ERROR),
				/* translator: %s is name of a SQL construct, eg GROUP BY */
						 errmsg("window functions are not allowed in %s",
								ParseExprKindName(exprKind)),
						 parser_errposition(pstate,
											locate_windowfunc((Node *) tle->expr))));
			break;
		case EXPR_KIND_ORDER_BY:
			/* no extra checks needed */
			break;
		case EXPR_KIND_DISTINCT_ON:
			/* no extra checks needed */
			break;
		default:
			elog(ERROR, "unexpected exprKind in checkTargetlistEntrySQL92");
			break;
	}
}