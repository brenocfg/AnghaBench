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
struct TYPE_3__ {int flags; int /*<<< orphan*/ * varlist; } ;
typedef  TYPE_1__ pull_var_clause_context ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * NIL ; 
 int PVC_INCLUDE_AGGREGATES ; 
 int PVC_INCLUDE_PLACEHOLDERS ; 
 int PVC_INCLUDE_WINDOWFUNCS ; 
 int PVC_RECURSE_AGGREGATES ; 
 int PVC_RECURSE_PLACEHOLDERS ; 
 int PVC_RECURSE_WINDOWFUNCS ; 
 int /*<<< orphan*/  pull_var_clause_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

List *
pull_var_clause(Node *node, int flags)
{
	pull_var_clause_context context;

	/* Assert that caller has not specified inconsistent flags */
	Assert((flags & (PVC_INCLUDE_AGGREGATES | PVC_RECURSE_AGGREGATES))
		   != (PVC_INCLUDE_AGGREGATES | PVC_RECURSE_AGGREGATES));
	Assert((flags & (PVC_INCLUDE_WINDOWFUNCS | PVC_RECURSE_WINDOWFUNCS))
		   != (PVC_INCLUDE_WINDOWFUNCS | PVC_RECURSE_WINDOWFUNCS));
	Assert((flags & (PVC_INCLUDE_PLACEHOLDERS | PVC_RECURSE_PLACEHOLDERS))
		   != (PVC_INCLUDE_PLACEHOLDERS | PVC_RECURSE_PLACEHOLDERS));

	context.varlist = NIL;
	context.flags = flags;

	pull_var_clause_walker(node, &context);
	return context.varlist;
}