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
typedef  int /*<<< orphan*/  indexed_tlist ;
struct TYPE_3__ {int rtoffset; int /*<<< orphan*/  newvarno; int /*<<< orphan*/ * subplan_itlist; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ fix_upper_expr_context ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/ * fix_upper_expr_mutator (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Node *
fix_upper_expr(PlannerInfo *root,
			   Node *node,
			   indexed_tlist *subplan_itlist,
			   Index newvarno,
			   int rtoffset)
{
	fix_upper_expr_context context;

	context.root = root;
	context.subplan_itlist = subplan_itlist;
	context.newvarno = newvarno;
	context.rtoffset = rtoffset;
	return fix_upper_expr_mutator(node, &context);
}