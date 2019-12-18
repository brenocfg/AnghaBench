#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {int n_members; TYPE_1__** members; } ;
struct TYPE_11__ {scalar_t__ attnum; scalar_t__ attisdropped; } ;
struct TYPE_10__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
struct TYPE_9__ {int /*<<< orphan*/  tuple; } ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 void* NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 void* PG_TOAST_NAMESPACE ; 
#define  RELKIND_INDEX 132 
#define  RELKIND_PARTITIONED_TABLE 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_SEQUENCE 129 
#define  RELKIND_VIEW 128 
 void* RelationRelationId ; 
 int /*<<< orphan*/  ReleaseCatCacheList (TYPE_4__*) ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_COLUMN ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SCHEMA ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SEQUENCE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_TABLE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_VIEW ; 
 int /*<<< orphan*/  SEPG_DB_COLUMN__DROP ; 
 int /*<<< orphan*/  SEPG_DB_SCHEMA__REMOVE_NAME ; 
 int /*<<< orphan*/  SEPG_DB_TABLE__DROP ; 
 TYPE_4__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* getObjectIdentity (TYPE_2__*) ; 
 void* get_rel_namespace (void*) ; 
 char get_rel_relkind (void*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sepgsql_index_modify (void*) ; 

void
sepgsql_relation_drop(Oid relOid)
{
	ObjectAddress object;
	char	   *audit_name;
	uint16_t	tclass = 0;
	char		relkind = get_rel_relkind(relOid);

	switch (relkind)
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
			/* ignore indexes on toast tables */
			if (get_rel_namespace(relOid) == PG_TOAST_NAMESPACE)
				return;
			/* other indexes are handled specially below; no need for tclass */
			break;
		default:
			/* ignore other relkinds */
			return;
	}

	/*
	 * check db_schema:{remove_name} permission
	 */
	object.classId = NamespaceRelationId;
	object.objectId = get_rel_namespace(relOid);
	object.objectSubId = 0;
	audit_name = getObjectIdentity(&object);

	sepgsql_avc_check_perms(&object,
							SEPG_CLASS_DB_SCHEMA,
							SEPG_DB_SCHEMA__REMOVE_NAME,
							audit_name,
							true);
	pfree(audit_name);

	/* deal with indexes specially */
	if (relkind == RELKIND_INDEX)
	{
		sepgsql_index_modify(relOid);
		return;
	}

	/*
	 * check db_table/sequence/view:{drop} permission
	 */
	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = 0;
	audit_name = getObjectIdentity(&object);

	sepgsql_avc_check_perms(&object,
							tclass,
							SEPG_DB_TABLE__DROP,
							audit_name,
							true);
	pfree(audit_name);

	/*
	 * check db_column:{drop} permission
	 */
	if (relkind == RELKIND_RELATION || relkind == RELKIND_PARTITIONED_TABLE)
	{
		Form_pg_attribute attForm;
		CatCList   *attrList;
		HeapTuple	atttup;
		int			i;

		attrList = SearchSysCacheList1(ATTNUM, ObjectIdGetDatum(relOid));
		for (i = 0; i < attrList->n_members; i++)
		{
			atttup = &attrList->members[i]->tuple;
			attForm = (Form_pg_attribute) GETSTRUCT(atttup);

			if (attForm->attisdropped)
				continue;

			object.classId = RelationRelationId;
			object.objectId = relOid;
			object.objectSubId = attForm->attnum;
			audit_name = getObjectIdentity(&object);

			sepgsql_avc_check_perms(&object,
									SEPG_CLASS_DB_COLUMN,
									SEPG_DB_COLUMN__DROP,
									audit_name,
									true);
			pfree(audit_name);
		}
		ReleaseCatCacheList(attrList);
	}
}