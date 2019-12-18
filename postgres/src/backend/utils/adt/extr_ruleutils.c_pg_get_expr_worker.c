#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * deparse_context_for (char const*,int /*<<< orphan*/ ) ; 
 char* deparse_expression_pretty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ stringToNode (char*) ; 
 int /*<<< orphan*/ * string_to_text (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static text *
pg_get_expr_worker(text *expr, Oid relid, const char *relname, int prettyFlags)
{
	Node	   *node;
	List	   *context;
	char	   *exprstr;
	char	   *str;

	/* Convert input TEXT object to C string */
	exprstr = text_to_cstring(expr);

	/* Convert expression to node tree */
	node = (Node *) stringToNode(exprstr);

	pfree(exprstr);

	/* Prepare deparse context if needed */
	if (OidIsValid(relid))
		context = deparse_context_for(relname, relid);
	else
		context = NIL;

	/* Deparse */
	str = deparse_expression_pretty(node, context, false, false,
									prettyFlags, 0);

	return string_to_text(str);
}