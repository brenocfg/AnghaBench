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
struct TYPE_4__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  SEPG_CLASS_DB_DATABASE ; 
 int /*<<< orphan*/  SEPG_DB_DATABASE__SETATTR ; 
 char* getObjectIdentity (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sepgsql_avc_check_perms (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
sepgsql_database_setattr(Oid databaseId)
{
	ObjectAddress object;
	char	   *audit_name;

	/*
	 * check db_database:{setattr} permission
	 */
	object.classId = DatabaseRelationId;
	object.objectId = databaseId;
	object.objectSubId = 0;
	audit_name = getObjectIdentity(&object);

	sepgsql_avc_check_perms(&object,
							SEPG_CLASS_DB_DATABASE,
							SEPG_DB_DATABASE__SETATTR,
							audit_name,
							true);
	pfree(audit_name);
}