#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buf; TYPE_3__* root; } ;
typedef  TYPE_2__ deparse_expr_cxt ;
struct TYPE_8__ {TYPE_1__* parse; } ;
struct TYPE_6__ {scalar_t__ limitOffset; scalar_t__ limitCount; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  deparseExpr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  reset_transmission_modes (int) ; 
 int set_transmission_modes () ; 

__attribute__((used)) static void
appendLimitClause(deparse_expr_cxt *context)
{
	PlannerInfo *root = context->root;
	StringInfo	buf = context->buf;
	int			nestlevel;

	/* Make sure any constants in the exprs are printed portably */
	nestlevel = set_transmission_modes();

	if (root->parse->limitCount)
	{
		appendStringInfoString(buf, " LIMIT ");
		deparseExpr((Expr *) root->parse->limitCount, context);
	}
	if (root->parse->limitOffset)
	{
		appendStringInfoString(buf, " OFFSET ");
		deparseExpr((Expr *) root->parse->limitOffset, context);
	}

	reset_transmission_modes(nestlevel);
}