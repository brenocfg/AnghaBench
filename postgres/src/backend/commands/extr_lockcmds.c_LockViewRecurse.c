#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nowait; int /*<<< orphan*/  ancestor_views; int /*<<< orphan*/  viewoid; int /*<<< orphan*/  viewowner; int /*<<< orphan*/  lockmode; } ;
struct TYPE_9__ {TYPE_1__* rd_rel; } ;
struct TYPE_8__ {int /*<<< orphan*/  relowner; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ LockViewRecurse_context ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  LockViewRecurse_walker (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * get_view_query (TYPE_2__*) ; 
 int /*<<< orphan*/  lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_delete_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LockViewRecurse(Oid reloid, LOCKMODE lockmode, bool nowait, List *ancestor_views)
{
	LockViewRecurse_context context;

	Relation	view;
	Query	   *viewquery;

	view = table_open(reloid, NoLock);
	viewquery = get_view_query(view);

	context.lockmode = lockmode;
	context.nowait = nowait;
	context.viewowner = view->rd_rel->relowner;
	context.viewoid = reloid;
	context.ancestor_views = lappend_oid(ancestor_views, reloid);

	LockViewRecurse_walker((Node *) viewquery, &context);

	(void) list_delete_last(context.ancestor_views);

	table_close(view, NoLock);
}