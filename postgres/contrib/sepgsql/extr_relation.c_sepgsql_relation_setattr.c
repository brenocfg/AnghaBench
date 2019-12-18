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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ relnamespace; int /*<<< orphan*/  relname; } ;
struct TYPE_5__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_class_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ClassOidIndexId ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
#define  RELKIND_INDEX 132 
#define  RELKIND_PARTITIONED_TABLE 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_SEQUENCE 129 
#define  RELKIND_VIEW 128 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SEQUENCE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_TABLE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_VIEW ; 
 int /*<<< orphan*/  SEPG_DB_TABLE__SETATTR ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* getObjectIdentity (TYPE_1__*) ; 
 int get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sepgsql_index_modify (int /*<<< orphan*/ ) ; 
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
sepgsql_relation_setattr(Oid relOid)
{
	Relation	rel;
	ScanKeyData skey;
	SysScanDesc sscan;
	HeapTuple	oldtup;
	HeapTuple	newtup;
	Form_pg_class oldform;
	Form_pg_class newform;
	ObjectAddress object;
	char	   *audit_name;
	uint16_t	tclass;

	switch (get_rel_relkind(relOid))
	{
		case RELKIND_RELATION:
		case RELKIND_PARTITIONED_TABLE:
			tclass = SEPG_CLASS_DB_TABLE;
			break;
		case RELKIND_SEQUENCE:
			tclass = SEPG_CLASS_DB_SEQUENCE;
			break;
		case RELKIND_VIEW:
			tclass = SEPG_CLASS_DB_VIEW;
			break;
		case RELKIND_INDEX:
			/* deal with indexes specially */
			sepgsql_index_modify(relOid);
			return;
		default:
			/* other relkinds don't need additional work */
			return;
	}

	/*
	 * Fetch newer catalog
	 */
	rel = table_open(RelationRelationId, AccessShareLock);

	ScanKeyInit(&skey,
				Anum_pg_class_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relOid));

	sscan = systable_beginscan(rel, ClassOidIndexId, true,
							   SnapshotSelf, 1, &skey);

	newtup = systable_getnext(sscan);
	if (!HeapTupleIsValid(newtup))
		elog(ERROR, "could not find tuple for relation %u", relOid);
	newform = (Form_pg_class) GETSTRUCT(newtup);

	/*
	 * Fetch older catalog
	 */
	oldtup = SearchSysCache1(RELOID, ObjectIdGetDatum(relOid));
	if (!HeapTupleIsValid(oldtup))
		elog(ERROR, "cache lookup failed for relation %u", relOid);
	oldform = (Form_pg_class) GETSTRUCT(oldtup);

	/*
	 * Does this ALTER command takes operation to namespace?
	 */
	if (newform->relnamespace != oldform->relnamespace)
	{
		sepgsql_schema_remove_name(oldform->relnamespace);
		sepgsql_schema_add_name(newform->relnamespace);
	}
	if (strcmp(NameStr(newform->relname), NameStr(oldform->relname)) != 0)
		sepgsql_schema_rename(oldform->relnamespace);

	/*
	 * XXX - In the future version, db_tuple:{use} of system catalog entry
	 * shall be checked, if tablespace configuration is changed.
	 */

	/*
	 * check db_xxx:{setattr} permission
	 */
	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = 0;
	audit_name = getObjectIdentity(&object);

	sepgsql_avc_check_perms(&object,
							tclass,
							SEPG_DB_TABLE__SETATTR,
							audit_name,
							true);
	pfree(audit_name);

	ReleaseSysCache(oldtup);
	systable_endscan(sscan);
	table_close(rel, AccessShareLock);
}