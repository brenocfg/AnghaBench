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
struct TYPE_2__ {int sublevels_up; int /*<<< orphan*/ * vars; } ;
typedef  TYPE_1__ pull_vars_context ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  pull_vars_walker ; 
 int /*<<< orphan*/  query_or_expression_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

List *
pull_vars_of_level(Node *node, int levelsup)
{
	pull_vars_context context;

	context.vars = NIL;
	context.sublevels_up = levelsup;

	/*
	 * Must be prepared to start with a Query or a bare expression tree; if
	 * it's a Query, we don't want to increment sublevels_up.
	 */
	query_or_expression_tree_walker(node,
									pull_vars_walker,
									(void *) &context,
									0);

	return context.vars;
}