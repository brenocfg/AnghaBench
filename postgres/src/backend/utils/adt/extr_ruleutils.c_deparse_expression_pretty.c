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
struct TYPE_5__ {int varprefix; int prettyFlags; int indentLevel; int /*<<< orphan*/  special_exprkind; int /*<<< orphan*/  wrapColumn; void* windowTList; void* windowClause; int /*<<< orphan*/ * namespaces; TYPE_2__* buf; } ;
typedef  TYPE_1__ deparse_context ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_KIND_NONE ; 
 void* NIL ; 
 int /*<<< orphan*/  WRAP_COLUMN_DEFAULT ; 
 int /*<<< orphan*/  get_rule_expr (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 

__attribute__((used)) static char *
deparse_expression_pretty(Node *expr, List *dpcontext,
						  bool forceprefix, bool showimplicit,
						  int prettyFlags, int startIndent)
{
	StringInfoData buf;
	deparse_context context;

	initStringInfo(&buf);
	context.buf = &buf;
	context.namespaces = dpcontext;
	context.windowClause = NIL;
	context.windowTList = NIL;
	context.varprefix = forceprefix;
	context.prettyFlags = prettyFlags;
	context.wrapColumn = WRAP_COLUMN_DEFAULT;
	context.indentLevel = startIndent;
	context.special_exprkind = EXPR_KIND_NONE;

	get_rule_expr(expr, &context, showimplicit);

	return buf.data;
}