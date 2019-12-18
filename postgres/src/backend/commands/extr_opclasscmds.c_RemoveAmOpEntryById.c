#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessMethodOperatorOidIndexId ; 
 int /*<<< orphan*/  AccessMethodOperatorRelationId ; 
 int /*<<< orphan*/  Anum_pg_amop_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveAmOpEntryById(Oid entryOid)
{
	Relation	rel;
	HeapTuple	tup;
	ScanKeyData skey[1];
	SysScanDesc scan;

	ScanKeyInit(&skey[0],
				Anum_pg_amop_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(entryOid));

	rel = table_open(AccessMethodOperatorRelationId, RowExclusiveLock);

	scan = systable_beginscan(rel, AccessMethodOperatorOidIndexId, true,
							  NULL, 1, skey);

	/* we expect exactly one match */
	tup = systable_getnext(scan);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "could not find tuple for amop entry %u", entryOid);

	CatalogTupleDelete(rel, &tup->t_self);

	systable_endscan(scan);
	table_close(rel, RowExclusiveLock);
}