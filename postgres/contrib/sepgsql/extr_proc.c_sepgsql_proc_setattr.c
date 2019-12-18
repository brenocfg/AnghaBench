#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {scalar_t__ pronamespace; scalar_t__ proleakproof; int /*<<< orphan*/  proname; } ;
struct TYPE_5__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_proc_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ProcedureOidIndexId ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_PROCEDURE ; 
 int /*<<< orphan*/  SEPG_DB_PROCEDURE__INSTALL ; 
 int /*<<< orphan*/  SEPG_DB_PROCEDURE__SETATTR ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* getObjectIdentity (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sepgsql_schema_add_name (scalar_t__) ; 
 int /*<<< orphan*/  sepgsql_schema_remove_name (scalar_t__) ; 
 int /*<<< orphan*/  sepgsql_schema_rename (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sepgsql_proc_setattr(Oid functionId)
{
	Relation	rel;
	ScanKeyData skey;
	SysScanDesc sscan;
	HeapTuple	oldtup;
	HeapTuple	newtup;
	Form_pg_proc oldform;
	Form_pg_proc newform;
	uint32		required;
	ObjectAddress object;
	char	   *audit_name;

	/*
	 * Fetch newer catalog
	 */
	rel = table_open(ProcedureRelationId, AccessShareLock);

	ScanKeyInit(&skey,
				Anum_pg_proc_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(functionId));

	sscan = systable_beginscan(rel, ProcedureOidIndexId, true,
							   SnapshotSelf, 1, &skey);
	newtup = systable_getnext(sscan);
	if (!HeapTupleIsValid(newtup))
		elog(ERROR, "could not find tuple for function %u", functionId);
	newform = (Form_pg_proc) GETSTRUCT(newtup);

	/*
	 * Fetch older catalog
	 */
	oldtup = SearchSysCache1(PROCOID, ObjectIdGetDatum(functionId));
	if (!HeapTupleIsValid(oldtup))
		elog(ERROR, "cache lookup failed for function %u", functionId);
	oldform = (Form_pg_proc) GETSTRUCT(oldtup);

	/*
	 * Does this ALTER command takes operation to namespace?
	 */
	if (newform->pronamespace != oldform->pronamespace)
	{
		sepgsql_schema_remove_name(oldform->pronamespace);
		sepgsql_schema_add_name(oldform->pronamespace);
	}
	if (strcmp(NameStr(newform->proname), NameStr(oldform->proname)) != 0)
		sepgsql_schema_rename(oldform->pronamespace);

	/*
	 * check db_procedure:{setattr (install)} permission
	 */
	required = SEPG_DB_PROCEDURE__SETATTR;
	if (!oldform->proleakproof && newform->proleakproof)
		required |= SEPG_DB_PROCEDURE__INSTALL;

	object.classId = ProcedureRelationId;
	object.objectId = functionId;
	object.objectSubId = 0;
	audit_name = getObjectIdentity(&object);

	sepgsql_avc_check_perms(&object,
							SEPG_CLASS_DB_PROCEDURE,
							required,
							audit_name,
							true);
	/* cleanups */
	pfree(audit_name);

	ReleaseSysCache(oldtup);
	systable_endscan(sscan);
	table_close(rel, AccessShareLock);
}