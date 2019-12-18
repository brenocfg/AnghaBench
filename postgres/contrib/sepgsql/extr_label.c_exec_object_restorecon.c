#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct selabel_handle {int dummy; } ;
typedef  int /*<<< orphan*/  security_context_t ;
struct TYPE_14__ {int /*<<< orphan*/  attnum; int /*<<< orphan*/  attrelid; int /*<<< orphan*/  attname; } ;
struct TYPE_13__ {int relnamespace; int /*<<< orphan*/  oid; int /*<<< orphan*/  relname; int /*<<< orphan*/  relkind; } ;
struct TYPE_12__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  datname; } ;
struct TYPE_11__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  nspname; } ;
struct TYPE_10__ {int pronamespace; int /*<<< orphan*/  oid; int /*<<< orphan*/  proname; } ;
struct TYPE_9__ {int classId; int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;
typedef  TYPE_3__* Form_pg_namespace ;
typedef  TYPE_4__* Form_pg_database ;
typedef  TYPE_5__* Form_pg_class ;
typedef  TYPE_6__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
#define  AttributeRelationId 132 
#define  DatabaseRelationId 131 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
#define  NamespaceRelationId 130 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
#define  ProcedureRelationId 129 
 int /*<<< orphan*/  RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RELKIND_RELATION ; 
 int /*<<< orphan*/  RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  RELKIND_VIEW ; 
#define  RelationRelationId 128 
 int SELABEL_DB_COLUMN ; 
 int SELABEL_DB_DATABASE ; 
 int SELABEL_DB_PROCEDURE ; 
 int SELABEL_DB_SCHEMA ; 
 int SELABEL_DB_SEQUENCE ; 
 int SELABEL_DB_TABLE ; 
 int SELABEL_DB_VIEW ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SetSecurityLabel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  freecon (int /*<<< orphan*/ ) ; 
 char* get_database_name (int /*<<< orphan*/ ) ; 
 char* get_namespace_name (int) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* quote_object_name (char*,char*,char*,char*) ; 
 scalar_t__ selabel_lookup_raw (struct selabel_handle*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sepgsql_object_relabel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
exec_object_restorecon(struct selabel_handle *sehnd, Oid catalogId)
{
	Relation	rel;
	SysScanDesc sscan;
	HeapTuple	tuple;
	char	   *database_name = get_database_name(MyDatabaseId);
	char	   *namespace_name;
	Oid			namespace_id;
	char	   *relation_name;

	/*
	 * Open the target catalog. We don't want to allow writable accesses by
	 * other session during initial labeling.
	 */
	rel = table_open(catalogId, AccessShareLock);

	sscan = systable_beginscan(rel, InvalidOid, false,
							   NULL, 0, NULL);
	while (HeapTupleIsValid(tuple = systable_getnext(sscan)))
	{
		Form_pg_database datForm;
		Form_pg_namespace nspForm;
		Form_pg_class relForm;
		Form_pg_attribute attForm;
		Form_pg_proc proForm;
		char	   *objname;
		int			objtype = 1234;
		ObjectAddress object;
		security_context_t context;

		/*
		 * The way to determine object name depends on object classes. So, any
		 * branches set up `objtype', `objname' and `object' here.
		 */
		switch (catalogId)
		{
			case DatabaseRelationId:
				datForm = (Form_pg_database) GETSTRUCT(tuple);

				objtype = SELABEL_DB_DATABASE;

				objname = quote_object_name(NameStr(datForm->datname),
											NULL, NULL, NULL);

				object.classId = DatabaseRelationId;
				object.objectId = datForm->oid;
				object.objectSubId = 0;
				break;

			case NamespaceRelationId:
				nspForm = (Form_pg_namespace) GETSTRUCT(tuple);

				objtype = SELABEL_DB_SCHEMA;

				objname = quote_object_name(database_name,
											NameStr(nspForm->nspname),
											NULL, NULL);

				object.classId = NamespaceRelationId;
				object.objectId = nspForm->oid;
				object.objectSubId = 0;
				break;

			case RelationRelationId:
				relForm = (Form_pg_class) GETSTRUCT(tuple);

				if (relForm->relkind == RELKIND_RELATION ||
					relForm->relkind == RELKIND_PARTITIONED_TABLE)
					objtype = SELABEL_DB_TABLE;
				else if (relForm->relkind == RELKIND_SEQUENCE)
					objtype = SELABEL_DB_SEQUENCE;
				else if (relForm->relkind == RELKIND_VIEW)
					objtype = SELABEL_DB_VIEW;
				else
					continue;	/* no need to assign security label */

				namespace_name = get_namespace_name(relForm->relnamespace);
				objname = quote_object_name(database_name,
											namespace_name,
											NameStr(relForm->relname),
											NULL);
				pfree(namespace_name);

				object.classId = RelationRelationId;
				object.objectId = relForm->oid;
				object.objectSubId = 0;
				break;

			case AttributeRelationId:
				attForm = (Form_pg_attribute) GETSTRUCT(tuple);

				if (get_rel_relkind(attForm->attrelid) != RELKIND_RELATION &&
					get_rel_relkind(attForm->attrelid) != RELKIND_PARTITIONED_TABLE)
					continue;	/* no need to assign security label */

				objtype = SELABEL_DB_COLUMN;

				namespace_id = get_rel_namespace(attForm->attrelid);
				namespace_name = get_namespace_name(namespace_id);
				relation_name = get_rel_name(attForm->attrelid);
				objname = quote_object_name(database_name,
											namespace_name,
											relation_name,
											NameStr(attForm->attname));
				pfree(namespace_name);
				pfree(relation_name);

				object.classId = RelationRelationId;
				object.objectId = attForm->attrelid;
				object.objectSubId = attForm->attnum;
				break;

			case ProcedureRelationId:
				proForm = (Form_pg_proc) GETSTRUCT(tuple);

				objtype = SELABEL_DB_PROCEDURE;

				namespace_name = get_namespace_name(proForm->pronamespace);
				objname = quote_object_name(database_name,
											namespace_name,
											NameStr(proForm->proname),
											NULL);
				pfree(namespace_name);

				object.classId = ProcedureRelationId;
				object.objectId = proForm->oid;
				object.objectSubId = 0;
				break;

			default:
				elog(ERROR, "unexpected catalog id: %u", catalogId);
				objname = NULL; /* for compiler quiet */
				break;
		}

		if (selabel_lookup_raw(sehnd, &context, objname, objtype) == 0)
		{
			PG_TRY();
			{
				/*
				 * Check SELinux permission to relabel the fetched object,
				 * then do the actual relabeling.
				 */
				sepgsql_object_relabel(&object, context);

				SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, context);
			}
			PG_FINALLY();
			{
				freecon(context);
			}
			PG_END_TRY();
		}
		else if (errno == ENOENT)
			ereport(WARNING,
					(errmsg("SELinux: no initial label assigned for %s (type=%d), skipping",
							objname, objtype)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("SELinux: could not determine initial security label for %s (type=%d): %m", objname, objtype)));

		pfree(objname);
	}
	systable_endscan(sscan);

	table_close(rel, NoLock);
}