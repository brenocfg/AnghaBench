#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nargs; int sublevels_up; int /*<<< orphan*/ * args; } ;
typedef  TYPE_1__ substitute_actual_srf_parameters_context ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * query_tree_mutator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substitute_actual_srf_parameters_mutator ; 

__attribute__((used)) static Query *
substitute_actual_srf_parameters(Query *expr, int nargs, List *args)
{
	substitute_actual_srf_parameters_context context;

	context.nargs = nargs;
	context.args = args;
	context.sublevels_up = 1;

	return query_tree_mutator(expr,
							  substitute_actual_srf_parameters_mutator,
							  &context,
							  0);
}