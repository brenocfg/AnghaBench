#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  int /*<<< orphan*/  PartitionPruneStep ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  GeneratePruningStepsContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/ * gen_prune_step_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_steps_using_prefix_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_head (int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_make1_oid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
get_steps_using_prefix(GeneratePruningStepsContext *context,
					   StrategyNumber step_opstrategy,
					   bool step_op_is_ne,
					   Expr *step_lastexpr,
					   Oid step_lastcmpfn,
					   int step_lastkeyno,
					   Bitmapset *step_nullkeys,
					   List *prefix)
{
	/* Quick exit if there are no values to prefix with. */
	if (list_length(prefix) == 0)
	{
		PartitionPruneStep *step;

		step = gen_prune_step_op(context,
								 step_opstrategy,
								 step_op_is_ne,
								 list_make1(step_lastexpr),
								 list_make1_oid(step_lastcmpfn),
								 step_nullkeys);
		return list_make1(step);
	}

	/* Recurse to generate steps for various combinations. */
	return get_steps_using_prefix_recurse(context,
										  step_opstrategy,
										  step_op_is_ne,
										  step_lastexpr,
										  step_lastcmpfn,
										  step_lastkeyno,
										  step_nullkeys,
										  prefix,
										  list_head(prefix),
										  NIL, NIL);
}