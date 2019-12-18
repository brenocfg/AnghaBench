#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_14__ {scalar_t__ attnum; int /*<<< orphan*/  attname; } ;
struct TYPE_13__ {int relkind; scalar_t__ relnamespace; int /*<<< orphan*/  relname; } ;
struct TYPE_12__ {scalar_t__ objectId; scalar_t__ objectSubId; void* classId; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_class ;
typedef  TYPE_4__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_attribute_attrelid ; 
 int /*<<< orphan*/  Anum_pg_class_oid ; 
 void* AttributeRelationId ; 
 int /*<<< orphan*/  AttributeRelidNumIndexId ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  ClassOidIndexId ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 void* NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 scalar_t__ PG_TOAST_NAMESPACE ; 
#define  RELKIND_INDEX 132 
#define  RELKIND_PARTITIONED_TABLE 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_SEQUENCE 129 
#define  RELKIND_VIEW 128 
 void* RelationRelationId ; 
 int /*<<< orphan*/  SEPGSQL_LABEL_TAG ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_COLUMN ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SCHEMA ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SEQUENCE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_TABLE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_VIEW ; 
 int /*<<< orphan*/  SEPG_DB_COLUMN__CREATE ; 
 int /*<<< orphan*/  SEPG_DB_DATABASE__CREATE ; 
 int /*<<< orphan*/  SEPG_DB_SCHEMA__ADD_NAME ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSecurityLabel (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SnapshotSelf ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  getObjectIdentity (TYPE_2__*) ; 
 char* get_namespace_name (scalar_t__) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sepgsql_compute_create (char*,char*,int /*<<< orphan*/ ,char*) ; 
 char* sepgsql_get_client_label () ; 
 char* sepgsql_get_label (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_index_modify (void*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (void*,int /*<<< orphan*/ ) ; 

void
sepgsql_relation_post_create(Oid relOid)
{
	Relation	rel;
	ScanKeyData skey;
	SysScanDesc sscan;
	HeapTuple	tuple;
	Form_pg_class classForm;
	ObjectAddress object;
	uint16_t	tclass;
	char	   *scontext;		/* subject */
	char	   *tcontext;		/* schema */
	char	   *rcontext;		/* relation */
	char	   *ccontext;		/* column */
	char	   *nsp_name;
	StringInfoData audit_name;

	/*
	 * Fetch catalog record of the new relation. Because pg_class entry is not
	 * visible right now, we need to scan the catalog using SnapshotSelf.
	 */
	rel = table_open(RelationRelationId, AccessShareLock);

	ScanKeyInit(&skey,
				Anum_pg_class_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(relOid));

	sscan = systable_beginscan(rel, ClassOidIndexId, true,
							   SnapshotSelf, 1, &skey);

	tuple = systable_getnext(sscan);
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for relation %u", relOid);

	classForm = (Form_pg_class) GETSTRUCT(tuple);

	/* ignore indexes on toast tables */
	if (classForm->relkind == RELKIND_INDEX &&
		classForm->relnamespace == PG_TOAST_NAMESPACE)
		goto out;

	/*
	 * check db_schema:{add_name} permission of the namespace
	 */
	object.classId = NamespaceRelationId;
	object.objectId = classForm->relnamespace;
	object.objectSubId = 0;
	sepgsql_avc_check_perms(&object,
							SEPG_CLASS_DB_SCHEMA,
							SEPG_DB_SCHEMA__ADD_NAME,
							getObjectIdentity(&object),
							true);

	switch (classForm->relkind)
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
			/* deal with indexes specially; no need for tclass */
			sepgsql_index_modify(relOid);
			goto out;
		default:
			/* ignore other relkinds */
			goto out;
	}

	/*
	 * Compute a default security label when we create a new relation object
	 * under the specified namespace.
	 */
	scontext = sepgsql_get_client_label();
	tcontext = sepgsql_get_label(NamespaceRelationId,
								 classForm->relnamespace, 0);
	rcontext = sepgsql_compute_create(scontext, tcontext, tclass,
									  NameStr(classForm->relname));

	/*
	 * check db_xxx:{create} permission
	 */
	nsp_name = get_namespace_name(classForm->relnamespace);
	initStringInfo(&audit_name);
	appendStringInfo(&audit_name, "%s.%s",
					 quote_identifier(nsp_name),
					 quote_identifier(NameStr(classForm->relname)));
	sepgsql_avc_check_perms_label(rcontext,
								  tclass,
								  SEPG_DB_DATABASE__CREATE,
								  audit_name.data,
								  true);

	/*
	 * Assign the default security label on the new regular or partitioned
	 * relation.
	 */
	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = 0;
	SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, rcontext);

	/*
	 * We also assign a default security label on columns of a new table.
	 */
	if (classForm->relkind == RELKIND_RELATION ||
		classForm->relkind == RELKIND_PARTITIONED_TABLE)
	{
		Relation	arel;
		ScanKeyData akey;
		SysScanDesc ascan;
		HeapTuple	atup;
		Form_pg_attribute attForm;

		arel = table_open(AttributeRelationId, AccessShareLock);

		ScanKeyInit(&akey,
					Anum_pg_attribute_attrelid,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(relOid));

		ascan = systable_beginscan(arel, AttributeRelidNumIndexId, true,
								   SnapshotSelf, 1, &akey);

		while (HeapTupleIsValid(atup = systable_getnext(ascan)))
		{
			attForm = (Form_pg_attribute) GETSTRUCT(atup);

			resetStringInfo(&audit_name);
			appendStringInfo(&audit_name, "%s.%s.%s",
							 quote_identifier(nsp_name),
							 quote_identifier(NameStr(classForm->relname)),
							 quote_identifier(NameStr(attForm->attname)));

			ccontext = sepgsql_compute_create(scontext,
											  rcontext,
											  SEPG_CLASS_DB_COLUMN,
											  NameStr(attForm->attname));

			/*
			 * check db_column:{create} permission
			 */
			sepgsql_avc_check_perms_label(ccontext,
										  SEPG_CLASS_DB_COLUMN,
										  SEPG_DB_COLUMN__CREATE,
										  audit_name.data,
										  true);

			object.classId = RelationRelationId;
			object.objectId = relOid;
			object.objectSubId = attForm->attnum;
			SetSecurityLabel(&object, SEPGSQL_LABEL_TAG, ccontext);

			pfree(ccontext);
		}
		systable_endscan(ascan);
		table_close(arel, AccessShareLock);
	}
	pfree(rcontext);

out:
	systable_endscan(sscan);
	table_close(rel, AccessShareLock);
}