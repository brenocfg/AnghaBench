#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rtoffset; TYPE_3__* root; } ;
typedef  TYPE_2__ fix_scan_expr_context ;
struct TYPE_9__ {scalar_t__ multiexpr_params; scalar_t__ minmax_aggs; TYPE_1__* glob; } ;
struct TYPE_7__ {scalar_t__ lastPHId; } ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ NIL ; 
 int /*<<< orphan*/ * fix_scan_expr_mutator (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fix_scan_expr_walker (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static Node *
fix_scan_expr(PlannerInfo *root, Node *node, int rtoffset)
{
	fix_scan_expr_context context;

	context.root = root;
	context.rtoffset = rtoffset;

	if (rtoffset != 0 ||
		root->multiexpr_params != NIL ||
		root->glob->lastPHId != 0 ||
		root->minmax_aggs != NIL)
	{
		return fix_scan_expr_mutator(node, &context);
	}
	else
	{
		/*
		 * If rtoffset == 0, we don't need to change any Vars, and if there
		 * are no MULTIEXPR subqueries then we don't need to replace
		 * PARAM_MULTIEXPR Params, and if there are no placeholders anywhere
		 * we won't need to remove them, and if there are no minmax Aggrefs we
		 * won't need to replace them.  Then it's OK to just scribble on the
		 * input node tree instead of copying (since the only change, filling
		 * in any unset opfuncid fields, is harmless).  This saves just enough
		 * cycles to be noticeable on trivial queries.
		 */
		(void) fix_scan_expr_walker(node, &context);
		return node;
	}
}