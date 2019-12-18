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
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  get_rule_expr (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
get_special_variable(Node *node, deparse_context *context, void *private)
{
	StringInfo	buf = context->buf;

	/*
	 * Force parentheses because our caller probably assumed a Var is a simple
	 * expression.
	 */
	if (!IsA(node, Var))
		appendStringInfoChar(buf, '(');
	get_rule_expr(node, context, true);
	if (!IsA(node, Var))
		appendStringInfoChar(buf, ')');
}