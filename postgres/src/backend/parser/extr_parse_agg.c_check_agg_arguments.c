#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int min_varlevel; int min_agglevel; scalar_t__ sublevels_up; int /*<<< orphan*/ * pstate; } ;
typedef  TYPE_1__ check_agg_arguments_context ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_GROUPING_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  check_agg_arguments_walker ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  expression_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int locate_agg_of_level (int /*<<< orphan*/ *,int) ; 
 int locate_var_of_level (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
check_agg_arguments(ParseState *pstate,
					List *directargs,
					List *args,
					Expr *filter)
{
	int			agglevel;
	check_agg_arguments_context context;

	context.pstate = pstate;
	context.min_varlevel = -1;	/* signifies nothing found yet */
	context.min_agglevel = -1;
	context.sublevels_up = 0;

	(void) expression_tree_walker((Node *) args,
								  check_agg_arguments_walker,
								  (void *) &context);

	(void) expression_tree_walker((Node *) filter,
								  check_agg_arguments_walker,
								  (void *) &context);

	/*
	 * If we found no vars nor aggs at all, it's a level-zero aggregate;
	 * otherwise, its level is the minimum of vars or aggs.
	 */
	if (context.min_varlevel < 0)
	{
		if (context.min_agglevel < 0)
			agglevel = 0;
		else
			agglevel = context.min_agglevel;
	}
	else if (context.min_agglevel < 0)
		agglevel = context.min_varlevel;
	else
		agglevel = Min(context.min_varlevel, context.min_agglevel);

	/*
	 * If there's a nested aggregate of the same semantic level, complain.
	 */
	if (agglevel == context.min_agglevel)
	{
		int			aggloc;

		aggloc = locate_agg_of_level((Node *) args, agglevel);
		if (aggloc < 0)
			aggloc = locate_agg_of_level((Node *) filter, agglevel);
		ereport(ERROR,
				(errcode(ERRCODE_GROUPING_ERROR),
				 errmsg("aggregate function calls cannot be nested"),
				 parser_errposition(pstate, aggloc)));
	}

	/*
	 * Now check for vars/aggs in the direct arguments, and throw error if
	 * needed.  Note that we allow a Var of the agg's semantic level, but not
	 * an Agg of that level.  In principle such Aggs could probably be
	 * supported, but it would create an ordering dependency among the
	 * aggregates at execution time.  Since the case appears neither to be
	 * required by spec nor particularly useful, we just treat it as a
	 * nested-aggregate situation.
	 */
	if (directargs)
	{
		context.min_varlevel = -1;
		context.min_agglevel = -1;
		(void) expression_tree_walker((Node *) directargs,
									  check_agg_arguments_walker,
									  (void *) &context);
		if (context.min_varlevel >= 0 && context.min_varlevel < agglevel)
			ereport(ERROR,
					(errcode(ERRCODE_GROUPING_ERROR),
					 errmsg("outer-level aggregate cannot contain a lower-level variable in its direct arguments"),
					 parser_errposition(pstate,
										locate_var_of_level((Node *) directargs,
															context.min_varlevel))));
		if (context.min_agglevel >= 0 && context.min_agglevel <= agglevel)
			ereport(ERROR,
					(errcode(ERRCODE_GROUPING_ERROR),
					 errmsg("aggregate function calls cannot be nested"),
					 parser_errposition(pstate,
										locate_agg_of_level((Node *) directargs,
															context.min_agglevel))));
	}
	return agglevel;
}