#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inserted_sublink; int /*<<< orphan*/  possible_sublink; scalar_t__ sublevels_up; TYPE_2__* query; } ;
typedef  TYPE_1__ flatten_join_alias_vars_context ;
struct TYPE_6__ {int /*<<< orphan*/  hasSubLinks; } ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * flatten_join_alias_vars_mutator (int /*<<< orphan*/ *,TYPE_1__*) ; 

Node *
flatten_join_alias_vars(Query *query, Node *node)
{
	flatten_join_alias_vars_context context;

	context.query = query;
	context.sublevels_up = 0;
	/* flag whether join aliases could possibly contain SubLinks */
	context.possible_sublink = query->hasSubLinks;
	/* if hasSubLinks is already true, no need to work hard */
	context.inserted_sublink = query->hasSubLinks;

	return flatten_join_alias_vars_mutator(node, &context);
}