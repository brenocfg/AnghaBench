#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ state; int /*<<< orphan*/  collation; } ;
typedef  TYPE_2__ foreign_loc_cxt ;
struct TYPE_12__ {int /*<<< orphan*/  relids; TYPE_4__* foreignrel; int /*<<< orphan*/ * root; } ;
typedef  TYPE_3__ foreign_glob_cxt ;
struct TYPE_14__ {TYPE_1__* outerrel; } ;
struct TYPE_13__ {int /*<<< orphan*/  relids; scalar_t__ fdw_private; } ;
struct TYPE_10__ {int /*<<< orphan*/  relids; } ;
typedef  TYPE_4__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_5__ PgFdwRelationInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ FDW_COLLATE_NONE ; 
 scalar_t__ FDW_COLLATE_UNSAFE ; 
 scalar_t__ IS_UPPER_REL (TYPE_4__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ contain_mutable_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  foreign_expr_walker (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 

bool
is_foreign_expr(PlannerInfo *root,
				RelOptInfo *baserel,
				Expr *expr)
{
	foreign_glob_cxt glob_cxt;
	foreign_loc_cxt loc_cxt;
	PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) (baserel->fdw_private);

	/*
	 * Check that the expression consists of nodes that are safe to execute
	 * remotely.
	 */
	glob_cxt.root = root;
	glob_cxt.foreignrel = baserel;

	/*
	 * For an upper relation, use relids from its underneath scan relation,
	 * because the upperrel's own relids currently aren't set to anything
	 * meaningful by the core code.  For other relation, use their own relids.
	 */
	if (IS_UPPER_REL(baserel))
		glob_cxt.relids = fpinfo->outerrel->relids;
	else
		glob_cxt.relids = baserel->relids;
	loc_cxt.collation = InvalidOid;
	loc_cxt.state = FDW_COLLATE_NONE;
	if (!foreign_expr_walker((Node *) expr, &glob_cxt, &loc_cxt))
		return false;

	/*
	 * If the expression has a valid collation that does not arise from a
	 * foreign var, the expression can not be sent over.
	 */
	if (loc_cxt.state == FDW_COLLATE_UNSAFE)
		return false;

	/*
	 * An expression which includes any mutable functions can't be sent over
	 * because its result is not stable.  For example, sending now() remote
	 * side could cause confusion from clock offsets.  Future versions might
	 * be able to make this choice with more granularity.  (We check this last
	 * because it requires a lot of expensive catalog lookups.)
	 */
	if (contain_mutable_functions((Node *) expr))
		return false;

	/* OK to evaluate on the remote server */
	return true;
}