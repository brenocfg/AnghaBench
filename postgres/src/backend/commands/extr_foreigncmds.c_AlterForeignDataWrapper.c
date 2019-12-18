#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_val ;
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  repl_null ;
struct TYPE_21__ {int /*<<< orphan*/  options; int /*<<< orphan*/  func_options; int /*<<< orphan*/  fdwname; } ;
struct TYPE_20__ {void* fdwvalidator; void* oid; } ;
struct TYPE_19__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_18__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_foreign_data_wrapper ;
typedef  int Datum ;
typedef  TYPE_4__ AlterFdwStmt ;

/* Variables and functions */
 int Anum_pg_foreign_data_wrapper_fdwhandler ; 
 int Anum_pg_foreign_data_wrapper_fdwoptions ; 
 int Anum_pg_foreign_data_wrapper_fdwvalidator ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  DatumGetPointer (int) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOREIGNDATAWRAPPERNAME ; 
 int /*<<< orphan*/  FOREIGNDATAWRAPPEROID ; 
 int /*<<< orphan*/  ForeignDataWrapperRelationId ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int Natts_pg_foreign_data_wrapper ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,void*) ; 
 int ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/ ) ; 
 void* ProcedureRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  deleteDependencyRecordsForClass (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  parse_func_options (int /*<<< orphan*/ ,int*,void**,int*,void**) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int transformGenericOptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

ObjectAddress
AlterForeignDataWrapper(AlterFdwStmt *stmt)
{
	Relation	rel;
	HeapTuple	tp;
	Form_pg_foreign_data_wrapper fdwForm;
	Datum		repl_val[Natts_pg_foreign_data_wrapper];
	bool		repl_null[Natts_pg_foreign_data_wrapper];
	bool		repl_repl[Natts_pg_foreign_data_wrapper];
	Oid			fdwId;
	bool		isnull;
	Datum		datum;
	bool		handler_given;
	bool		validator_given;
	Oid			fdwhandler;
	Oid			fdwvalidator;
	ObjectAddress myself;

	rel = table_open(ForeignDataWrapperRelationId, RowExclusiveLock);

	/* Must be super user */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to alter foreign-data wrapper \"%s\"",
						stmt->fdwname),
				 errhint("Must be superuser to alter a foreign-data wrapper.")));

	tp = SearchSysCacheCopy1(FOREIGNDATAWRAPPERNAME,
							 CStringGetDatum(stmt->fdwname));

	if (!HeapTupleIsValid(tp))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("foreign-data wrapper \"%s\" does not exist", stmt->fdwname)));

	fdwForm = (Form_pg_foreign_data_wrapper) GETSTRUCT(tp);
	fdwId = fdwForm->oid;

	memset(repl_val, 0, sizeof(repl_val));
	memset(repl_null, false, sizeof(repl_null));
	memset(repl_repl, false, sizeof(repl_repl));

	parse_func_options(stmt->func_options,
					   &handler_given, &fdwhandler,
					   &validator_given, &fdwvalidator);

	if (handler_given)
	{
		repl_val[Anum_pg_foreign_data_wrapper_fdwhandler - 1] = ObjectIdGetDatum(fdwhandler);
		repl_repl[Anum_pg_foreign_data_wrapper_fdwhandler - 1] = true;

		/*
		 * It could be that the behavior of accessing foreign table changes
		 * with the new handler.  Warn about this.
		 */
		ereport(WARNING,
				(errmsg("changing the foreign-data wrapper handler can change behavior of existing foreign tables")));
	}

	if (validator_given)
	{
		repl_val[Anum_pg_foreign_data_wrapper_fdwvalidator - 1] = ObjectIdGetDatum(fdwvalidator);
		repl_repl[Anum_pg_foreign_data_wrapper_fdwvalidator - 1] = true;

		/*
		 * It could be that existing options for the FDW or dependent SERVER,
		 * USER MAPPING or FOREIGN TABLE objects are no longer valid according
		 * to the new validator.  Warn about this.
		 */
		if (OidIsValid(fdwvalidator))
			ereport(WARNING,
					(errmsg("changing the foreign-data wrapper validator can cause "
							"the options for dependent objects to become invalid")));
	}
	else
	{
		/*
		 * Validator is not changed, but we need it for validating options.
		 */
		fdwvalidator = fdwForm->fdwvalidator;
	}

	/*
	 * If options specified, validate and update.
	 */
	if (stmt->options)
	{
		/* Extract the current options */
		datum = SysCacheGetAttr(FOREIGNDATAWRAPPEROID,
								tp,
								Anum_pg_foreign_data_wrapper_fdwoptions,
								&isnull);
		if (isnull)
			datum = PointerGetDatum(NULL);

		/* Transform the options */
		datum = transformGenericOptions(ForeignDataWrapperRelationId,
										datum,
										stmt->options,
										fdwvalidator);

		if (PointerIsValid(DatumGetPointer(datum)))
			repl_val[Anum_pg_foreign_data_wrapper_fdwoptions - 1] = datum;
		else
			repl_null[Anum_pg_foreign_data_wrapper_fdwoptions - 1] = true;

		repl_repl[Anum_pg_foreign_data_wrapper_fdwoptions - 1] = true;
	}

	/* Everything looks good - update the tuple */
	tp = heap_modify_tuple(tp, RelationGetDescr(rel),
						   repl_val, repl_null, repl_repl);

	CatalogTupleUpdate(rel, &tp->t_self, tp);

	heap_freetuple(tp);

	ObjectAddressSet(myself, ForeignDataWrapperRelationId, fdwId);

	/* Update function dependencies if we changed them */
	if (handler_given || validator_given)
	{
		ObjectAddress referenced;

		/*
		 * Flush all existing dependency records of this FDW on functions; we
		 * assume there can be none other than the ones we are fixing.
		 */
		deleteDependencyRecordsForClass(ForeignDataWrapperRelationId,
										fdwId,
										ProcedureRelationId,
										DEPENDENCY_NORMAL);

		/* And build new ones. */

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
	}

	InvokeObjectPostAlterHook(ForeignDataWrapperRelationId, fdwId, 0);

	table_close(rel, RowExclusiveLock);

	return myself;
}