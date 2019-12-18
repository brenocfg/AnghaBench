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
struct TYPE_5__ {int /*<<< orphan*/  srsublsn; int /*<<< orphan*/  srsubstate; int /*<<< orphan*/  srrelid; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsn; int /*<<< orphan*/  state; int /*<<< orphan*/  relid; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  TYPE_1__ SubscriptionRelState ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_subscription_rel ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_subscription_rel_srsubid ; 
 int /*<<< orphan*/  Anum_pg_subscription_rel_srsubstate ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CHARNE ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREL_STATE_READY ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubscriptionRelRelationId ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

List *
GetSubscriptionNotReadyRelations(Oid subid)
{
	List	   *res = NIL;
	Relation	rel;
	HeapTuple	tup;
	int			nkeys = 0;
	ScanKeyData skey[2];
	SysScanDesc scan;

	rel = table_open(SubscriptionRelRelationId, AccessShareLock);

	ScanKeyInit(&skey[nkeys++],
				Anum_pg_subscription_rel_srsubid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(subid));

	ScanKeyInit(&skey[nkeys++],
				Anum_pg_subscription_rel_srsubstate,
				BTEqualStrategyNumber, F_CHARNE,
				CharGetDatum(SUBREL_STATE_READY));

	scan = systable_beginscan(rel, InvalidOid, false,
							  NULL, nkeys, skey);

	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		Form_pg_subscription_rel subrel;
		SubscriptionRelState *relstate;

		subrel = (Form_pg_subscription_rel) GETSTRUCT(tup);

		relstate = (SubscriptionRelState *) palloc(sizeof(SubscriptionRelState));
		relstate->relid = subrel->srrelid;
		relstate->state = subrel->srsubstate;
		relstate->lsn = subrel->srsublsn;

		res = lappend(res, relstate);
	}

	/* Cleanup */
	systable_endscan(scan);
	table_close(rel, AccessShareLock);

	return res;
}