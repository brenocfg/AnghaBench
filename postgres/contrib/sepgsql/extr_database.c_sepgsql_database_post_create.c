#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  datname; } ;
struct TYPE_9__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; void* classId; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_database ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_database_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DatabaseOidIndexId ; 
 void* DatabaseRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 char const* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_DATABASE ; 
 int /*<<< orphan*/  SEPG_DB_DATABASE__CREATE ; 
 int /*<<< orphan*/  SEPG_DB_DATABASE__GETATTR ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityLabel (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_oid (char const*,int) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  quote_identifier (char const*) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sepgsql_compute_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sepgsql_get_client_label () ; 
 char* sepgsql_get_label (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (void*,int /*<<< orphan*/ ) ; 

void
sepgsql_database_post_create(Oid databaseId, const char *dtemplate)
{
	Relation	rel;
	ScanKeyData skey;
	SysScanDesc sscan;
	HeapTuple	tuple;
	char	   *tcontext;
	char	   *ncontext;
	ObjectAddress object;
	Form_pg_database datForm;
	StringInfoData audit_name;

	/*
	 * Oid of the source database is not saved in pg_database catalog, so we
	 * collect its identifier using contextual information. If NULL, its
	 * default is "template1" according to createdb().
	 */
	if (!dtemplate)
		dtemplate = "template1";

	object.classId = DatabaseRelationId;
	object.objectId = get_database_oid(dtemplate, false);
	object.objectSubId = 0;

	tcontext = sepgsql_get_label(object.classId,
								 object.objectId,
								 object.objectSubId);

	/*
	 * check db_database:{getattr} permission
	 */
	initStringInfo(&audit_name);
	appendStringInfoString(&audit_name, quote_identifier(dtemplate));
	sepgsql_avc_check_perms_label(tcontext,
								  SEPG_CLASS_DB_DATABASE,
								  SEPG_DB_DATABASE__GETATTR,
								  audit_name.data,
								  true);

	/*
	 * Compute a default security label of the newly created database based on
	 * a pair of security label of client and source database.
	 *
	 * XXX - upcoming version of libselinux supports to take object name to
	 * handle special treatment on default security label.
	 */
	rel = table_open(DatabaseRelationId, AccessShareLock);

	ScanKeyInit(&skey,
				Anum_pg_database_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(databaseId));

	sscan = systable_beginscan(rel, DatabaseOidIndexId, true,
							   SnapshotSelf, 1, &skey);
	tuple = systable_getnext(sscan);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for database %u", databaseId);

	datForm = (Form_pg_database) GETSTRUCT(tuple);

	ncontext = sepgsql_compute_create(sepgsql_get_client_label(),
									  tcontext,
									  SEPG_CLASS_DB_DATABASE,
									  NameStr(datForm->datname));

	/*
	 * check db_database:{create} permission
	 */
	resetStringInfo(&audit_name);
	appendStringInfoString(&audit_name,
						   quote_identifier(NameStr(datForm->datname)));
	sepgsql_avc_check_perms_label(ncontext,
								  SEPG_CLASS_DB_DATABASE,
								  SEPG_DB_DATABASE__CREATE,
								  audit_name.data,
								  true);

	systable_endscan(sscan);
	table_close(rel, AccessShareLock);

	/*
	 * Assign the default security label on the new database
	 */
	object.classId = DatabaseRelationId;
	object.objectId = databaseId;
	object.objectSubId = 0;

	SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, ncontext);

	pfree(ncontext);
	pfree(tcontext);
}