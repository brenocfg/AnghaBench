#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  nspname; } ;
struct TYPE_8__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_namespace ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_namespace_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceOidIndexId ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SCHEMA ; 
 int /*<<< orphan*/  SEPG_DB_SCHEMA__CREATE ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityLabel (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  quote_identifier (char const*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sepgsql_compute_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sepgsql_get_client_label () ; 
 char* sepgsql_get_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sepgsql_schema_post_create(Oid namespaceId)
{
	Relation	rel;
	ScanKeyData skey;
	SysScanDesc sscan;
	HeapTuple	tuple;
	char	   *tcontext;
	char	   *ncontext;
	const char *nsp_name;
	ObjectAddress object;
	Form_pg_namespace nspForm;
	StringInfoData audit_name;

	/*
	 * Compute a default security label when we create a new schema object
	 * under the working database.
	 *
	 * XXX - upcoming version of libselinux supports to take object name to
	 * handle special treatment on default security label; such as special
	 * label on "pg_temp" schema.
	 */
	rel = table_open(NamespaceRelationId, AccessShareLock);

	ScanKeyInit(&skey,
				Anum_pg_namespace_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(namespaceId));

	sscan = systable_beginscan(rel, NamespaceOidIndexId, true,
							   SnapshotSelf, 1, &skey);
	tuple = systable_getnext(sscan);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for namespace %u", namespaceId);

	nspForm = (Form_pg_namespace) GETSTRUCT(tuple);
	nsp_name = NameStr(nspForm->nspname);
	if (strncmp(nsp_name, "pg_temp_", 8) == 0)
		nsp_name = "pg_temp";
	else if (strncmp(nsp_name, "pg_toast_temp_", 14) == 0)
		nsp_name = "pg_toast_temp";

	tcontext = sepgsql_get_label(DatabaseRelationId, MyDatabaseId, 0);
	ncontext = sepgsql_compute_create(sepgsql_get_client_label(),
									  tcontext,
									  SEPG_CLASS_DB_SCHEMA,
									  nsp_name);

	/*
	 * check db_schema:{create}
	 */
	initStringInfo(&audit_name);
	appendStringInfo(&audit_name, "%s", quote_identifier(nsp_name));
	sepgsql_avc_check_perms_label(ncontext,
								  SEPG_CLASS_DB_SCHEMA,
								  SEPG_DB_SCHEMA__CREATE,
								  audit_name.data,
								  true);
	systable_endscan(sscan);
	table_close(rel, AccessShareLock);

	/*
	 * Assign the default security label on a new procedure
	 */
	object.classId = NamespaceRelationId;
	object.objectId = namespaceId;
	object.objectSubId = 0;
	SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, ncontext);

	pfree(ncontext);
	pfree(tcontext);
}