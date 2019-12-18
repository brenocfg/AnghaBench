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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 char RELKIND_SEQUENCE ; 
 char RELKIND_VIEW ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_SEQUENCE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_TABLE ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_VIEW ; 
 int SEPG_DB_TABLE__RELABELFROM ; 
 int /*<<< orphan*/  SEPG_DB_TABLE__RELABELTO ; 
 int SEPG_DB_TABLE__SETATTR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* getObjectIdentity (TYPE_1__*) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_1__*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms_label (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
sepgsql_relation_relabel(Oid relOid, const char *seclabel)
{
	ObjectAddress object;
	char	   *audit_name;
	char		relkind = get_rel_relkind(relOid);
	uint16_t	tclass = 0;

	if (relkind == RELKIND_RELATION || relkind == RELKIND_PARTITIONED_TABLE)
		tclass = SEPG_CLASS_DB_TABLE;
	else if (relkind == RELKIND_SEQUENCE)
		tclass = SEPG_CLASS_DB_SEQUENCE;
	else if (relkind == RELKIND_VIEW)
		tclass = SEPG_CLASS_DB_VIEW;
	else
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot set security labels on relations except "
						"for tables, sequences or views")));

	object.classId = RelationRelationId;
	object.objectId = relOid;
	object.objectSubId = 0;
	audit_name = getObjectIdentity(&object);

	/*
	 * check db_xxx:{setattr relabelfrom} permission
	 */
	sepgsql_avc_check_perms(&object,
							tclass,
							SEPG_DB_TABLE__SETATTR |
							SEPG_DB_TABLE__RELABELFROM,
							audit_name,
							true);

	/*
	 * check db_xxx:{relabelto} permission
	 */
	sepgsql_avc_check_perms_label(seclabel,
								  tclass,
								  SEPG_DB_TABLE__RELABELTO,
								  audit_name,
								  true);
	pfree(audit_name);
}