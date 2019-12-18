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
struct TYPE_2__ {int /*<<< orphan*/ * varnos; scalar_t__ sublevels_up; } ;
typedef  TYPE_1__ pull_varnos_context ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  pull_varnos_walker ; 
 int /*<<< orphan*/  query_or_expression_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

Relids
pull_varnos(Node *node)
{
	pull_varnos_context context;

	context.varnos = NULL;
	context.sublevels_up = 0;

	/*
	 * Must be prepared to start with a Query or a bare expression tree; if
	 * it's a Query, we don't want to increment sublevels_up.
	 */
	query_or_expression_tree_walker(node,
									pull_varnos_walker,
									(void *) &context,
									0);

	return context.varnos;
}