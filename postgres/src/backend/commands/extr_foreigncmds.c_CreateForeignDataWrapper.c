#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_15__ {int /*<<< orphan*/  options; int /*<<< orphan*/  func_options; int /*<<< orphan*/  fdwname; } ;
struct TYPE_14__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
struct TYPE_13__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;
typedef  TYPE_3__ CreateFdwStmt ;

/* Variables and functions */
 int Anum_pg_foreign_data_wrapper_fdwacl ; 
 int Anum_pg_foreign_data_wrapper_fdwhandler ; 
 int Anum_pg_foreign_data_wrapper_fdwname ; 
 int Anum_pg_foreign_data_wrapper_fdwoptions ; 
 int Anum_pg_foreign_data_wrapper_fdwowner ; 
 int Anum_pg_foreign_data_wrapper_fdwvalidator ; 
 int Anum_pg_foreign_data_wrapper_oid ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  DatumGetPointer (int) ; 
 int DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ForeignDataWrapperOidIndexId ; 
 void* ForeignDataWrapperRelationId ; 
 int /*<<< orphan*/ * GetForeignDataWrapperByName (int /*<<< orphan*/ ,int) ; 
 void* GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (void*,void*,int /*<<< orphan*/ ) ; 
 int Natts_pg_foreign_data_wrapper ; 
 int ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/ ) ; 
 void* ProcedureRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namein ; 
 int /*<<< orphan*/  parse_func_options (int /*<<< orphan*/ ,int*,void**,int*,void**) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_2__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (void*,void*,void*) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (void*,int /*<<< orphan*/ ) ; 
 int transformGenericOptions (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

ObjectAddress
CreateForeignDataWrapper(CreateFdwStmt *stmt)
{
	Relation	rel;
	Datum		values[Natts_pg_foreign_data_wrapper];
	bool		nulls[Natts_pg_foreign_data_wrapper];
	HeapTuple	tuple;
	Oid			fdwId;
	bool		handler_given;
	bool		validator_given;
	Oid			fdwhandler;
	Oid			fdwvalidator;
	Datum		fdwoptions;
	Oid			ownerId;
	ObjectAddress myself;
	ObjectAddress referenced;

	rel = table_open(ForeignDataWrapperRelationId, RowExclusiveLock);

	/* Must be super user */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to create foreign-data wrapper \"%s\"",
						stmt->fdwname),
				 errhint("Must be superuser to create a foreign-data wrapper.")));

	/* For now the owner cannot be specified on create. Use effective user ID. */
	ownerId = GetUserId();

	/*
	 * Check that there is no other foreign-data wrapper by this name.
	 */
	if (GetForeignDataWrapperByName(stmt->fdwname, true) != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("foreign-data wrapper \"%s\" already exists",
						stmt->fdwname)));

	/*
	 * Insert tuple into pg_foreign_data_wrapper.
	 */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	fdwId = GetNewOidWithIndex(rel, ForeignDataWrapperOidIndexId,
							   Anum_pg_foreign_data_wrapper_oid);
	values[Anum_pg_foreign_data_wrapper_oid - 1] = ObjectIdGetDatum(fdwId);
	values[Anum_pg_foreign_data_wrapper_fdwname - 1] =
		DirectFunctionCall1(namein, CStringGetDatum(stmt->fdwname));
	values[Anum_pg_foreign_data_wrapper_fdwowner - 1] = ObjectIdGetDatum(ownerId);

	/* Lookup handler and validator functions, if given */
	parse_func_options(stmt->func_options,
					   &handler_given, &fdwhandler,
					   &validator_given, &fdwvalidator);

	values[Anum_pg_foreign_data_wrapper_fdwhandler - 1] = ObjectIdGetDatum(fdwhandler);
	values[Anum_pg_foreign_data_wrapper_fdwvalidator - 1] = ObjectIdGetDatum(fdwvalidator);

	nulls[Anum_pg_foreign_data_wrapper_fdwacl - 1] = true;

	fdwoptions = transformGenericOptions(ForeignDataWrapperRelationId,
										 PointerGetDatum(NULL),
										 stmt->options,
										 fdwvalidator);

	if (PointerIsValid(DatumGetPointer(fdwoptions)))
		values[Anum_pg_foreign_data_wrapper_fdwoptions - 1] = fdwoptions;
	else
		nulls[Anum_pg_foreign_data_wrapper_fdwoptions - 1] = true;

	tuple = heap_form_tuple(rel->rd_att, values, nulls);

	CatalogTupleInsert(rel, tuple);

	heap_freetuple(tuple);

	/* record dependencies */
	myself.classId = ForeignDataWrapperRelationId;
	myself.objectId = fdwId;
	myself.objectSubId = 0;

	if (OidIsValid(fdwhandler))
	{
		referenced.classId = ProcedureRelationId;
		referenced.objectId = fdwhandler;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	if (OidIsValid(fdwvalidator))
	{
		referenced.classId = ProcedureRelationId;
		referenced.objectId = fdwvalidator;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	recordDependencyOnOwner(ForeignDataWrapperRelationId, fdwId, ownerId);

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, false);

	/* Post creation hook for new foreign data wrapper */
	InvokeObjectPostCreateHook(ForeignDataWrapperRelationId, fdwId, 0);

	table_close(rel, RowExclusiveLock);

	return myself;
}