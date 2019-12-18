#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_context ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprTypmod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_with_typemod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rule_expr (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ looks_like_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_rule_expr_funccall(Node *node, deparse_context *context,
					   bool showimplicit)
{
	if (looks_like_function(node))
		get_rule_expr(node, context, showimplicit);
	else
	{
		StringInfo	buf = context->buf;

		appendStringInfoString(buf, "CAST(");
		/* no point in showing any top-level implicit cast */
		get_rule_expr(node, context, false);
		appendStringInfo(buf, " AS %s)",
						 format_type_with_typemod(exprType(node),
												  exprTypmod(node)));
	}
}