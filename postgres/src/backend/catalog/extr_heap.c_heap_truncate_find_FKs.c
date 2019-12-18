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
struct TYPE_2__ {scalar_t__ contype; int /*<<< orphan*/  conrelid; int /*<<< orphan*/  confrelid; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 scalar_t__ CONSTRAINT_FOREIGN ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_deduplicate_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_oid_cmp ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

List *
heap_truncate_find_FKs(List *relationIds)
{
	List	   *result = NIL;
	Relation	fkeyRel;
	SysScanDesc fkeyScan;
	HeapTuple	tuple;

	/*
	 * Must scan pg_constraint.  Right now, it is a seqscan because there is
	 * no available index on confrelid.
	 */
	fkeyRel = table_open(ConstraintRelationId, AccessShareLock);

	fkeyScan = systable_beginscan(fkeyRel, InvalidOid, false,
								  NULL, 0, NULL);

	while (HeapTupleIsValid(tuple = systable_getnext(fkeyScan)))
	{
		Form_pg_constraint con = (Form_pg_constraint) GETSTRUCT(tuple);

		/* Not a foreign key */
		if (con->contype != CONSTRAINT_FOREIGN)
			continue;

		/* Not referencing one of our list of tables */
		if (!list_member_oid(relationIds, con->confrelid))
			continue;

		/* Add referencer to result, unless present in input list */
		if (!list_member_oid(relationIds, con->conrelid))
			result = lappend_oid(result, con->conrelid);
	}

	systable_endscan(fkeyScan);
	table_close(fkeyRel, AccessShareLock);

	/* Now sort and de-duplicate the result list */
	list_sort(result, list_oid_cmp);
	list_deduplicate_oid(result);

	return result;
}