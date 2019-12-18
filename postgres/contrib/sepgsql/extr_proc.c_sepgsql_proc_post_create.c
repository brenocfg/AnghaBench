#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_12__ {int /*<<< orphan*/ * values; } ;
struct TYPE_15__ {int pronargs; scalar_t__ proleakproof; TYPE_1__ proargtypes; int /*<<< orphan*/  proname; int /*<<< orphan*/  pronamespace; } ;
struct TYPE_14__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_13__ {char* data; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_proc_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcedureOidIndexId ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_PROCEDURE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SCHEMA ; 
 int /*<<< orphan*/  SEPG_DB_PROCEDURE__CREATE ; 
 int /*<<< orphan*/  SEPG_DB_PROCEDURE__INSTALL ; 
 int /*<<< orphan*/  SEPG_DB_SCHEMA__ADD_NAME ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityLabel (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getObjectIdentity (TYPE_3__*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  quote_qualified_identifier (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 char* sepgsql_compute_create (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sepgsql_get_client_label () ; 
 char* sepgsql_get_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sepgsql_proc_post_create(Oid functionId)
{
	Relation	rel;
	ScanKeyData skey;
	SysScanDesc sscan;
	HeapTuple	tuple;
	char	   *nsp_name;
	char	   *scontext;
	char	   *tcontext;
	char	   *ncontext;
	uint32		required;
	int			i;
	StringInfoData audit_name;
	ObjectAddress object;
	Form_pg_proc proForm;

	/*
	 * Fetch namespace of the new procedure. Because pg_proc entry is not
	 * visible right now, we need to scan the catalog using SnapshotSelf.
	 */
	rel = table_open(ProcedureRelationId, AccessShareLock);

	ScanKeyInit(&skey,
				Anum_pg_proc_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(functionId));

	sscan = systable_beginscan(rel, ProcedureOidIndexId, true,
							   SnapshotSelf, 1, &skey);

	tuple = systable_getnext(sscan);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for function %u", functionId);

	proForm = (Form_pg_proc) GETSTRUCT(tuple);

	/*
	 * check db_schema:{add_name} permission of the namespace
	 */
	object.classId = NamespaceRelationId;
	object.objectId = proForm->pronamespace;
	object.objectSubId = 0;
	sepgsql_avc_check_perms(&object,
							SEPG_CLASS_DB_SCHEMA,
							SEPG_DB_SCHEMA__ADD_NAME,
							getObjectIdentity(&object),
							true);

	/*
	 * XXX - db_language:{implement} also should be checked here
	 */


	/*
	 * Compute a default security label when we create a new procedure object
	 * under the specified namespace.
	 */
	scontext = sepgsql_get_client_label();
	tcontext = sepgsql_get_label(NamespaceRelationId,
								 proForm->pronamespace, 0);
	ncontext = sepgsql_compute_create(scontext, tcontext,
									  SEPG_CLASS_DB_PROCEDURE,
									  NameStr(proForm->proname));

	/*
	 * check db_procedure:{create (install)} permission
	 */
	initStringInfo(&audit_name);
	nsp_name = get_namespace_name(proForm->pronamespace);
	appendStringInfo(&audit_name, "%s(",
					 quote_qualified_identifier(nsp_name, NameStr(proForm->proname)));
	for (i = 0; i < proForm->pronargs; i++)
	{
		if (i > 0)
			appendStringInfoChar(&audit_name, ',');

		object.classId = TypeRelationId;
		object.objectId = proForm->proargtypes.values[i];
		object.objectSubId = 0;
		appendStringInfoString(&audit_name, getObjectIdentity(&object));
	}
	appendStringInfoChar(&audit_name, ')');

	required = SEPG_DB_PROCEDURE__CREATE;
	if (proForm->proleakproof)
		required |= SEPG_DB_PROCEDURE__INSTALL;

	sepgsql_avc_check_perms_label(ncontext,
								  SEPG_CLASS_DB_PROCEDURE,
								  required,
								  audit_name.data,
								  true);

	/*
	 * Assign the default security label on a new procedure
	 */
	object.classId = ProcedureRelationId;
	object.objectId = functionId;
	object.objectSubId = 0;
	SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, ncontext);

	/*
	 * Cleanup
	 */
	systable_endscan(sscan);
	table_close(rel, AccessShareLock);

	pfree(audit_name.data);
	pfree(tcontext);
	pfree(ncontext);
}