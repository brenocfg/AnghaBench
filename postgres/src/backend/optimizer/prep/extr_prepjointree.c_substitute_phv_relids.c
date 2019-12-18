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
struct TYPE_2__ {int varno; int /*<<< orphan*/  subrelids; scalar_t__ sublevels_up; } ;
typedef  TYPE_1__ substitute_phv_relids_context ;
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  query_or_expression_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  substitute_phv_relids_walker ; 

__attribute__((used)) static void
substitute_phv_relids(Node *node, int varno, Relids subrelids)
{
	substitute_phv_relids_context context;

	context.varno = varno;
	context.sublevels_up = 0;
	context.subrelids = subrelids;

	/*
	 * Must be prepared to start with a Query or a bare expression tree.
	 */
	query_or_expression_tree_walker(node,
									substitute_phv_relids_walker,
									(void *) &context,
									0);
}