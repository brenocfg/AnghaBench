#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * root; TYPE_2__* foreignrel; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_expr_cxt ;
struct TYPE_15__ {int /*<<< orphan*/  attrs_used; } ;
struct TYPE_14__ {int /*<<< orphan*/  relid; } ;
struct TYPE_13__ {int /*<<< orphan*/  relid; scalar_t__ fdw_private; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_4__ PgFdwRelationInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ IS_JOIN_REL (TYPE_2__*) ; 
 scalar_t__ IS_UPPER_REL (TYPE_2__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  deparseExplicitTargetList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  deparseSubqueryTargetList (TYPE_1__*) ; 
 int /*<<< orphan*/  deparseTargetList (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 TYPE_3__* planner_rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deparseSelectSql(List *tlist, bool is_subquery, List **retrieved_attrs,
				 deparse_expr_cxt *context)
{
	StringInfo	buf = context->buf;
	RelOptInfo *foreignrel = context->foreignrel;
	PlannerInfo *root = context->root;
	PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) foreignrel->fdw_private;

	/*
	 * Construct SELECT list
	 */
	appendStringInfoString(buf, "SELECT ");

	if (is_subquery)
	{
		/*
		 * For a relation that is deparsed as a subquery, emit expressions
		 * specified in the relation's reltarget.  Note that since this is for
		 * the subquery, no need to care about *retrieved_attrs.
		 */
		deparseSubqueryTargetList(context);
	}
	else if (IS_JOIN_REL(foreignrel) || IS_UPPER_REL(foreignrel))
	{
		/*
		 * For a join or upper relation the input tlist gives the list of
		 * columns required to be fetched from the foreign server.
		 */
		deparseExplicitTargetList(tlist, false, retrieved_attrs, context);
	}
	else
	{
		/*
		 * For a base relation fpinfo->attrs_used gives the list of columns
		 * required to be fetched from the foreign server.
		 */
		RangeTblEntry *rte = planner_rt_fetch(foreignrel->relid, root);

		/*
		 * Core code already has some lock on each rel being planned, so we
		 * can use NoLock here.
		 */
		Relation	rel = table_open(rte->relid, NoLock);

		deparseTargetList(buf, rte, foreignrel->relid, rel, false,
						  fpinfo->attrs_used, false, retrieved_attrs);
		table_close(rel, NoLock);
	}
}