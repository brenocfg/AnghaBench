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
struct TYPE_3__ {int nargs; int* usecounts; int /*<<< orphan*/ * args; } ;
typedef  TYPE_1__ substitute_actual_parameters_context ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * substitute_actual_parameters_mutator (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Node *
substitute_actual_parameters(Node *expr, int nargs, List *args,
							 int *usecounts)
{
	substitute_actual_parameters_context context;

	context.nargs = nargs;
	context.args = args;
	context.usecounts = usecounts;

	return substitute_actual_parameters_mutator(expr, &context);
}