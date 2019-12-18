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
struct TYPE_2__ {scalar_t__ relkind; int relnatts; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  RELOID ; 
 scalar_t__ RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  recordExtensionInitPrivWorker (scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 

void
removeExtObjInitPriv(Oid objoid, Oid classoid)
{
	/*
	 * If this is a relation then we need to see if there are any sub-objects
	 * (eg: columns) for it and, if so, be sure to call
	 * recordExtensionInitPrivWorker() for each one.
	 */
	if (classoid == RelationRelationId)
	{
		Form_pg_class pg_class_tuple;
		HeapTuple	tuple;

		tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(objoid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for relation %u", objoid);
		pg_class_tuple = (Form_pg_class) GETSTRUCT(tuple);

		/* Indexes don't have permissions */
		if (pg_class_tuple->relkind == RELKIND_INDEX ||
			pg_class_tuple->relkind == RELKIND_PARTITIONED_INDEX)
			return;

		/* Composite types don't have permissions either */
		if (pg_class_tuple->relkind == RELKIND_COMPOSITE_TYPE)
			return;

		/*
		 * If this isn't a sequence, index, or composite type then it's
		 * possibly going to have columns associated with it that might have
		 * ACLs.
		 */
		if (pg_class_tuple->relkind != RELKIND_SEQUENCE)
		{
			AttrNumber	curr_att;
			AttrNumber	nattrs = pg_class_tuple->relnatts;

			for (curr_att = 1; curr_att <= nattrs; curr_att++)
			{
				HeapTuple	attTuple;

				attTuple = SearchSysCache2(ATTNUM,
										   ObjectIdGetDatum(objoid),
										   Int16GetDatum(curr_att));

				if (!HeapTupleIsValid(attTuple))
					continue;

				/* when removing, remove all entries, even dropped columns */

				recordExtensionInitPrivWorker(objoid, classoid, curr_att, NULL);

				ReleaseSysCache(attTuple);
			}
		}

		ReleaseSysCache(tuple);
	}

	/* Remove the record, if any, for the top-level object */
	recordExtensionInitPrivWorker(objoid, classoid, 0, NULL);
}