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
struct TYPE_7__ {int /*<<< orphan*/  ev_class; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_rewrite ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Anum_pg_rewrite_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RewriteOidIndexId ; 
 int /*<<< orphan*/  RewriteRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveRewriteRuleById(Oid ruleOid)
{
	Relation	RewriteRelation;
	ScanKeyData skey[1];
	SysScanDesc rcscan;
	Relation	event_relation;
	HeapTuple	tuple;
	Oid			eventRelationOid;

	/*
	 * Open the pg_rewrite relation.
	 */
	RewriteRelation = table_open(RewriteRelationId, RowExclusiveLock);

	/*
	 * Find the tuple for the target rule.
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_rewrite_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(ruleOid));

	rcscan = systable_beginscan(RewriteRelation, RewriteOidIndexId, true,
								NULL, 1, skey);

	tuple = systable_getnext(rcscan);

	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for rule %u", ruleOid);

	/*
	 * We had better grab AccessExclusiveLock to ensure that no queries are
	 * going on that might depend on this rule.  (Note: a weaker lock would
	 * suffice if it's not an ON SELECT rule.)
	 */
	eventRelationOid = ((Form_pg_rewrite) GETSTRUCT(tuple))->ev_class;
	event_relation = table_open(eventRelationOid, AccessExclusiveLock);

	/*
	 * Now delete the pg_rewrite tuple for the rule
	 */
	CatalogTupleDelete(RewriteRelation, &tuple->t_self);

	systable_endscan(rcscan);

	table_close(RewriteRelation, RowExclusiveLock);

	/*
	 * Issue shared-inval notice to force all backends (including me!) to
	 * update relcache entries with the new rule set.
	 */
	CacheInvalidateRelcache(event_relation);

	/* Close rel, but keep lock till commit... */
	table_close(event_relation, NoLock);
}