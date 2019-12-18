#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_18__ {int /*<<< orphan*/  options; int /*<<< orphan*/  servername; } ;
struct TYPE_17__ {int /*<<< orphan*/  fdwvalidator; } ;
struct TYPE_16__ {int /*<<< orphan*/  serverid; int /*<<< orphan*/  fdwid; int /*<<< orphan*/  servername; } ;
struct TYPE_15__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_14__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ ForeignServer ;
typedef  TYPE_4__ ForeignDataWrapper ;
typedef  int Datum ;
typedef  TYPE_5__ CreateForeignTableStmt ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int Anum_pg_foreign_table_ftoptions ; 
 int Anum_pg_foreign_table_ftrelid ; 
 int Anum_pg_foreign_table_ftserver ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  DatumGetPointer (int) ; 
 int /*<<< orphan*/  ForeignServerRelationId ; 
 int /*<<< orphan*/  ForeignTableRelationId ; 
 TYPE_4__* GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 TYPE_3__* GetForeignServerByName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int Natts_pg_foreign_table ; 
 int /*<<< orphan*/  OBJECT_FOREIGN_SERVER ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ pg_foreign_server_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int transformGenericOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CreateForeignTable(CreateForeignTableStmt *stmt, Oid relid)
{
	Relation	ftrel;
	Datum		ftoptions;
	Datum		values[Natts_pg_foreign_table];
	bool		nulls[Natts_pg_foreign_table];
	HeapTuple	tuple;
	AclResult	aclresult;
	ObjectAddress myself;
	ObjectAddress referenced;
	Oid			ownerId;
	ForeignDataWrapper *fdw;
	ForeignServer *server;

	/*
	 * Advance command counter to ensure the pg_attribute tuple is visible;
	 * the tuple might be updated to add constraints in previous step.
	 */
	CommandCounterIncrement();

	ftrel = table_open(ForeignTableRelationId, RowExclusiveLock);

	/*
	 * For now the owner cannot be specified on create. Use effective user ID.
	 */
	ownerId = GetUserId();

	/*
	 * Check that the foreign server exists and that we have USAGE on it. Also
	 * get the actual FDW for option validation etc.
	 */
	server = GetForeignServerByName(stmt->servername, false);
	aclresult = pg_foreign_server_aclcheck(server->serverid, ownerId, ACL_USAGE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_FOREIGN_SERVER, server->servername);

	fdw = GetForeignDataWrapper(server->fdwid);

	/*
	 * Insert tuple into pg_foreign_table.
	 */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	values[Anum_pg_foreign_table_ftrelid - 1] = ObjectIdGetDatum(relid);
	values[Anum_pg_foreign_table_ftserver - 1] = ObjectIdGetDatum(server->serverid);
	/* Add table generic options */
	ftoptions = transformGenericOptions(ForeignTableRelationId,
										PointerGetDatum(NULL),
										stmt->options,
										fdw->fdwvalidator);

	if (PointerIsValid(DatumGetPointer(ftoptions)))
		values[Anum_pg_foreign_table_ftoptions - 1] = ftoptions;
	else
		nulls[Anum_pg_foreign_table_ftoptions - 1] = true;

	tuple = heap_form_tuple(ftrel->rd_att, values, nulls);

	CatalogTupleInsert(ftrel, tuple);

	heap_freetuple(tuple);

	/* Add pg_class dependency on the server */
	myself.classId = RelationRelationId;
	myself.objectId = relid;
	myself.objectSubId = 0;

	referenced.classId = ForeignServerRelationId;
	referenced.objectId = server->serverid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	table_close(ftrel, RowExclusiveLock);
}