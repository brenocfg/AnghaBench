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
struct TYPE_3__ {int rtoffset; int /*<<< orphan*/  acceptable_rel; int /*<<< orphan*/ * inner_itlist; int /*<<< orphan*/ * outer_itlist; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ fix_join_expr_context ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 scalar_t__ fix_join_expr_mutator (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static List *
fix_join_expr(PlannerInfo *root,
			  List *clauses,
			  indexed_tlist *outer_itlist,
			  indexed_tlist *inner_itlist,
			  Index acceptable_rel,
			  int rtoffset)
{
	fix_join_expr_context context;

	context.root = root;
	context.outer_itlist = outer_itlist;
	context.inner_itlist = inner_itlist;
	context.acceptable_rel = acceptable_rel;
	context.rtoffset = rtoffset;
	return (List *) fix_join_expr_mutator((Node *) clauses, &context);
}