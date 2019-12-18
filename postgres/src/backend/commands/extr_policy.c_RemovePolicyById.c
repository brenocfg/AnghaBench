#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  polrelid; } ;
struct TYPE_17__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_16__ {TYPE_1__* rd_rel; } ;
struct TYPE_15__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_policy ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Anum_pg_policy_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleDelete (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ IsSystemRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PolicyOidIndexId ; 
 int /*<<< orphan*/  PolicyRelationId ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allowSystemTableMods ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_3__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemovePolicyById(Oid policy_id)
{
	Relation	pg_policy_rel;
	SysScanDesc sscan;
	ScanKeyData skey[1];
	HeapTuple	tuple;
	Oid			relid;
	Relation	rel;

	pg_policy_rel = table_open(PolicyRelationId, RowExclusiveLock);

	/*
	 * Find the policy to delete.
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_policy_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(policy_id));

	sscan = systable_beginscan(pg_policy_rel, PolicyOidIndexId, true,
							   NULL, 1, skey);

	tuple = systable_getnext(sscan);

	/* If the policy exists, then remove it, otherwise raise an error. */
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for policy %u", policy_id);

	/*
	 * Open and exclusive-lock the relation the policy belongs to.  (We need
	 * exclusive lock to lock out queries that might otherwise depend on the
	 * set of policies the rel has; furthermore we've got to hold the lock
	 * till commit.)
	 */
	relid = ((Form_pg_policy) GETSTRUCT(tuple))->polrelid;

	rel = table_open(relid, AccessExclusiveLock);
	if (rel->rd_rel->relkind != RELKIND_RELATION &&
		rel->rd_rel->relkind != RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not a table",
						RelationGetRelationName(rel))));

	if (!allowSystemTableMods && IsSystemRelation(rel))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied: \"%s\" is a system catalog",
						RelationGetRelationName(rel))));

	CatalogTupleDelete(pg_policy_rel, &tuple->t_self);

	systable_endscan(sscan);

	/*
	 * Note that, unlike some of the other flags in pg_class, relrowsecurity
	 * is not just an indication of if policies exist.  When relrowsecurity is
	 * set by a user, then all access to the relation must be through a
	 * policy.  If no policy is defined for the relation then a default-deny
	 * policy is created and all records are filtered (except for queries from
	 * the owner).
	 */
	CacheInvalidateRelcache(rel);

	table_close(rel, NoLock);

	/* Clean up */
	table_close(pg_policy_rel, RowExclusiveLock);
}