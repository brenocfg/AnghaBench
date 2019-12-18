#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_12__ {int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_11__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ DependencyType ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/ * CatalogIndexState ;

/* Variables and functions */
 int Anum_pg_depend_classid ; 
 int Anum_pg_depend_deptype ; 
 int Anum_pg_depend_objid ; 
 int Anum_pg_depend_objsubid ; 
 int Anum_pg_depend_refclassid ; 
 int Anum_pg_depend_refobjid ; 
 int Anum_pg_depend_refobjsubid ; 
 int /*<<< orphan*/  CatalogCloseIndexes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CatalogOpenIndexes (TYPE_1__*) ; 
 int /*<<< orphan*/  CatalogTupleInsertWithInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CharGetDatum (char) ; 
 int /*<<< orphan*/  DependRelationId ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int Natts_pg_depend ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isObjectPinned (TYPE_2__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
recordMultipleDependencies(const ObjectAddress *depender,
						   const ObjectAddress *referenced,
						   int nreferenced,
						   DependencyType behavior)
{
	Relation	dependDesc;
	CatalogIndexState indstate;
	HeapTuple	tup;
	int			i;
	bool		nulls[Natts_pg_depend];
	Datum		values[Natts_pg_depend];

	if (nreferenced <= 0)
		return;					/* nothing to do */

	/*
	 * During bootstrap, do nothing since pg_depend may not exist yet. initdb
	 * will fill in appropriate pg_depend entries after bootstrap.
	 */
	if (IsBootstrapProcessingMode())
		return;

	dependDesc = table_open(DependRelationId, RowExclusiveLock);

	/* Don't open indexes unless we need to make an update */
	indstate = NULL;

	memset(nulls, false, sizeof(nulls));

	for (i = 0; i < nreferenced; i++, referenced++)
	{
		/*
		 * If the referenced object is pinned by the system, there's no real
		 * need to record dependencies on it.  This saves lots of space in
		 * pg_depend, so it's worth the time taken to check.
		 */
		if (!isObjectPinned(referenced, dependDesc))
		{
			/*
			 * Record the Dependency.  Note we don't bother to check for
			 * duplicate dependencies; there's no harm in them.
			 */
			values[Anum_pg_depend_classid - 1] = ObjectIdGetDatum(depender->classId);
			values[Anum_pg_depend_objid - 1] = ObjectIdGetDatum(depender->objectId);
			values[Anum_pg_depend_objsubid - 1] = Int32GetDatum(depender->objectSubId);

			values[Anum_pg_depend_refclassid - 1] = ObjectIdGetDatum(referenced->classId);
			values[Anum_pg_depend_refobjid - 1] = ObjectIdGetDatum(referenced->objectId);
			values[Anum_pg_depend_refobjsubid - 1] = Int32GetDatum(referenced->objectSubId);

			values[Anum_pg_depend_deptype - 1] = CharGetDatum((char) behavior);

			tup = heap_form_tuple(dependDesc->rd_att, values, nulls);

			/* fetch index info only when we know we need it */
			if (indstate == NULL)
				indstate = CatalogOpenIndexes(dependDesc);

			CatalogTupleInsertWithInfo(dependDesc, tup, indstate);

			heap_freetuple(tup);
		}
	}

	if (indstate != NULL)
		CatalogCloseIndexes(indstate);

	table_close(dependDesc, RowExclusiveLock);
}