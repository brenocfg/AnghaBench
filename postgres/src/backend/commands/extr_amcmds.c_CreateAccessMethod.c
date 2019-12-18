#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_9__ {int /*<<< orphan*/  amtype; int /*<<< orphan*/  amname; int /*<<< orphan*/  handler_name; } ;
struct TYPE_8__ {scalar_t__ objectSubId; void* objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;
typedef  TYPE_2__ CreateAmStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AMNAME ; 
 int /*<<< orphan*/  AccessMethodRelationId ; 
 int /*<<< orphan*/  AmOidIndexId ; 
 int Anum_pg_am_amhandler ; 
 int Anum_pg_am_amname ; 
 int Anum_pg_am_amtype ; 
 int Anum_pg_am_oid ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 void* GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* GetSysCacheOid1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int Natts_pg_am ; 
 int ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 void* lookup_am_handler_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namein ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_1__*,int) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
CreateAccessMethod(CreateAmStmt *stmt)
{
	Relation	rel;
	ObjectAddress myself;
	ObjectAddress referenced;
	Oid			amoid;
	Oid			amhandler;
	bool		nulls[Natts_pg_am];
	Datum		values[Natts_pg_am];
	HeapTuple	tup;

	rel = table_open(AccessMethodRelationId, RowExclusiveLock);

	/* Must be super user */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to create access method \"%s\"",
						stmt->amname),
				 errhint("Must be superuser to create an access method.")));

	/* Check if name is used */
	amoid = GetSysCacheOid1(AMNAME, Anum_pg_am_oid,
							CStringGetDatum(stmt->amname));
	if (OidIsValid(amoid))
	{
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("access method \"%s\" already exists",
						stmt->amname)));
	}

	/*
	 * Get the handler function oid, verifying the AM type while at it.
	 */
	amhandler = lookup_am_handler_func(stmt->handler_name, stmt->amtype);

	/*
	 * Insert tuple into pg_am.
	 */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	amoid = GetNewOidWithIndex(rel, AmOidIndexId, Anum_pg_am_oid);
	values[Anum_pg_am_oid - 1] = ObjectIdGetDatum(amoid);
	values[Anum_pg_am_amname - 1] =
		DirectFunctionCall1(namein, CStringGetDatum(stmt->amname));
	values[Anum_pg_am_amhandler - 1] = ObjectIdGetDatum(amhandler);
	values[Anum_pg_am_amtype - 1] = CharGetDatum(stmt->amtype);

	tup = heap_form_tuple(RelationGetDescr(rel), values, nulls);

	CatalogTupleInsert(rel, tup);
	heap_freetuple(tup);

	myself.classId = AccessMethodRelationId;
	myself.objectId = amoid;
	myself.objectSubId = 0;

	/* Record dependency on handler function */
	referenced.classId = ProcedureRelationId;
	referenced.objectId = amhandler;
	referenced.objectSubId = 0;

	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	recordDependencyOnCurrentExtension(&myself, false);

	table_close(rel, RowExclusiveLock);

	return myself;
}