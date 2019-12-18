#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_5__ {int /*<<< orphan*/  subname; int /*<<< orphan*/  subenabled; int /*<<< orphan*/  subowner; int /*<<< orphan*/  subdbid; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  enabled; int /*<<< orphan*/  owner; int /*<<< orphan*/  dbid; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ Subscription ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_subscription ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  SubscriptionRelationId ; 
 int /*<<< orphan*/  heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
get_subscription_list(void)
{
	List	   *res = NIL;
	Relation	rel;
	TableScanDesc scan;
	HeapTuple	tup;
	MemoryContext resultcxt;

	/* This is the context that we will allocate our output data in */
	resultcxt = CurrentMemoryContext;

	/*
	 * Start a transaction so we can access pg_database, and get a snapshot.
	 * We don't have a use for the snapshot itself, but we're interested in
	 * the secondary effect that it sets RecentGlobalXmin.  (This is critical
	 * for anything that reads heap pages, because HOT may decide to prune
	 * them even if the process doesn't attempt to modify any tuples.)
	 */
	StartTransactionCommand();
	(void) GetTransactionSnapshot();

	rel = table_open(SubscriptionRelationId, AccessShareLock);
	scan = table_beginscan_catalog(rel, 0, NULL);

	while (HeapTupleIsValid(tup = heap_getnext(scan, ForwardScanDirection)))
	{
		Form_pg_subscription subform = (Form_pg_subscription) GETSTRUCT(tup);
		Subscription *sub;
		MemoryContext oldcxt;

		/*
		 * Allocate our results in the caller's context, not the
		 * transaction's. We do this inside the loop, and restore the original
		 * context at the end, so that leaky things like heap_getnext() are
		 * not called in a potentially long-lived context.
		 */
		oldcxt = MemoryContextSwitchTo(resultcxt);

		sub = (Subscription *) palloc0(sizeof(Subscription));
		sub->oid = subform->oid;
		sub->dbid = subform->subdbid;
		sub->owner = subform->subowner;
		sub->enabled = subform->subenabled;
		sub->name = pstrdup(NameStr(subform->subname));
		/* We don't fill fields we are not interested in. */

		res = lappend(res, sub);
		MemoryContextSwitchTo(oldcxt);
	}

	table_endscan(scan);
	table_close(rel, AccessShareLock);

	CommitTransactionCommand();

	return res;
}