#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_COLUMN ; 
 int SEPG_DB_COLUMN__RELABELFROM ; 
 int SEPG_DB_COLUMN__SETATTR ; 
 int /*<<< orphan*/  SEPG_DB_PROCEDURE__RELABELTO ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* getObjectIdentity (TYPE_1__*) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_1__*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
sepgsql_attribute_relabel(Oid relOid, AttrNumber attnum,
						  const char *seclabel)
{
	ObjectAddress object;
	char	   *audit_name;
	char		relkind = get_rel_relkind(relOid);

	if (relkind != RELKIND_RELATION && relkind != RELKIND_PARTITIONED_TABLE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot set security label on non-regular columns")));

	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = attnum;
	audit_name = getObjectIdentity(&object);

	/*
	 * check db_column:{setattr relabelfrom} permission
	 */
	sepgsql_avc_check_perms(&object,
							SEPG_CLASS_DB_COLUMN,
							SEPG_DB_COLUMN__SETATTR |
							SEPG_DB_COLUMN__RELABELFROM,
							audit_name,
							true);

	/*
	 * check db_column:{relabelto} permission
	 */
	sepgsql_avc_check_perms_label(seclabel,
								  SEPG_CLASS_DB_COLUMN,
								  SEPG_DB_PROCEDURE__RELABELTO,
								  audit_name,
								  true);
	pfree(audit_name);
}