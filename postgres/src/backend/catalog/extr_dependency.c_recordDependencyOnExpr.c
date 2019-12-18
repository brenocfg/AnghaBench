#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* addrs; int /*<<< orphan*/  rtables; } ;
typedef  TYPE_1__ find_expr_references_context ;
struct TYPE_7__ {int /*<<< orphan*/  numrefs; int /*<<< orphan*/  refs; } ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DependencyType ;

/* Variables and functions */
 int /*<<< orphan*/  eliminate_duplicate_dependencies (TYPE_2__*) ; 
 int /*<<< orphan*/  find_expr_references_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free_object_addresses (TYPE_2__*) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 TYPE_2__* new_object_addresses () ; 
 int /*<<< orphan*/  recordMultipleDependencies (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
recordDependencyOnExpr(const ObjectAddress *depender,
					   Node *expr, List *rtable,
					   DependencyType behavior)
{
	find_expr_references_context context;

	context.addrs = new_object_addresses();

	/* Set up interpretation for Vars at varlevelsup = 0 */
	context.rtables = list_make1(rtable);

	/* Scan the expression tree for referenceable objects */
	find_expr_references_walker(expr, &context);

	/* Remove any duplicates */
	eliminate_duplicate_dependencies(context.addrs);

	/* And record 'em */
	recordMultipleDependencies(depender,
							   context.addrs->refs, context.addrs->numrefs,
							   behavior);

	free_object_addresses(context.addrs);
}