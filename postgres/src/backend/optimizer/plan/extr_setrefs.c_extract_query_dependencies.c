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
typedef  int /*<<< orphan*/  root ;
typedef  int /*<<< orphan*/  glob ;
struct TYPE_5__ {int dependsOnRole; int /*<<< orphan*/ * invalItems; int /*<<< orphan*/ * relationOids; struct TYPE_5__* glob; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  TYPE_1__ PlannerGlobal ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* NIL ; 
 int /*<<< orphan*/  T_PlannerGlobal ; 
 int /*<<< orphan*/  T_PlannerInfo ; 
 int /*<<< orphan*/  extract_query_dependencies_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
extract_query_dependencies(Node *query,
						   List **relationOids,
						   List **invalItems,
						   bool *hasRowSecurity)
{
	PlannerGlobal glob;
	PlannerInfo root;

	/* Make up dummy planner state so we can use this module's machinery */
	MemSet(&glob, 0, sizeof(glob));
	glob.type = T_PlannerGlobal;
	glob.relationOids = NIL;
	glob.invalItems = NIL;
	/* Hack: we use glob.dependsOnRole to collect hasRowSecurity flags */
	glob.dependsOnRole = false;

	MemSet(&root, 0, sizeof(root));
	root.type = T_PlannerInfo;
	root.glob = &glob;

	(void) extract_query_dependencies_walker(query, &root);

	*relationOids = glob.relationOids;
	*invalItems = glob.invalItems;
	*hasRowSecurity = glob.dependsOnRole;
}