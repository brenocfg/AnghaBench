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
struct TYPE_7__ {scalar_t__ inhparent; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_inherits ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_inherits_inhrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/  InheritsRelidSeqnoIndexId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
DeleteInheritsTuple(Oid inhrelid, Oid inhparent)
{
	bool		found = false;
	Relation	catalogRelation;
	ScanKeyData key;
	SysScanDesc scan;
	HeapTuple	inheritsTuple;

	/*
	 * Find pg_inherits entries by inhrelid.
	 */
	catalogRelation = table_open(InheritsRelationId, RowExclusiveLock);
	ScanKeyInit(&key,
				Anum_pg_inherits_inhrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(inhrelid));
	scan = systable_beginscan(catalogRelation, InheritsRelidSeqnoIndexId,
							  true, NULL, 1, &key);

	while (HeapTupleIsValid(inheritsTuple = systable_getnext(scan)))
	{
		Oid			parent;

		/* Compare inhparent if it was given, and do the actual deletion. */
		parent = ((Form_pg_inherits) GETSTRUCT(inheritsTuple))->inhparent;
		if (!OidIsValid(inhparent) || parent == inhparent)
		{
			CatalogTupleDelete(catalogRelation, &inheritsTuple->t_self);
			found = true;
		}
	}

	/* Done */
	systable_endscan(scan);
	table_close(catalogRelation, RowExclusiveLock);

	return found;
}