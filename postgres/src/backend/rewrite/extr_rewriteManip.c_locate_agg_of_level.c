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
struct TYPE_2__ {int agg_location; int sublevels_up; } ;
typedef  TYPE_1__ locate_agg_of_level_context ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  locate_agg_of_level_walker ; 
 int /*<<< orphan*/  query_or_expression_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int
locate_agg_of_level(Node *node, int levelsup)
{
	locate_agg_of_level_context context;

	context.agg_location = -1;	/* in case we find nothing */
	context.sublevels_up = levelsup;

	/*
	 * Must be prepared to start with a Query or a bare expression tree; if
	 * it's a Query, we don't want to increment sublevels_up.
	 */
	(void) query_or_expression_tree_walker(node,
										   locate_agg_of_level_walker,
										   (void *) &context,
										   0);

	return context.agg_location;
}