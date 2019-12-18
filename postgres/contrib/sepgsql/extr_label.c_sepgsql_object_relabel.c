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
typedef  int /*<<< orphan*/  security_context_t ;
struct TYPE_4__ {int classId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  objectSubId; } ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
#define  DatabaseRelationId 131 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
#define  NamespaceRelationId 130 
#define  ProcedureRelationId 129 
#define  RelationRelationId 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 char const* getObjectTypeDescription (TYPE_1__ const*) ; 
 scalar_t__ security_check_context_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sepgsql_attribute_relabel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sepgsql_database_relabel (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sepgsql_proc_relabel (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sepgsql_relation_relabel (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sepgsql_schema_relabel (int /*<<< orphan*/ ,char const*) ; 

void
sepgsql_object_relabel(const ObjectAddress *object, const char *seclabel)
{
	/*
	 * validate format of the supplied security label, if it is security
	 * context of selinux.
	 */
	if (seclabel &&
		security_check_context_raw((security_context_t) seclabel) < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("SELinux: invalid security label: \"%s\"", seclabel)));

	/*
	 * Do actual permission checks for each object classes
	 */
	switch (object->classId)
	{
		case DatabaseRelationId:
			sepgsql_database_relabel(object->objectId, seclabel);
			break;

		case NamespaceRelationId:
			sepgsql_schema_relabel(object->objectId, seclabel);
			break;

		case RelationRelationId:
			if (object->objectSubId == 0)
				sepgsql_relation_relabel(object->objectId,
										 seclabel);
			else
				sepgsql_attribute_relabel(object->objectId,
										  object->objectSubId,
										  seclabel);
			break;

		case ProcedureRelationId:
			sepgsql_proc_relabel(object->objectId, seclabel);
			break;

		default:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("sepgsql provider does not support labels on %s",
							getObjectTypeDescription(object))));
			break;
	}
}