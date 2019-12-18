#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int /*<<< orphan*/  rd_node; TYPE_1__* rd_rel; } ;
struct TYPE_7__ {int relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidMultiXactId ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ IsCatalogNamespace (scalar_t__) ; 
 scalar_t__ IsNormalProcessingMode () ; 
 scalar_t__ IsToastNamespace (scalar_t__) ; 
 scalar_t__ MyDatabaseTableSpace ; 
 int OidIsValid (scalar_t__) ; 
#define  RELKIND_COMPOSITE_TYPE 137 
#define  RELKIND_FOREIGN_TABLE 136 
 int /*<<< orphan*/  RELKIND_HAS_STORAGE (char) ; 
#define  RELKIND_INDEX 135 
#define  RELKIND_MATVIEW 134 
#define  RELKIND_PARTITIONED_INDEX 133 
#define  RELKIND_PARTITIONED_TABLE 132 
#define  RELKIND_RELATION 131 
#define  RELKIND_SEQUENCE 130 
#define  RELKIND_TOASTVALUE 129 
#define  RELKIND_VIEW 128 
 TYPE_2__* RelationBuildLocalRelation (char const*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,char,char) ; 
 int /*<<< orphan*/  RelationCreateStorage (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_namespace_name (scalar_t__) ; 
 int /*<<< orphan*/  table_relation_set_new_filenode (TYPE_2__*,int /*<<< orphan*/ *,char,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Relation
heap_create(const char *relname,
			Oid relnamespace,
			Oid reltablespace,
			Oid relid,
			Oid relfilenode,
			Oid accessmtd,
			TupleDesc tupDesc,
			char relkind,
			char relpersistence,
			bool shared_relation,
			bool mapped_relation,
			bool allow_system_table_mods,
			TransactionId *relfrozenxid,
			MultiXactId *relminmxid)
{
	bool		create_storage;
	Relation	rel;

	/* The caller must have provided an OID for the relation. */
	Assert(OidIsValid(relid));

	/*
	 * Don't allow creating relations in pg_catalog directly, even though it
	 * is allowed to move user defined relations there. Semantics with search
	 * paths including pg_catalog are too confusing for now.
	 *
	 * But allow creating indexes on relations in pg_catalog even if
	 * allow_system_table_mods = off, upper layers already guarantee it's on a
	 * user defined relation, not a system one.
	 */
	if (!allow_system_table_mods &&
		((IsCatalogNamespace(relnamespace) && relkind != RELKIND_INDEX) ||
		 IsToastNamespace(relnamespace)) &&
		IsNormalProcessingMode())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to create \"%s.%s\"",
						get_namespace_name(relnamespace), relname),
				 errdetail("System catalog modifications are currently disallowed.")));

	*relfrozenxid = InvalidTransactionId;
	*relminmxid = InvalidMultiXactId;

	/* Handle reltablespace for specific relkinds. */
	switch (relkind)
	{
		case RELKIND_VIEW:
		case RELKIND_COMPOSITE_TYPE:
		case RELKIND_FOREIGN_TABLE:

			/*
			 * Force reltablespace to zero if the relation has no physical
			 * storage.  This is mainly just for cleanliness' sake.
			 *
			 * Partitioned tables and indexes don't have physical storage
			 * either, but we want to keep their tablespace settings so that
			 * their children can inherit it.
			 */
			reltablespace = InvalidOid;
			break;

		case RELKIND_SEQUENCE:

			/*
			 * Force reltablespace to zero for sequences, since we don't
			 * support moving them around into different tablespaces.
			 */
			reltablespace = InvalidOid;
			break;
		default:
			break;
	}

	/*
	 * Decide whether to create storage. If caller passed a valid relfilenode,
	 * storage is already created, so don't do it here.  Also don't create it
	 * for relkinds without physical storage.
	 */
	if (!RELKIND_HAS_STORAGE(relkind) || OidIsValid(relfilenode))
		create_storage = false;
	else
	{
		create_storage = true;
		relfilenode = relid;
	}

	/*
	 * Never allow a pg_class entry to explicitly specify the database's
	 * default tablespace in reltablespace; force it to zero instead. This
	 * ensures that if the database is cloned with a different default
	 * tablespace, the pg_class entry will still match where CREATE DATABASE
	 * will put the physically copied relation.
	 *
	 * Yes, this is a bit of a hack.
	 */
	if (reltablespace == MyDatabaseTableSpace)
		reltablespace = InvalidOid;

	/*
	 * build the relcache entry.
	 */
	rel = RelationBuildLocalRelation(relname,
									 relnamespace,
									 tupDesc,
									 relid,
									 accessmtd,
									 relfilenode,
									 reltablespace,
									 shared_relation,
									 mapped_relation,
									 relpersistence,
									 relkind);

	/*
	 * Have the storage manager create the relation's disk file, if needed.
	 *
	 * For relations the callback creates both the main and the init fork, for
	 * indexes only the main fork is created. The other forks will be created
	 * on demand.
	 */
	if (create_storage)
	{
		RelationOpenSmgr(rel);

		switch (rel->rd_rel->relkind)
		{
			case RELKIND_VIEW:
			case RELKIND_COMPOSITE_TYPE:
			case RELKIND_FOREIGN_TABLE:
			case RELKIND_PARTITIONED_TABLE:
			case RELKIND_PARTITIONED_INDEX:
				Assert(false);
				break;

			case RELKIND_INDEX:
			case RELKIND_SEQUENCE:
				RelationCreateStorage(rel->rd_node, relpersistence);
				break;

			case RELKIND_RELATION:
			case RELKIND_TOASTVALUE:
			case RELKIND_MATVIEW:
				table_relation_set_new_filenode(rel, &rel->rd_node,
												relpersistence,
												relfrozenxid, relminmxid);
				break;
		}
	}

	return rel;
}