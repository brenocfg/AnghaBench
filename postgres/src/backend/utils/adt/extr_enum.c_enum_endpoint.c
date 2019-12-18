#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_enum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_enum_enumtypid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  EnumRelationId ; 
 int /*<<< orphan*/  EnumTypIdSortOrderIndexId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_safe_enum_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan_ordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
enum_endpoint(Oid enumtypoid, ScanDirection direction)
{
	Relation	enum_rel;
	Relation	enum_idx;
	SysScanDesc enum_scan;
	HeapTuple	enum_tuple;
	ScanKeyData skey;
	Oid			minmax;

	/*
	 * Find the first/last enum member using pg_enum_typid_sortorder_index.
	 * Note we must not use the syscache.  See comments for RenumberEnumType
	 * in catalog/pg_enum.c for more info.
	 */
	ScanKeyInit(&skey,
				Anum_pg_enum_enumtypid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(enumtypoid));

	enum_rel = table_open(EnumRelationId, AccessShareLock);
	enum_idx = index_open(EnumTypIdSortOrderIndexId, AccessShareLock);
	enum_scan = systable_beginscan_ordered(enum_rel, enum_idx, NULL,
										   1, &skey);

	enum_tuple = systable_getnext_ordered(enum_scan, direction);
	if (HeapTupleIsValid(enum_tuple))
	{
		/* check it's safe to use in SQL */
		check_safe_enum_use(enum_tuple);
		minmax = ((Form_pg_enum) GETSTRUCT(enum_tuple))->oid;
	}
	else
	{
		/* should only happen with an empty enum */
		minmax = InvalidOid;
	}

	systable_endscan_ordered(enum_scan);
	index_close(enum_idx, AccessShareLock);
	table_close(enum_rel, AccessShareLock);

	return minmax;
}