#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_shdescription_classoid ; 
 int /*<<< orphan*/  Anum_pg_shdescription_objoid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SharedDescriptionObjIndexId ; 
 int /*<<< orphan*/  SharedDescriptionRelationId ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
DeleteSharedComments(Oid oid, Oid classoid)
{
	Relation	shdescription;
	ScanKeyData skey[2];
	SysScanDesc sd;
	HeapTuple	oldtuple;

	/* Use the index to search for all matching old tuples */

	ScanKeyInit(&skey[0],
				Anum_pg_shdescription_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(oid));
	ScanKeyInit(&skey[1],
				Anum_pg_shdescription_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classoid));

	shdescription = table_open(SharedDescriptionRelationId, RowExclusiveLock);

	sd = systable_beginscan(shdescription, SharedDescriptionObjIndexId, true,
							NULL, 2, skey);

	while ((oldtuple = systable_getnext(sd)) != NULL)
		CatalogTupleDelete(shdescription, &oldtuple->t_self);

	/* Done */

	systable_endscan(sd);
	table_close(shdescription, RowExclusiveLock);
}