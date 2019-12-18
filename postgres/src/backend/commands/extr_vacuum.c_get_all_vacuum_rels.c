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
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_3__ {scalar_t__ relkind; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeVacuumRelation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vac_context ; 
 int /*<<< orphan*/  vacuum_is_relation_owner (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static List *
get_all_vacuum_rels(int options)
{
	List	   *vacrels = NIL;
	Relation	pgclass;
	TableScanDesc scan;
	HeapTuple	tuple;

	pgclass = table_open(RelationRelationId, AccessShareLock);

	scan = table_beginscan_catalog(pgclass, 0, NULL);

	while ((tuple = heap_getnext(scan, ForwardScanDirection)) != NULL)
	{
		Form_pg_class classForm = (Form_pg_class) GETSTRUCT(tuple);
		MemoryContext oldcontext;
		Oid			relid = classForm->oid;

		/* check permissions of relation */
		if (!vacuum_is_relation_owner(relid, classForm, options))
			continue;

		/*
		 * We include partitioned tables here; depending on which operation is
		 * to be performed, caller will decide whether to process or ignore
		 * them.
		 */
		if (classForm->relkind != RELKIND_RELATION &&
			classForm->relkind != RELKIND_MATVIEW &&
			classForm->relkind != RELKIND_PARTITIONED_TABLE)
			continue;

		/*
		 * Build VacuumRelation(s) specifying the table OIDs to be processed.
		 * We omit a RangeVar since it wouldn't be appropriate to complain
		 * about failure to open one of these relations later.
		 */
		oldcontext = MemoryContextSwitchTo(vac_context);
		vacrels = lappend(vacrels, makeVacuumRelation(NULL,
													  relid,
													  NIL));
		MemoryContextSwitchTo(oldcontext);
	}

	table_endscan(scan);
	table_close(pgclass, AccessShareLock);

	return vacrels;
}