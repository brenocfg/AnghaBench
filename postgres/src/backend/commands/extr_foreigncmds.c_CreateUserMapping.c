#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_23__ {int /*<<< orphan*/  options; int /*<<< orphan*/  servername; scalar_t__ if_not_exists; scalar_t__ user; } ;
struct TYPE_22__ {int /*<<< orphan*/  fdwvalidator; } ;
struct TYPE_21__ {int /*<<< orphan*/  serverid; int /*<<< orphan*/  fdwid; } ;
struct TYPE_20__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_19__ {int /*<<< orphan*/  rd_att; } ;
struct TYPE_18__ {scalar_t__ roletype; } ;
typedef  TYPE_1__ RoleSpec ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__ ForeignServer ;
typedef  TYPE_5__ ForeignDataWrapper ;
typedef  int Datum ;
typedef  TYPE_6__ CreateUserMappingStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_ID_PUBLIC ; 
 int Anum_pg_user_mapping_oid ; 
 int Anum_pg_user_mapping_umoptions ; 
 int Anum_pg_user_mapping_umserver ; 
 int Anum_pg_user_mapping_umuser ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  DatumGetPointer (int) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ForeignServerRelationId ; 
 TYPE_5__* GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 TYPE_4__* GetForeignServerByName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetNewOidWithIndex (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetSysCacheOid2 (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_3__ InvalidObjectAddress ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappingUserName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 int Natts_pg_user_mapping ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ ROLESPEC_PUBLIC ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  USERMAPPINGUSERSERVER ; 
 int /*<<< orphan*/  UserMappingOidIndexId ; 
 int /*<<< orphan*/  UserMappingRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rolespec_oid (scalar_t__,int) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int transformGenericOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mapping_ddl_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
CreateUserMapping(CreateUserMappingStmt *stmt)
{
	Relation	rel;
	Datum		useoptions;
	Datum		values[Natts_pg_user_mapping];
	bool		nulls[Natts_pg_user_mapping];
	HeapTuple	tuple;
	Oid			useId;
	Oid			umId;
	ObjectAddress myself;
	ObjectAddress referenced;
	ForeignServer *srv;
	ForeignDataWrapper *fdw;
	RoleSpec   *role = (RoleSpec *) stmt->user;

	rel = table_open(UserMappingRelationId, RowExclusiveLock);

	if (role->roletype == ROLESPEC_PUBLIC)
		useId = ACL_ID_PUBLIC;
	else
		useId = get_rolespec_oid(stmt->user, false);

	/* Check that the server exists. */
	srv = GetForeignServerByName(stmt->servername, false);

	user_mapping_ddl_aclcheck(useId, srv->serverid, stmt->servername);

	/*
	 * Check that the user mapping is unique within server.
	 */
	umId = GetSysCacheOid2(USERMAPPINGUSERSERVER, Anum_pg_user_mapping_oid,
						   ObjectIdGetDatum(useId),
						   ObjectIdGetDatum(srv->serverid));

	if (OidIsValid(umId))
	{
		if (stmt->if_not_exists)
		{
			ereport(NOTICE,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("user mapping for \"%s\" already exists for server \"%s\", skipping",
							MappingUserName(useId),
							stmt->servername)));

			table_close(rel, RowExclusiveLock);
			return InvalidObjectAddress;
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("user mapping for \"%s\" already exists for server \"%s\"",
							MappingUserName(useId),
							stmt->servername)));
	}

	fdw = GetForeignDataWrapper(srv->fdwid);

	/*
	 * Insert tuple into pg_user_mapping.
	 */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	umId = GetNewOidWithIndex(rel, UserMappingOidIndexId,
							  Anum_pg_user_mapping_oid);
	values[Anum_pg_user_mapping_oid - 1] = ObjectIdGetDatum(umId);
	values[Anum_pg_user_mapping_umuser - 1] = ObjectIdGetDatum(useId);
	values[Anum_pg_user_mapping_umserver - 1] = ObjectIdGetDatum(srv->serverid);

	/* Add user options */
	useoptions = transformGenericOptions(UserMappingRelationId,
										 PointerGetDatum(NULL),
										 stmt->options,
										 fdw->fdwvalidator);

	if (PointerIsValid(DatumGetPointer(useoptions)))
		values[Anum_pg_user_mapping_umoptions - 1] = useoptions;
	else
		nulls[Anum_pg_user_mapping_umoptions - 1] = true;

	tuple = heap_form_tuple(rel->rd_att, values, nulls);

	CatalogTupleInsert(rel, tuple);

	heap_freetuple(tuple);

	/* Add dependency on the server */
	myself.classId = UserMappingRelationId;
	myself.objectId = umId;
	myself.objectSubId = 0;

	referenced.classId = ForeignServerRelationId;
	referenced.objectId = srv->serverid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	if (OidIsValid(useId))
	{
		/* Record the mapped user dependency */
		recordDependencyOnOwner(UserMappingRelationId, umId, useId);
	}

	/*
	 * Perhaps someday there should be a recordDependencyOnCurrentExtension
	 * call here; but since roles aren't members of extensions, it seems like
	 * user mappings shouldn't be either.  Note that the grammar and pg_dump
	 * would need to be extended too if we change this.
	 */

	/* Post creation hook for new user mapping */
	InvokeObjectPostCreateHook(UserMappingRelationId, umId, 0);

	table_close(rel, RowExclusiveLock);

	return myself;
}