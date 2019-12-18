#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  prettyFlags; } ;
typedef  TYPE_1__ deparse_context ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ PRETTY_PAREN (TYPE_1__*) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  get_rule_expr (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  isSimpleNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_rule_expr_paren(Node *node, deparse_context *context,
					bool showimplicit, Node *parentNode)
{
	bool		need_paren;

	need_paren = PRETTY_PAREN(context) &&
		!isSimpleNode(node, parentNode, context->prettyFlags);

	if (need_paren)
		appendStringInfoChar(context->buf, '(');

	get_rule_expr(node, context, showimplicit);

	if (need_paren)
		appendStringInfoChar(context->buf, ')');
}