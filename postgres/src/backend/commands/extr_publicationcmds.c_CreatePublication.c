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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_3__ {int for_all_tables; scalar_t__ tables; int /*<<< orphan*/  options; int /*<<< orphan*/  pubname; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;
typedef  TYPE_1__ CreatePublicationStmt ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int Anum_pg_publication_oid ; 
 int Anum_pg_publication_puballtables ; 
 int Anum_pg_publication_pubdelete ; 
 int Anum_pg_publication_pubinsert ; 
 int Anum_pg_publication_pubname ; 
 int Anum_pg_publication_pubowner ; 
 int Anum_pg_publication_pubtruncate ; 
 int Anum_pg_publication_pubupdate ; 
 int /*<<< orphan*/  Assert (int) ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseTableList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetSysCacheOid1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int Natts_pg_publication ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenTableList (scalar_t__) ; 
 int /*<<< orphan*/  PUBLICATIONNAME ; 
 int /*<<< orphan*/  PublicationAddTables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PublicationObjectIndexId ; 
 int /*<<< orphan*/  PublicationRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ WAL_LEVEL_LOGICAL ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 scalar_t__ list_length (scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namein ; 
 int /*<<< orphan*/  parse_publication_options (int /*<<< orphan*/ ,int*,int*,int*,int*,int*) ; 
 scalar_t__ pg_database_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wal_level ; 

ObjectAddress
CreatePublication(CreatePublicationStmt *stmt)
{
	Relation	rel;
	ObjectAddress myself;
	Oid			puboid;
	bool		nulls[Natts_pg_publication];
	Datum		values[Natts_pg_publication];
	HeapTuple	tup;
	bool		publish_given;
	bool		publish_insert;
	bool		publish_update;
	bool		publish_delete;
	bool		publish_truncate;
	AclResult	aclresult;

	/* must have CREATE privilege on database */
	aclresult = pg_database_aclcheck(MyDatabaseId, GetUserId(), ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_DATABASE,
					   get_database_name(MyDatabaseId));

	/* FOR ALL TABLES requires superuser */
	if (stmt->for_all_tables && !superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 (errmsg("must be superuser to create FOR ALL TABLES publication"))));

	rel = table_open(PublicationRelationId, RowExclusiveLock);

	/* Check if name is used */
	puboid = GetSysCacheOid1(PUBLICATIONNAME, Anum_pg_publication_oid,
							 CStringGetDatum(stmt->pubname));
	if (OidIsValid(puboid))
	{
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("publication \"%s\" already exists",
						stmt->pubname)));
	}

	/* Form a tuple. */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	values[Anum_pg_publication_pubname - 1] =
		DirectFunctionCall1(namein, CStringGetDatum(stmt->pubname));
	values[Anum_pg_publication_pubowner - 1] = ObjectIdGetDatum(GetUserId());

	parse_publication_options(stmt->options,
							  &publish_given, &publish_insert,
							  &publish_update, &publish_delete,
							  &publish_truncate);

	puboid = GetNewOidWithIndex(rel, PublicationObjectIndexId,
								Anum_pg_publication_oid);
	values[Anum_pg_publication_oid - 1] = ObjectIdGetDatum(puboid);
	values[Anum_pg_publication_puballtables - 1] =
		BoolGetDatum(stmt->for_all_tables);
	values[Anum_pg_publication_pubinsert - 1] =
		BoolGetDatum(publish_insert);
	values[Anum_pg_publication_pubupdate - 1] =
		BoolGetDatum(publish_update);
	values[Anum_pg_publication_pubdelete - 1] =
		BoolGetDatum(publish_delete);
	values[Anum_pg_publication_pubtruncate - 1] =
		BoolGetDatum(publish_truncate);

	tup = heap_form_tuple(RelationGetDescr(rel), values, nulls);

	/* Insert tuple into catalog. */
	CatalogTupleInsert(rel, tup);
	heap_freetuple(tup);

	recordDependencyOnOwner(PublicationRelationId, puboid, GetUserId());

	ObjectAddressSet(myself, PublicationRelationId, puboid);

	/* Make the changes visible. */
	CommandCounterIncrement();

	if (stmt->tables)
	{
		List	   *rels;

		Assert(list_length(stmt->tables) > 0);

		rels = OpenTableList(stmt->tables);
		PublicationAddTables(puboid, rels, true, NULL);
		CloseTableList(rels);
	}

	table_close(rel, RowExclusiveLock);

	InvokeObjectPostCreateHook(PublicationRelationId, puboid, 0);

	if (wal_level != WAL_LEVEL_LOGICAL)
	{
		ereport(WARNING,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("wal_level is insufficient to publish logical changes"),
				 errhint("Set wal_level to logical before creating subscriptions.")));
	}

	return myself;
}