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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_12__ {scalar_t__ objectSubId; void* objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_11__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessMethodRelationId ; 
 int Anum_pg_opfamily_oid ; 
 int Anum_pg_opfamily_opfmethod ; 
 int Anum_pg_opfamily_opfname ; 
 int Anum_pg_opfamily_opfnamespace ; 
 int Anum_pg_opfamily_opfowner ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 void* GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int Natts_pg_opfamily ; 
 int /*<<< orphan*/  OPFAMILYAMNAMENSP ; 
 int ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  OperatorFamilyRelationId ; 
 int /*<<< orphan*/  OpfamilyOidIndexId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ SearchSysCacheExists3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_2__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
CreateOpFamily(const char *amname, const char *opfname, Oid namespaceoid, Oid amoid)
{
	Oid			opfamilyoid;
	Relation	rel;
	HeapTuple	tup;
	Datum		values[Natts_pg_opfamily];
	bool		nulls[Natts_pg_opfamily];
	NameData	opfName;
	ObjectAddress myself,
				referenced;

	rel = table_open(OperatorFamilyRelationId, RowExclusiveLock);

	/*
	 * Make sure there is no existing opfamily of this name (this is just to
	 * give a more friendly error message than "duplicate key").
	 */
	if (SearchSysCacheExists3(OPFAMILYAMNAMENSP,
							  ObjectIdGetDatum(amoid),
							  CStringGetDatum(opfname),
							  ObjectIdGetDatum(namespaceoid)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("operator family \"%s\" for access method \"%s\" already exists",
						opfname, amname)));

	/*
	 * Okay, let's create the pg_opfamily entry.
	 */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	opfamilyoid = GetNewOidWithIndex(rel, OpfamilyOidIndexId,
									 Anum_pg_opfamily_oid);
	values[Anum_pg_opfamily_oid - 1] = ObjectIdGetDatum(opfamilyoid);
	values[Anum_pg_opfamily_opfmethod - 1] = ObjectIdGetDatum(amoid);
	namestrcpy(&opfName, opfname);
	values[Anum_pg_opfamily_opfname - 1] = NameGetDatum(&opfName);
	values[Anum_pg_opfamily_opfnamespace - 1] = ObjectIdGetDatum(namespaceoid);
	values[Anum_pg_opfamily_opfowner - 1] = ObjectIdGetDatum(GetUserId());

	tup = heap_form_tuple(rel->rd_att, values, nulls);

	CatalogTupleInsert(rel, tup);

	heap_freetuple(tup);

	/*
	 * Create dependencies for the opfamily proper.
	 */
	myself.classId = OperatorFamilyRelationId;
	myself.objectId = opfamilyoid;
	myself.objectSubId = 0;

	/* dependency on access method */
	referenced.classId = AccessMethodRelationId;
	referenced.objectId = amoid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_AUTO);

	/* dependency on namespace */
	referenced.classId = NamespaceRelationId;
	referenced.objectId = namespaceoid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* dependency on owner */
	recordDependencyOnOwner(OperatorFamilyRelationId, opfamilyoid, GetUserId());

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, false);

	/* Post creation hook for new operator family */
	InvokeObjectPostCreateHook(OperatorFamilyRelationId, opfamilyoid, 0);

	table_close(rel, RowExclusiveLock);

	return myself;
}