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
struct TYPE_10__ {int /*<<< orphan*/  attname; } ;
struct TYPE_9__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_attribute_attnum ; 
 int /*<<< orphan*/  Anum_pg_attribute_attrelid ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  AttributeRelidNumIndexId ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT2EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 void* RelationRelationId ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_COLUMN ; 
 int /*<<< orphan*/  SEPG_DB_COLUMN__CREATE ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityLabel (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,void*) ; 
 int /*<<< orphan*/  getObjectIdentity (TYPE_2__*) ; 
 char get_rel_relkind (void*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sepgsql_compute_create (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sepgsql_get_client_label () ; 
 char* sepgsql_get_label (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sepgsql_attribute_post_create(Oid relOid, AttrNumber attnum)
{
	Relation	rel;
	ScanKeyData skey[2];
	SysScanDesc sscan;
	HeapTuple	tuple;
	char	   *scontext;
	char	   *tcontext;
	char	   *ncontext;
	ObjectAddress object;
	Form_pg_attribute attForm;
	StringInfoData audit_name;
	char		relkind = get_rel_relkind(relOid);

	/*
	 * Only attributes within regular relations or partition relations have
	 * individual security labels.
	 */
	if (relkind != RELKIND_RELATION && relkind != RELKIND_PARTITIONED_TABLE)
		return;

	/*
	 * Compute a default security label of the new column underlying the
	 * specified relation, and check permission to create it.
	 */
	rel = table_open(AttributeRelationId, AccessShareLock);

	ScanKeyInit(&skey[0],
				Anum_pg_attribute_attrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relOid));
	ScanKeyInit(&skey[1],
				Anum_pg_attribute_attnum,
				BTEqualStrategyNumber, F_INT2EQ,
				Int16GetDatum(attnum));

	sscan = systable_beginscan(rel, AttributeRelidNumIndexId, true,
							   SnapshotSelf, 2, &skey[0]);

	tuple = systable_getnext(sscan);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for column %d of relation %u",
			 attnum, relOid);

	attForm = (Form_pg_attribute) GETSTRUCT(tuple);

	scontext = sepgsql_get_client_label();
	tcontext = sepgsql_get_label(RelationRelationId, relOid, 0);
	ncontext = sepgsql_compute_create(scontext, tcontext,
									  SEPG_CLASS_DB_COLUMN,
									  NameStr(attForm->attname));

	/*
	 * check db_column:{create} permission
	 */
	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = 0;

	initStringInfo(&audit_name);
	appendStringInfo(&audit_name, "%s.%s",
					 getObjectIdentity(&object),
					 quote_identifier(NameStr(attForm->attname)));
	sepgsql_avc_check_perms_label(ncontext,
								  SEPG_CLASS_DB_COLUMN,
								  SEPG_DB_COLUMN__CREATE,
								  audit_name.data,
								  true);

	/*
	 * Assign the default security label on a new procedure
	 */
	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = attnum;
	SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, ncontext);

	systable_endscan(sscan);
	table_close(rel, AccessShareLock);

	pfree(tcontext);
	pfree(ncontext);
}